CC		= gcc
CFLAGS	= -Wall -Wextra
CCLIBS	= -lmysqlclient
PROGRAM	= rezervacijaKafica

DEPS	=			\
		util.h		\
		korisnik.h	\
		konobar.h	

OBJ		=			\
		app.o		\
		util.o		\
		korisnik.o	\
		konobar.o

VPATH	= src


.PHONY: all create insert

all: create triggers insert $(PROGRAM)

create:
	mysql -u root --password= -D mysql <src/create.sql

triggers:
	mysql -u root --password= -D mysql <src/triggers.sql

insert:
	mysql -u root --password= -D mysql <src/insert.sql


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)

