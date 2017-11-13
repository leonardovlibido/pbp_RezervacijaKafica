delimiter $$

drop trigger if exists azuriraj_ocene $$

create trigger azuriraj_ocene after insert on Ocena
for each row begin
    update Kafic set ocena = (
        select avg(brZvezdica)
        from Ocena
        where Ocena.Kafic_idKafic = Kafic.idKafic
    );
end$$


drop trigger if exists azuriranje_stanja_stolova $$

create trigger azuriranje_stanja_stolova after insert on biraSto
for each row begin
    update Kafic set
        brSlobodnihStolova = brSlobodnihStolova - 1,
        brZauzetihStolova = brZauzetihStolova + 1;
end $$

