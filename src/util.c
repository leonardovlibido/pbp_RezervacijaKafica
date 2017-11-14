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

