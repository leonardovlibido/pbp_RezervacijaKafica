#ifndef KONOBAR_H
#define KONOBAR_H

#include <mysql/mysql.h>


int prijaviKonobara( MYSQL *connection );
void konobarAkcije( MYSQL *connection, int idKonobara );
int izaberiKafic( MYSQL *connection, int idKonobara);
void izlistajRezervacijePoKaficu( MYSQL *connection, int idKafica);
void obradiRezervacijuNaCekanju( MYSQL *connection, int idKonobara, int idKafica);
void izlistajSlobodneStolove( MYSQL *connection, int idKafica);

#endif

