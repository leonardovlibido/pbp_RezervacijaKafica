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
                //TODO
				break;
			case 2:
                //TODO
				break;
			case 3:
                //TODO
				break;
            default:
                printf("Los ulaz. Unesite redni broj opcije koju zelite da izaberete\n");
                break;
		}
    }
}

