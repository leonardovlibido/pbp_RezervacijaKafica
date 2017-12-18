use RezervacijaKafica;

insert into Korisnik ( idKorisnik, JMBG, ime, prezime, username, password, `e-mail` ) values
( 1, '2201986710312', 'Filip', 'Marjanovic', 'fica007', '123456', 'fica@gmail.com'),
( 2, '1203993711482', 'Marijana', 'Filipovic', 'jana001', 'abcdef', 'jana@gmail.com'),
( 3, '1105998711512', 'Jelena', 'Jelenic', 'jela', 'unutra', 'jela@gmail.com')
;

insert into Kafic ( idKafic, ime, ulica, brojUlice, radnoVremeRadniDan, radnoVremeVikend, ukupanBrStolova, brSlobodnihStolova, brZauzetihStolova ) values
( 1, 'Verona', 'Kraljice Natalije', '37', '10:00-00:00', '12:00-02:00', 12, 12, 0),
( 2, 'Rolling Barrel', 'Knjeginje Ljubice','26', '10:00-00:00', '08:00-00:00', 10, 10, 0)
;


insert into Konobar ( idKonobar, JMBG, ime, prezime, username, password ) values
    ( 1, '1203956710234', 'Konan', 'Baric', 'kon123', '321' ),
    ( 2, '0304556711724', 'Kristina', 'Bakic', 'kri451', '666' ),
    ( 3, '2203956711154', 'Tijana', 'Jelic', 'tij943', '999')
;


insert into Sto ( redniBroj, trenutnoStanje, brojMesta, Kafic_idKafic) values
    ( 1, 'slobodno', 3, 1 ),
    ( 2, 'slobodno', 3, 1 ),
    ( 3, 'slobodno', 4, 1 ),
    ( 4, 'slobodno', 4, 1 ),
    ( 5, 'slobodno', 5, 1 ),
    ( 6, 'slobodno', 6, 1 ),
    ( 1, 'slobodno', 3, 2 ),
    ( 2, 'slobodno', 3, 2 ),
    ( 3, 'slobodno', 3, 2 ),
    ( 4, 'slobodno', 3, 2 ),
    ( 5, 'slobodno', 5, 2 ),
    ( 6, 'slobodno', 5, 2 )
;

insert into Ocena ( Korisnik_idKorisnik, Kafic_idKafic, brZvezdica) values
    ( 1, 1, 4 ),
--    ( 1, 2, 5 ),
    ( 2, 1, 3 ),
    ( 2, 2, 5 ),
    ( 3, 2, 4 )
;

insert into zaposlen ( Konobar_idKonobar , Kafic_idKafic ) values
    ( 1, 1 ),
    ( 1, 2 ),
    ( 2, 1 ),
    ( 3, 2 )
;


insert into Rezervacije ( datum, vreme, brLjudi, Korisnik_idKorisnik, Kafic_idKafic ) values
    ( '2017-12-21', '18:00', 5, 1, 1 ),
    ( '2017-12-22', '19:00', 3, 2, 2 ),
    ( '2017-12-19', '19:00', 4, 3, 2 ),
    ( '2017-12-20', '20:00', 3, 3, 2 )
;


insert into Odobrava ( Rezervacije_idRezervacije, Konobar_idKonobar ) values 
    ( 1, 1 ),
    ( 2, 1 ),
    ( 3, 3 )
;


insert into biraSto ( Odobrava_Rezervacije_idRezervacije, Sto_redniBroj, Sto_Kafic_idKafic ) values
    ( 1, 5, 1 ), 
    ( 2, 1, 2 ),
    ( 3, 6, 2 )
;


