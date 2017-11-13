
.PHONY: all create insert

all: create triggers insert

create:
	mysql -u root -p -D mysql <src/create.sql

triggers:
	mysql -u root -p -D mysql <src/triggers.sql

insert:
	mysql -u root -p -D mysql <src/insert.sql

