#ifndef KORISNIK_H
#define KORISNIK_H

#include <mysql/mysql.h>

int prijaviKorisnika( MYSQL *connection );
void korisnikAkcije( MYSQL *connection, int idKorisnika );

#endif

