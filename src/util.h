#ifndef UTIL_H
#define UTIL_H

#define QUERY_SIZE 2048
#define BUFFER_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

/* Funkcija error_fatal() ispisuje poruku o gresci i potom prekida program. */
void error_fatal(char *format, ...);

/* Funkcija titleScreen brise trenutni sadzraj sa ekrana u terminalu zbog lepseg prikaza */
void titleScreen();
void printPrompt();

#endif

