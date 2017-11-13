
.PHONY: all create insert

all: create insert

create:
	mysql -u root -p -D mysql <src/create.sql

insert:
	mysql -u root -p -D mysql <src/insert.sql

