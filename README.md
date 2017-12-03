# Baza Podataka Za Rezervaciju Kafica


## Opis problema

Baza podataka za rezervaciju kafica sluzi kao podrska informacionom sistemu za rezervaciju mesta u kaficima.

U bazi se cuvaju informacije **korisnika** koji imaju pravo da rezervisu mesto u nekom od kafica. Svakog korisnika karakterise JMBG, ime, prezime, username, password, e-mail, broj rezervacija koje je ispostovao, i broj rezervacija na koje se nije pojavio, kao i procentualna vrednost dolaska na rezervisana mesta.

Za **kafic** se prati sifra kafica, ime kafica, ulica i broj, mesto u kom se nalazi, radno vreme radnim danima, radno vreme vikendom, broj stolova koji se mogu rezervisati, trenutni broj slobodnih stolova, trenutni broj rezervisanih stolova. Svaki kafic moze imati jedan ili vise stolova, a svaki **sto** pripada samo jednom kaficu. Za sto se cuva trenutno stanje, koje moze biti _rezervisano_, ili _slobodno_, broj mesta stola, i po potrebi dodatne infrmacije.

**Konobar** se odlikuje JMBG-om, imenom i prezimenom. Konobar moze raditi u jednom ili vise kafica, i kafic moze zaposljavati jednog ili vise konobara.

**Rezervaciju** karakterise datum i vreme rezervacije kao i broj ljudi koji ce doci, rezervaciju moze rezervisati tacno jedna osoba, a svaka osoba moze rezervisati vise rezervacija. Rezervacija vazi za tacno jedan kafic, a u jednom kaficu se moze napraviti jedna ili vise rezervacija. Svaku rezervaciju odobrava tacno jedan konobar, a konobar moze odobriti nijednu ili vise rezervacija. Prilikom odobravanja rezervacije, konobar dodeljuje prikladni sto za rezervaciju.

Kafic se moze **oceniti** od strane korisnika. Korisnik moze oceniti nijedan ili vise kafica, a svaki kafic moze biti ocenjen od strane nijednog ili vise korisnika. Ocenu opisujemo brojem zvezdica kafica sto opisuje nivo usluge, kao i dodatni komentar za detaljno obrazlozenje date ocene.

---

## Trigeri nad bazom

- azuriranjeOcena:
  Nakon unosa ocene korisnika za odredjeni kafic, azurira se ocena kafica, koja predstavlja srednju vrednost svih ocena kafica.
- azuriranjeStanjaStolova:
  Nakon unosenja nove rezervacije menja se trenutno stanje stola koji je dodeljen rezervaciji, kao i ukupan broj rezervisanih i ukupan broj slobodnih stolova datog kafica.

---
## Entiteti

- Nezavisni entiteti:
    - Kafici
    - Korisnici
    - Konobari
    - Rezervacije
- Zavisni entiteti:
    - sto
- Agregirani entiteti:
    - ocena
    - zaposlen
