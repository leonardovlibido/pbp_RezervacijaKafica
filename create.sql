-- MySQL Script generated by MySQL Workbench
-- Sun 10 Dec 2017 19:09:32 CET
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema RezervacijaKafica
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema RezervacijaKafica
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `RezervacijaKafica` DEFAULT CHARACTER SET utf8 ;
USE `RezervacijaKafica` ;

-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Korisnik`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Korisnik` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Korisnik` (
  `idKorisnik` INT NOT NULL,
  `JMBG` VARCHAR(13) NOT NULL,
  `ime` VARCHAR(45) NOT NULL,
  `prezime` VARCHAR(45) NOT NULL,
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `e-mail` VARCHAR(45) NOT NULL,
  `ukupanBrRezervacija` INT NOT NULL DEFAULT 0,
  `brIspostovanihRezerevacija` INT NOT NULL DEFAULT 0,
  `brOtkazanihRezervacija` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`idKorisnik`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Kafic`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Kafic` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Kafic` (
  `idKafic` INT NOT NULL,
  `ime` VARCHAR(45) NOT NULL,
  `ulica` VARCHAR(45) NOT NULL,
  `brojUlice` VARCHAR(10) NOT NULL,
  `radnoVremeRadniDan` VARCHAR(12) NOT NULL,
  `radnoVremeVikend` VARCHAR(12) NOT NULL,
  `ukupanBrStolova` INT NOT NULL,
  `brSlobodnihStolova` INT NOT NULL,
  `brZauzetihStolova` INT NOT NULL,
  PRIMARY KEY (`idKafic`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Konobar`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Konobar` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Konobar` (
  `idKonobar` INT NOT NULL,
  `JMBG` VARCHAR(13) NOT NULL,
  `ime` VARCHAR(45) NOT NULL,
  `prezime` VARCHAR(45) NOT NULL,
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idKonobar`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Sto`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Sto` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Sto` (
  `redniBroj` INT NOT NULL,
  `trenutnoStanje` VARCHAR(45) NOT NULL,
  `brojMesta` INT NOT NULL,
  `dodatneIfnormacije` TEXT NULL DEFAULT NULL,
  `Kafic_idKafic` INT NOT NULL,
  PRIMARY KEY (`redniBroj`, `Kafic_idKafic`),
  INDEX `fk_Sto_Kafic1_idx` (`Kafic_idKafic` ASC),
  CONSTRAINT `fk_Sto_Kafic1`
    FOREIGN KEY (`Kafic_idKafic`)
    REFERENCES `RezervacijaKafica`.`Kafic` (`idKafic`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Ocena`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Ocena` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Ocena` (
  `Korisnik_idKorisnik` INT NOT NULL,
  `Kafic_idKafic` INT NOT NULL,
  `brZvezdica` INT NOT NULL,
  `komentar` TEXT NULL DEFAULT NULL,
  PRIMARY KEY (`Korisnik_idKorisnik`, `Kafic_idKafic`),
  INDEX `fk_Korisnik_has_Kafic_Kafic1_idx` (`Kafic_idKafic` ASC),
  INDEX `fk_Korisnik_has_Kafic_Korisnik_idx` (`Korisnik_idKorisnik` ASC),
  CONSTRAINT `fk_Korisnik_has_Kafic_Korisnik`
    FOREIGN KEY (`Korisnik_idKorisnik`)
    REFERENCES `RezervacijaKafica`.`Korisnik` (`idKorisnik`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Korisnik_has_Kafic_Kafic1`
    FOREIGN KEY (`Kafic_idKafic`)
    REFERENCES `RezervacijaKafica`.`Kafic` (`idKafic`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`zaposlen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`zaposlen` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`zaposlen` (
  `Konobar_idKonobar` INT NOT NULL,
  `Kafic_idKafic` INT NOT NULL,
  PRIMARY KEY (`Konobar_idKonobar`, `Kafic_idKafic`),
  INDEX `fk_Konobar_has_Kafic_Kafic1_idx` (`Kafic_idKafic` ASC),
  INDEX `fk_Konobar_has_Kafic_Konobar1_idx` (`Konobar_idKonobar` ASC),
  CONSTRAINT `fk_Konobar_has_Kafic_Konobar1`
    FOREIGN KEY (`Konobar_idKonobar`)
    REFERENCES `RezervacijaKafica`.`Konobar` (`idKonobar`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Konobar_has_Kafic_Kafic1`
    FOREIGN KEY (`Kafic_idKafic`)
    REFERENCES `RezervacijaKafica`.`Kafic` (`idKafic`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Rezervacije`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Rezervacije` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Rezervacije` (
  `idRezervacije` INT NOT NULL,
  `datum` DATE NOT NULL,
  `vreme` TIME NOT NULL,
  `brLjudi` INT NOT NULL,
  `Korisnik_idKorisnik` INT NOT NULL,
  `Kafic_idKafic` INT NOT NULL,
  PRIMARY KEY (`idRezervacije`),
  INDEX `fk_Rezervacije_Korisnik1_idx` (`Korisnik_idKorisnik` ASC),
  INDEX `fk_Rezervacije_Kafic1_idx` (`Kafic_idKafic` ASC),
  CONSTRAINT `fk_Rezervacije_Korisnik1`
    FOREIGN KEY (`Korisnik_idKorisnik`)
    REFERENCES `RezervacijaKafica`.`Korisnik` (`idKorisnik`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Rezervacije_Kafic1`
    FOREIGN KEY (`Kafic_idKafic`)
    REFERENCES `RezervacijaKafica`.`Kafic` (`idKafic`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`Odobrava`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`Odobrava` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`Odobrava` (
  `Rezervacije_idRezervacije` INT NOT NULL,
  `Konobar_idKonobar` INT NOT NULL,
  PRIMARY KEY (`Rezervacije_idRezervacije`),
  INDEX `fk_Rezervacije_has_Konobar_Konobar1_idx` (`Konobar_idKonobar` ASC),
  INDEX `fk_Rezervacije_has_Konobar_Rezervacije1_idx` (`Rezervacije_idRezervacije` ASC),
  CONSTRAINT `fk_Rezervacije_has_Konobar_Rezervacije1`
    FOREIGN KEY (`Rezervacije_idRezervacije`)
    REFERENCES `RezervacijaKafica`.`Rezervacije` (`idRezervacije`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Rezervacije_has_Konobar_Konobar1`
    FOREIGN KEY (`Konobar_idKonobar`)
    REFERENCES `RezervacijaKafica`.`Konobar` (`idKonobar`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RezervacijaKafica`.`biraSto`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RezervacijaKafica`.`biraSto` ;

CREATE TABLE IF NOT EXISTS `RezervacijaKafica`.`biraSto` (
  `Odobrava_Rezervacije_idRezervacije` INT NOT NULL,
  `Sto_redniBroj` INT NOT NULL,
  `Sto_Kafic_idKafic` INT NOT NULL,
  PRIMARY KEY (`Sto_redniBroj`, `Sto_Kafic_idKafic`),
  INDEX `fk_Odobrava_has_Sto_Sto1_idx` (`Sto_redniBroj` ASC, `Sto_Kafic_idKafic` ASC),
  INDEX `fk_Odobrava_has_Sto_Odobrava1_idx` (`Odobrava_Rezervacije_idRezervacije` ASC),
  CONSTRAINT `fk_Odobrava_has_Sto_Odobrava1`
    FOREIGN KEY (`Odobrava_Rezervacije_idRezervacije`)
    REFERENCES `RezervacijaKafica`.`Odobrava` (`Rezervacije_idRezervacije`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Odobrava_has_Sto_Sto1`
    FOREIGN KEY (`Sto_redniBroj` , `Sto_Kafic_idKafic`)
    REFERENCES `RezervacijaKafica`.`Sto` (`redniBroj` , `Kafic_idKafic`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
