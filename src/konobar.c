#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "util.h"
#include "konobar.h"

int prijaviKonobara( MYSQL *connection )
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    // MYSQL_FIELD *field;
    char query[QUERY_SIZE];
    char bufferName[BUFFER_SIZE];
    char bufferPass[BUFFER_SIZE];
	int validanUnos = 0;
	int idKonobara = -1;

	while( !validanUnos ){
		printf("Prijavite se:\n");
		printf("\nUnesite vase korsinicko ime\n");
		printPrompt();
		scanf("%s", bufferName);
		printf("\nUnesite vasu lozinku\n");
		printPrompt();
		scanf("%s", bufferPass);

		sprintf (query, 
                "select idKonobar \
                from Konobar\
                where username = '%s' and password = '%s'",
                bufferName,
                bufferPass);

		if (mysql_query (connection, query) != 0){
			error_fatal ("Error in query %s\n", mysql_error (connection));
		}
		result = mysql_use_result (connection);

		// int num_fields = mysql_num_fields(result);
		row = mysql_fetch_row(result);
		if (row == 0){
			titleScreen();
			printf("Uneli ste pogresnu lozinku ili password.\n");
            printf("Zelite li da pokusate ponovo? ( y/n )\n");
			printPrompt();
            scanf("%s", bufferName);
            if ( bufferName[0] != 'y' ){
                validanUnos = 1;
                idKonobara = -1;
            }
			titleScreen();
		}
		else{
			titleScreen();
			printf("Dobrodosli %s.\n", bufferName);
            pressAnyKeyToContinue();
			validanUnos = 1;
			idKonobara = atoi(row[0]);
			// printf("Ovo je id konobara: %d\n", idKorisnika);
		}
		mysql_free_result (result); //TODO dal ovo treba ovako?
	}
	return idKonobara;
}


void konobarAkcije( MYSQL *connection, int idKonobara )
{
    int running = 1;

	titleScreen();
    int idKafica = izaberiKafic(connection, idKonobara);
    pressAnyKeyToContinue();

    while ( running ){
		titleScreen();
        printf("\nIzaberite koju akciju zelite da izvrsite:\n");
        printf("0. Odjavi se.\n");
        printf("1. Uloguj se u drugi kafic.\n");
        printf("2. Izlistaj rezervacije na cekanju.\n");
        printf("3. Izlistaj slobodne stolove.\n");
        printf("4. Obradi rezervaciju na cekanju.\n");
        printf("5. Promeni status rezervacija koje su bile danas.\n");
		printPrompt();
        scanf("%d", &running);
		switch ( running ){
			case 0:
			    titleScreen();
			    printf("Uspesno ste se odjavili.\n");
                pressAnyKeyToContinue();
				break;
			case 1:
                titleScreen();
                idKafica = izaberiKafic(connection, idKonobara);
                pressAnyKeyToContinue();
				break;
			case 2:
                titleScreen();
                izlistajRezervacijePoKaficu(connection, idKonobara);
                pressAnyKeyToContinue();
				break;
            case 3:
                titleScreen();
                izlistajSlobodneStolove(connection, idKafica);
                pressAnyKeyToContinue();
				break;

			case 4:
                titleScreen();
                obradiRezervacijuNaCekanju(connection, idKonobara, idKafica);
                pressAnyKeyToContinue();
				break;
            default:
                printf("Los ulaz. Unesite redni broj opcije koju zelite da izaberete\n");
                break;
		}
	}
}


int izaberiKafic( MYSQL *connection, int idKonobara)
{

    MYSQL_RES *result;
    char query[QUERY_SIZE];
    int idKafica;

    printf("Zaposleni ste u narednim kaficima:\n\n");
    sprintf (query,
            "select idKafic, ime, ulica, brojUlice\
            from zaposlen z join Kafic k on z.Kafic_idKafic=k.idKafic\
            where z.Konobar_idKonobar=%d", idKonobara);

    /* Pokusava se sa izvrsavanjem upita. */
    if (mysql_query (connection, query) != 0)
        error_fatal ("Error in query %s\n", mysql_error (connection));

    /* Preuzima se result. */
    result = mysql_store_result (connection);
    print_result(result, 0);
    mysql_free_result (result);

    printf("Unesite id Kafica za koji zelite da se ulogujete:\n");
	printPrompt();
    scanf("%d", &idKafica);

}



void izlistajRezervacijePoKaficu( MYSQL *connection, int idKafica)
{
    MYSQL_RES *result;
    char query[QUERY_SIZE];

    sprintf (query,
            "select idRezervacije, datum, vreme, brLjudi, k.ime as imeKafica, status \
            from Rezervacije r join Kafic k on r.Kafic_idKafic=k.idKafic \
            where r.Kafic_idKafic=%d and status=\"na cekanju\"", idKafica);

    /* Pokusava se sa izvrsavanjem upita. */
    if (mysql_query (connection, query) != 0)
        error_fatal ("Error in query %s\n", mysql_error (connection));

    /* Preuzima se result. */
    result = mysql_store_result (connection);
    print_result(result, 0);
    mysql_free_result (result);
}


void izlistajSlobodneStolove( MYSQL *connection, int idKafica)
{
    MYSQL_RES *result;
    char query[QUERY_SIZE];

    sprintf (query,
            "select redniBroj, brojMesta\
            from Sto\
            where Kafic_idKafic=%d and trenutnoStanje=\"slobodno\"", idKafica);

    /* Pokusava se sa izvrsavanjem upita. */
    if (mysql_query (connection, query) != 0)
        error_fatal ("Error in query %s\n", mysql_error (connection));

    /* Preuzima se result. */
    result = mysql_store_result (connection);
    print_result(result, 0);
    mysql_free_result (result);

}


void obradiRezervacijuNaCekanju( MYSQL *connection, int idKonobara, int idKafica)
{
    MYSQL_RES *result;
    char query[QUERY_SIZE];
    int idRezervacije;

    izlistajRezervacijePoKaficu( connection, idKafica);

    printf("Unesite id Rezervacije koju zelite da obradite");
    printPrompt();
    scanf("%d", &idRezervacije);

    char* chooseAnotherTable[QUERY_SIZE];
    chooseTable[0] = 'y';

    while(chooseTable[0] == 'y' || chooseTable[0] =='Y'){
        izlistajSlobodneStolove();
        printf("Izaberite koji sto zelite da rezervisete\n");
        printf("Uspesno ste rezervisali sto\n");
        //TODO CODE
        printf("Zelite li da rezervisete jos neki sto za datu rezervaciju?(Y/N)\n");
        printPrompt();
        scanf("%d", &chooseAnotherTable);
    }

    return;
}

