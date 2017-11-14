#ifndef KORISNIK_H
#define KORISNIK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "util.h"

int prijaviKorisnika( MYSQL *connection );
void korisnikAkcije( MYSQL *connection, int idKorisnika );

#endif

