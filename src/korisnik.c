#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "util.h"
#include "korisnik.h"

int prijaviKorisnika( MYSQL *connection )
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    // MYSQL_FIELD *field;
    char query[QUERY_SIZE];
    char bufferName[BUFFER_SIZE];
    char bufferPass[BUFFER_SIZE];
	int validanUnos = 0;
	int idKorisnika = 111;

	while( !validanUnos ){
		printf("Prijavite se:\n");
		printf("\nUnesite vase korsinicko ime\n");
		printPrompt();
		scanf("%s", bufferName);
		printf("\nUnesite vasu lozinku\n");
		printPrompt();
		scanf("%s", bufferPass);

		sprintf (query, 
                "select idKorisnik \
                from Korisnik\
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
                idKorisnika = -1;
            }
			titleScreen();
		}
		else{
			titleScreen();
			printf("Dobrodosli %s.\n", bufferName);
			printf("Unesite bilo koji karakter da biste nastavili\n");
			validanUnos = 1;
			idKorisnika = atoi(row[0]);
			// printf("Ovo je id korisnika: %d\n", idKorisnika);
		}
		mysql_free_result (result); //TODO dal ovo treba ovako?
	}
	return idKorisnika;
}


void korisnikAkcije( MYSQL *connection, int idKorisnika )
{
    int running = 1;
	while ( running ){
		titleScreen();
        printf("\nIzaberite koju akciju zelite da izvrsite:\n");
        printf("0. Odjavi se\n");
        printf("1. Izlistaj kafice sa slobodnim stolovima\n");
        printf("2. Napravi rezervaciju\n");
        printf("3. Oceni kafic\n");
		printPrompt();
        scanf("%d", &running);
		switch ( running ){
			case 0:
			    printf("Dovidjenja.\n");
				break;
			case 1:
			    titleScreen();
                izlistajKafice(connection);
                pressAnyKeyToContinue();
				break;
			case 2:
			    titleScreen();
                rezervisiKafic(connection, idKorisnika);
                pressAnyKeyToContinue();
				break;
			case 3:
			    titleScreen();
                oceniKafic(connection, idKorisnika);
                pressAnyKeyToContinue();
				break;
            default:
                printf("Los ulaz. Unesite redni broj opcije koju zelite da izaberete\n");
                pressAnyKeyToContinue();
                break;
		}
    }
}


void izlistajKafice( MYSQL *connection)
{
    MYSQL_RES *result;
    char query[QUERY_SIZE];
    /* Formulise se upit kojim se izlistavaju svi kafici sa slobodnim mestima. */
    sprintf (query,
            "select idKafic, ime, ulica, brojUlice, radnoVremeRadniDan, radnoVremeVikend \
                    brSlobodnihStolova, ocena \
            from Kafic \
            where brSlobodnihStolova > 0");

    /* Pokusava se sa izvrsavanjem upita. */
    if (mysql_query (connection, query) != 0)
        error_fatal ("Error in query %s\n", mysql_error (connection));

    /* Preuzima se result. */
    result = mysql_store_result (connection);
    print_result(result, 0);
    mysql_free_result (result);
}


void rezervisiKafic( MYSQL *connection, int idKorisnika)
{
    char query[QUERY_SIZE];
    char bufferDatum[BUFFER_SIZE];
    char bufferVreme[BUFFER_SIZE];
    int brLjudi;

    int idKafica;

    printf("Izaberite neki od kafica sa slobodnim stolovima:\n");
    izlistajKafice(connection);
    printf("Unesite id Kafica koji zelite da rezervisete:\n");
	printPrompt();
    scanf("%d", &idKafica);
    // TODO provera da li postoji kafic sa tim id-em
    printf("Unesite datum za koji zelite da rezervisete mesto: (YYYY-MM-DD)\n");
	printPrompt();
    scanf("%s", bufferDatum);
    printf("Unesite vreme: (HH:SS)\n");
	printPrompt();
    scanf("%s", bufferVreme);
    printf("Unesite broj ljudi koji ce doci:\n");
	printPrompt();
    scanf("%d", &brLjudi);

    // TODO ubaci da je ovo autoincrement
    sprintf (query,
            "insert into Rezervacije ( datum, vreme, brLjudi, Korisnik_idKorisnik,\
                        Kafic_idKafic ) values \
            ( %s, %s, %d, %d, %d )",
            bufferDatum, bufferVreme, brLjudi, idKorisnika, idKafica);
    // TODO provera da li se uspesno rezervisalo
    
    titleScreen();
    printf("Uspesno ste rezervisali mesto.\n");
}


void oceniKafic( MYSQL *connection, int idKorisnika )
{
    MYSQL_RES *result;
    MYSQL_ROW row;

    char query[QUERY_SIZE];
    int idKafica;
    int ocena;

    sprintf( query, "select idKafic, ime, ulica, brojUlice from Kafic");
    if (mysql_query (connection, query) != 0){
        error_fatal ("error in query %s\n", mysql_error (connection));
    }
    result = mysql_use_result (connection);
    printf("Unesite id Kafica zelite da ocenite:\n");
    print_result(result, 0);
    mysql_free_result(result);

	printPrompt();
    scanf("%d", &idKafica);

    sprintf( query, "select * from Ocena where Korisnik_idKorisnik = %d", idKorisnika);
    if (mysql_query (connection, query) != 0){
        error_fatal ("Error in query %s\n", mysql_error (connection));
    }
    result = mysql_use_result (connection);
    row = mysql_fetch_row(result);
    mysql_free_result (result);

    printf("Koliko zvezdica zelite da date kaficu?\n");
	printPrompt();
    scanf("%d", &ocena);

    if (row == 0){
        // mora da se unese ocena
        sprintf( query,
                "insert into Ocena ( Korisnik_idKorisnik, Kafic_idKafic, brZvezdica) values\
                ( %d, %d, %d )", idKorisnika, idKafica, ocena);
        if (mysql_query (connection, query) != 0){
            error_fatal ("Error in query %s\n", mysql_error (connection));
        }
        //result = mysql_store_result (connection);
        // TODO check if query did what it shoudl
    }
    else{
        // mora da se azurira ocena
        sprintf( query,
                "update Ocena \
                set brZvezdica = %d \
                where Korisnik_idKorisnik = %d and Kafic_idKafic = %d",
                ocena, idKorisnika, idKafica);
        if (mysql_query (connection, query) != 0){
            error_fatal ("Error in query %s\n", mysql_error (connection));
        }
        //result = mysql_store_result (connection);
        //TODO check if query did what it shoudl
    }
    titleScreen();
    printf("Uspesno ste uneli ocenu %d.\n", ocena);
}

