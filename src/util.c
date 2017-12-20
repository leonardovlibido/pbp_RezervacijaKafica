#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#include "util.h"

#define COOL_SCREEN


void error_fatal(char *format, ...)
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
#ifdef COOL_SCREEN
    titleScreen2();
    printf("\n");
    return;
#endif

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
void titleScreen2()
{
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    const char *title =
"   ___                                _   _        __ __     ____         \n\
  / _ \\___ ___ ___ _____  _____ _____(_) (_)__ _  / //_/__ _/ _(_)______ _\n\
 / , _/ -_)_ // -_) __/ |/ / _ `/ __/ / / / _ `/ / ,< / _ `/ _/ / __/ _ `/\n\
/_/|_|\\__//__/\\__/_/  |___/\\_,_/\\__/_/_/ /\\_,_/ /_/|_|\\_,_/_//_/\\__/\\_,_/ \n\
                                    |___/                                 \n";
    write(STDOUT_FILENO, title, 75*5);

}


void printPrompt()
{
	const char *PROMPT = "\n>> ";
	write(STDOUT_FILENO, PROMPT, 4);
}

void pressAnyKeyToContinue()
{
    char garbage[BUFFER_SIZE];
    printf("\nKliknite enter da biste nastavili. ");
    fgets(garbage,100,stdin);
    fgets(garbage,100,stdin);
}

void print_result(MYSQL_RES *result, int mark_order)
{
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    char garbage[1000];
    garbage[0]='\0';

    if (mark_order){
        printf("%-19s|", "place");
    }
    while( NULL != (field = mysql_fetch_field(result))){
        printf("%-19s|", field->name);
    }
    printf("\n");
    int num_fields = mysql_num_fields(result);

    int i=0;
    while ((row = mysql_fetch_row(result)) ){
        // unsigned long *lengths = mysql_fetch_lengths(result);
        if (mark_order){
            printf("%-19d|", ++i);
        }
        for (int i=0; i<num_fields; i++){
            printf ("%-19s|", row[i] ? row[i] : "NULL");
        }
        printf ("\n");
    }

    printf ("\n");
}
