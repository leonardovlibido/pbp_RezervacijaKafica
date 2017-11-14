#ifndef KONOBAR_H
#define KONOBAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "util.h"

int prijaviKonobara( MYSQL *connection );
void konobarAkcije( MYSQL *connection, int idKonobara );

#endif

