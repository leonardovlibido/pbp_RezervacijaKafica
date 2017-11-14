#include "app.h"

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

