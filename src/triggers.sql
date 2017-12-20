use RezervacijaKafica;

delimiter $$



drop trigger if exists ocena_check_interval_insert $$

create trigger ocena_check_interval_insert before insert on Ocena
for each row begin
    if new.brZvezdica > 5 or new.brZvezdica < 1 then
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Los broj zvezdica';
    end if;
end $$



drop trigger if exists ocena_check_interval_update $$

create trigger ocena_check_interval_update before update on Ocena
for each row begin
    if new.brZvezdica > 5 or new.brZvezdica < 1 then
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Los broj zvezdica';
    end if;
end $$
        


drop trigger if exists azuriraj_ocene $$

create trigger azuriraj_ocene after insert on Ocena
for each row begin
    update Kafic set ocena = (
        select avg(brZvezdica)
        from Ocena
        where Ocena.Kafic_idKafic = Kafic.idKafic
    );
end $$



drop trigger if exists azuriraj_ocene_update $$

create trigger azuriraj_ocene_update after update on Ocena
for each row begin
    update Kafic set ocena = (
        select avg(brZvezdica)
        from Ocena
        where Ocena.Kafic_idKafic = Kafic.idKafic
    );
end $$



drop trigger if exists azuriranje_statusa_rezervacije $$

create trigger azuriranje_statusa_rezervacije after insert on Odobrava
for each row begin
	update Rezervacije set
		status = "odobrena"
	where new.Rezervacije_idRezervacije = Rezervacije.idRezervacije;
end $$



drop trigger if exists azuriranje_stanja_stolova $$

create trigger azuriranje_stanja_stolova after insert on biraSto
for each row begin
    update Kafic set
        brSlobodnihStolova = brSlobodnihStolova - 1,
        brZauzetihStolova = brZauzetihStolova + 1
		where new.Sto_Kafic_idKafic = Kafic.idKafic;
	update Sto set
		trenutnoStanje = 'zauzet'
		where new.Sto_Kafic_idKafic = Sto.Kafic_idKafic and new.Sto_redniBroj = Sto.redniBroj;
end $$



drop trigger if exists azuriranje_ukupnog_broja_rezervacija_korisnika $$

create trigger azuriranje_ukupnog_broja_rezervacija_korisnika after insert on Rezervacije
for each row begin
	update Korisnik set
		ukupanBrRezervacija = ukupanBrRezervacija + 1
	where new.Korisnik_idKorisnik = Korisnik.idKorisnik;
end $$


drop trigger if exists azuriranje_stanja_stolova2 $$

create trigger azuriranje_stanja_stolova2 before delete on biraSto
for each row begin
    update Kafic set
        brSlobodnihStolova = brSlobodnihStolova + 1,
        brZauzetihStolova = brZauzetihStolova + 1
        where old.Sto_Kafic_idKafic = Kafic.idKafic;
    update Sto set
        trenutnoStanje = 'slobodno'
        where old.Sto_Kafic_idKafic = Sto.Kafic_idKafic and old.Sto_redniBroj = Sto.redniBroj;
end $$


delimiter ;
