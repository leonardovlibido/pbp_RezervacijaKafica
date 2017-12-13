#ifndef KONOBAR_H
#define KONOBAR_H

#include <mysql/mysql.h>


int prijaviKonobara( MYSQL *connection );
void konobarAkcije( MYSQL *connection, int idKonobara );

#endif

