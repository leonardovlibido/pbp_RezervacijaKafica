#include "demo.h"

//gcc 1.c -lmysqlclient

#define QUERY_SIZE 2048

#define BUFFER_SIZE 128

/* Funkcija error_fatal() ispisuje poruku o gresci i potom prekida program. */
static void error_fatal (char *format, ...);

int prijaviKorisnika( MYSQL *connection );
int prijaviKonobara( MYSQL *connection );
void korisnikAkcije( MYSQL *connection );
void konobarAkcije( MYSQL *connection );

int main (int argc, char **argv)
{
    MYSQL *connection;	/* Promenljiva za konekciju. */
    // char buffer[BUFFER_SIZE];
    /* Incijalizuje se promenljiva koja ce postavljati konekciju. */
    connection = mysql_init (NULL);
    if (connection == NULL){
		printf("connection JE NULL >:(");
      	error_fatal ("Greska u konekciji. %s\n", mysql_error (connection));
    }
    /* Pokusava se sa konektovanjem na bazu. */
    if (mysql_real_connect(connection, "127.0.0.1", "root", "", "RezervacijaKafica",
        0, NULL,0) == NULL){
        error_fatal ("Greska u konekciji. %s\n", mysql_error (connection));
    }
    int option;
    int running = 1;
    int tipKorisnika = -1;


    while ( running ){
        printf("\nIzaberite kao koji korisnik zelite da se ulogujete (unesite redni broj opcije ):\n");
        printf("0. Izadji\n");
        printf("1. Korisnik\n");
        printf("2. Konobar\n");
        scanf("%d", &izabranTipKorisnika);
		switch ( izabranTipKorisnika ){
			case 0:
			    printf("Dovidjenja.\n");
			    break;
			case 1:
			    printf("Hajde da vidimo da li si korisnik.\n");
                prijaviKorisnika(connection);
                korisnikAkcije(connection);
			    break;
			case 2:
			    printf("Ti kazes da si konobar?.\n");
//                prijaviKonobara(connection);
//                konobarAkcije(connection);
				break;
            default:
                printf("Los ulaz. Unesite redni broj opcije koju zelite da izaberete\n");
                break;
		}
    }


    /* Zatvara se connection. */
    mysql_close (connection);

    /* Zavrsava se program */
    exit(EXIT_SUCCESS);
}



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
		printf("Unesite vase korsinicko ime\n");
		scanf("%s", bufferName);
		printf("Unesite vasu lozinku\n");
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
			printf("Uneli ste pogresnu lozinku ili password.\n");
            printf("Zelite li da pokusate ponovo? ( y/n )\nj");
            scanf("%s", bufferName);
            if ( bufferName != 'y' ){
                validanUnos = 1;
                idKorisnika = -1;
            }
		}
		else{
			validanUnos = 1;
			// idKorisnika = kako se pristupa ovome?
			print_result(result, 1);
			idKorisnika = 123;
		}
		mysql_free_result (result); //TODO dal ovo treba ovako?
	}
	return idKorisnika;
}


void korisnikAkcije( MYSQL *connection )
{
    int running = 1;
    printf("kornik radi stvari\n");
    printf(" ... jos stvari ...\n");
    printf(" zavrsava svoje stvari.\n");
	while ( running ){
        printf("\nIzaberite koju akciju zelite da izvrsite:\n");
        printf("0. Izadji\n");
        printf("1. Izlistaj kafice sa slobodnim stolovima\n");
        printf("2. Napravi rezervaciju\n");
        printf("3. Oceni kafic\n");
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


int prijaviKonobara( MYSQL *connection )
{
	return 7777;
}


void konobarAkcije( MYSQL *connection )
{
    printf("konobar radi stvari\n");
    printf(" ... jos stvari ...\n");
    printf(" zavrsava svoje stvari.\n");
}


static void error_fatal (char *format, ...)
{
  va_list arguments;		/* Lista argumenata funkcije. */

  /* Stampa se string prostavljen argumentima funkcije. */
  va_start (arguments, format);
  vfprintf (stderr, format, arguments);
  va_end (arguments);

  /* Prekida se program. */
  exit (EXIT_FAILURE);
}

