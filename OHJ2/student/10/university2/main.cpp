//#include "utils.hh"
#include "cli.hh"
#include "university.hh"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>

/* Yliopisto
 *
 * ------------------------ Kuvaus: ------------------------
 *
 * Yliopisto ohjelma on yksinkertainen komentorivikäyttöliittymä yliopiston
 * kurssitarjonnan, opiskelija- tai opettaja-tilien ja opiskelijarekisterin
 * hallintaan. Se sisältää toiminnallisuuden uusien kurssien luomiseen,
 * henkilökunnan lisäämiseen kursseille, opiskelijoiden ilmoittautumisten
 * hallintaan, suoritettujen kurssien seurantaan ja opiskelijoiden valmistumisen
 * seurantaan.
 *
 * Ohjelman komennot on rakennettu pääsääntöisesti University-luokan päälle,
 * joka sisältää tietorakenteet Course- ja Account-objektien tallentamiseen.
 * Ohjelma ottaa syötteen komentojen ja parametrien muodossa ja
 * tulostaa tekstivastauksia konsoliin. Account- ja Course- luokat sisältävät
 * tietoa käyttäjjien tileistä ja kursseista, sekä mahdollistavat niiden
 * hallinnan. Jokaiselle käyttäjälle tai kurssille luodaan oma olio mitä
 * hallitaan metodeissa eri komentoja hyödyntäen. Luokka utils
 * toimii moduulina erilaisille ohjelmassa tarvittaville apuohjelmille, sekä
 * luokka cli toimii (esimerkki) komentorivinä käyttöliittymästä
 * funktioosoittimilla.
 *
 * Käyttäjälle aukeaa ikkuna mihin hän voi syöttää eri komentoja käyttötarpeen
 * mukaisesti.
 *
 * Kaiken kaikkiaan ohjelma mahdollistaa yliopiston akateemisten toimintojen
 * perushallinnan.
 *
 * ------------------------ Ohjelman kirjoittaja: ------------------------
 *
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 *
 * ------------------------ Komennot: ------------------------
 *
 * QUIT - Ohjelman suoritus päätty paluuarvoon EXIT_SUCCESS.
 *
 * NEW_ACCOUNT <koko nimi> - Komennolla voi lisätä yliopistoon opiskelijoita tai
 *                           henkilökuntaa.
 *
 * PRINT_ACCOUNT <henkilönumero> - Komento tulostaa annetun henkilön tiedot.
 *
 * PRINT_ACCOUNTS - Komento tulostaa kaikkien henkilöiden tiedot henkilönumeron
 *                  mukaisessa järjestyksessä.
 *
 * NEW_COURSE <koodi> <nimi> - Komennolla voi luoda uuden kurssin.
 *
 * ADD_STAFF <koodi> <henkilönumero> - Komento lisää annetulle kurssille annetun
 *                                     opettajan.
 *
 * PRINT_COURSE <koodi> - Komento tulostaa annetun kurssin tiedot.
 *
 * PRINT_COURSES - Komento tulostaa yliopiston kaikki kurssit kurssikoodin
 *                 mukaisessa aakkosjärjestyksessä.
 *
 * HELP - Jos komennolle ei anneta parametria, se tulostaa kaikki käytössä
 *        olevat komennot lyhenteineen.
 *
 * READ_FROM <tiedosto> - Komennolla voidaan lukea annetusta tiedostosta
 *                        komennot parametreineen.
 *
 * ------------------------ Toteutetut komennot: ------------------------
 *
 * SIGN_UP <koodi> <opiskelijanumero> - Komennolla annettu opiskelija voi
 *                                      ilmoittautua annetulle kurssille.
 *
 * COMPLETE <koodi> <opiskelijanumero> - Komennolla voidaan lisätä annetulle
 *                                       opiskelijalle suoritus annetusta
 *                                       kurssista.
 *
 * PRINT_STUDY_STATE <opiskelijanumero> - Komento tulostaa annetun opiskelijan
 *                                        opiskelutilanteen: ilmoittautumiset
 *                                        kursseille (meneillään olevat kurssit)
 *                                        suoritetut kurssit sekä suoritettujen
 *                                        kurssien opintopistemäärä yhteensä.
 *
 * PRINT_COMPLETED <opiskelijanumero> - Komento tulostaa annetun opiskelijan
 *                                      kurssisuoritukset ja
 *                                      kokonaisopintopistemäärän.
 *
 * PRINT_SIGNUPS <koodi> - Komento tulostaa annetulle kurssille ilmoittautuneet
 *                         opiskelijat.
 *
 * GRADUATE <opiskelijanumero> - Komennolla annettu opiskelija valmistuu
 *                               yliopistosta. Tällöin hänen kaikki kurssinsa
 *                               merkitään suoritetuiksi, eikä hän voi enää
 *                               ilmoittautua millekään kurssille.
 *
 * ------------------------ Muuta huomioitavaa: ------------------------
 *
 * Osassa koodipohjaa käytetään englantia ja osassa suomea. Suomeksi on
 * kirjoitettu kommentit, kun taas englantia on käytetty kaikessa muussa
 * olioiden kuvauksissa ja metodeista parametreihin. Ajatuksena oli kopioida
 * samaa tyyliä, että kieli pysyy samana ja jatkuvana tietyssä osiossa.
 * Ohjelman kirjoittaja on liitetty niihin osioihin mitä olen muokannut tai
 * tehtävänanto on maininnut, että tee muokkauksia näihin luokkiin. Joten missä
 * ei ole ohjelman kirjoittajaa liitetty, en ole itse tehnyt tai muokannut.
 * Samoin kuvausten ja kommenttien jättäminen kyseisistä osioista on jätetty
 * pois minun osaltani, vaikka siellä on valmiinpohjan tekstit.
 *
 * Myös koodi on rajattu 80 merkkiin, mikä on kurssin toteutuksessa
 * toivottu rajoitus. Koodi saattaa olla osittain siis hankalaa lukea, mutta
 * olen pyrkinyt seuraamaan tätä toivomusta. 80 merkin rajoitusta ei ole
 * korjattu luokkiin tai koodiin mitä ollaan ohjeistettu, että ei muokata.
 *
 * Olen myös jättänyt valmiit kuvaukset jos ne ovat olleet valmiina. Jäi
 * epäselväksi olisiko niitäkin pitänyt muokata.
 *
 * */

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

