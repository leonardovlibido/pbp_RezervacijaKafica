#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#include "util.h"


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

void pressEnterToContinue()
{
    printf("Press Enter to Continue\n");
    printPrompt()
    while( getchar() != '\n' );
}

void print_result(MYSQL_RES *result, int mark_order)
{
    MYSQL_FIELD *field;
    MYSQL_ROW row;

    row = mysql_fetch_row(result);
    if (row == 0){
        printf("Wrong username or pass\n");
        return;
    }

    if (mark_order){
        printf("%-13s|", "place");
    }
    while( NULL != (field = mysql_fetch_field(result))){
        printf("%-13s|", field->name);
    }
    printf("\n");
    int num_fields = mysql_num_fields(result);

    int i=0;
    while ((row = mysql_fetch_row(result)) ){
        // unsigned long *lengths = mysql_fetch_lengths(result);
        if (mark_order){
            printf("%-13d|", ++i);
        }
        for (int i=0; i<num_fields; i++){
            printf ("%-13s|", row[i] ? row[i] : "NULL");
        }
        printf ("\n");
    }

    printf ("\n");
}
