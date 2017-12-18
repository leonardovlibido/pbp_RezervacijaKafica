#ifndef KORISNIK_H
#define KORISNIK_H

#include <mysql/mysql.h>

int prijaviKorisnika( MYSQL *connection );
void korisnikAkcije( MYSQL *connection, int idKorisnika );
void izlistajKafice( MYSQL *connection);
void oceniKafic( MYSQL *connection, int idKorisnika );
void rezervisiKafic( MYSQL *connection, int idKorisnika);
void izlistajRezervacije( MYSQL *connection, int idKorisnika);

#endif


