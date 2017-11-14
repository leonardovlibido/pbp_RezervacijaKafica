#include "app.h"

//gcc 1.c -lmysqlclient

#define QUERY_SIZE 2048

#define BUFFER_SIZE 128

/* Funkcija error_fatal() ispisuje poruku o gresci i potom prekida program. */
static void error_fatal (char *format, ...);

/* Funkcija titleScreen brise trenutni sadzraj sa ekrana u terminalu zbog lepseg prikaza */
void titleScreen();
void printPrompt();

int prijaviKorisnika( MYSQL *connection );
int prijaviKonobara( MYSQL *connection );
void korisnikAkcije( MYSQL *connection, int idKorisnika );
void konobarAkcije( MYSQL *connection, int idKonobara );


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
    if (mysql_real_connect(connection, "localhost", "root", "", "RezervacijaKafica",
        0, NULL,0) == NULL){
        error_fatal ("Greska u konekciji. %s\n", mysql_error (connection));
    }
    int option;
    int tipKorisnika = -1;
	int izabranTipKorisnika = 1;
	int idKorisnika = -1;
	int idKonobara = -1;

    while ( izabranTipKorisnika ){
		titleScreen();
        printf("\nIzaberite kao koji korisnik zelite da se ulogujete (unesite redni broj opcije ):\n");
        printf("0. Izadji\n");
        printf("1. Korisnik\n");
        printf("2. Konobar\n");
		printPrompt();
        scanf("%d", &izabranTipKorisnika);
		switch ( izabranTipKorisnika ){
			case 0:
			    printf("Dovidjenja.\n");
			    break;
			case 1:
				titleScreen();
			    printf("Izabrali ste da zelite da se ulogujete kao korisnik.\n");
                idKorisnika = prijaviKorisnika(connection);
				if ( idKorisnika != -1 ){
					korisnikAkcije(connection, idKorisnika);
				}
			    break;
			case 2:
				titleScreen();
			    printf("Izabrali ste da zelite da se ulogujete kao konobar.\n");
                idKonobara = prijaviKonobara(connection);
				if ( idKonobara != -1 ){
					konobarAkcije(connection, idKonobara);
				}
				break;
            default:
				titleScreen();
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
			printf("Unesite bilo koji karakter da biste nastavili\n");
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
	while ( running ){
		titleScreen();
        printf("\nIzaberite koju akciju zelite da izvrsite:\n");
        printf("0. Odjavi se\n");
        printf("1. Izlistaj rezervacije po kaficu.\n");
        printf("2. Obradi rezervaciju na cekanju.\n");
        printf("3. Promeni status rezervacija koje su bile danas.\n");
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


void titleScreen()
{
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
	const char *FRAME0 = "                                                                               \n";
	const char *FRAME1 = "===============================================================================\n";
	const char *FRAME2 = "||                                                                           ||\n";
	const char *TITLE = "||                            Rezervacija Kafica                             ||\n";
	write(STDOUT_FILENO, FRAME0, 80);
	write(STDOUT_FILENO, FRAME1, 80);
	write(STDOUT_FILENO, FRAME2, 80);
	write(STDOUT_FILENO, TITLE, 80);
	write(STDOUT_FILENO, FRAME2, 80);
	write(STDOUT_FILENO, FRAME1, 80);
	write(STDOUT_FILENO, FRAME0, 80);
}

void printPrompt()
{
	const char *PROMPT = ">> ";
	write(STDOUT_FILENO, PROMPT, 3);
}
