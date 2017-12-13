#ifndef UTIL_H
#define UTIL_H

#define QUERY_SIZE 2048
#define BUFFER_SIZE 128

#include <stdarg.h>
#include <mysql/mysql.h>

/* Funkcija error_fatal() ispisuje poruku o gresci i potom prekida program. */
void error_fatal(char *format, ...);

/* Funkcija titleScreen brise trenutni sadzraj sa ekrana u terminalu zbog lepseg prikaza */
void titleScreen();
void printPrompt();
void pressEnterToContinue();
void print_result(MYSQL_RES *result, int mark_order);

#endif

