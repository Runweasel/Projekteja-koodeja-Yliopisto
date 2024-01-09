#include "mainwindow.hh"

#include <QApplication>


/* Polku -peli
 *
 * ------------------------ Kuvaus: ------------------------
 *
 * Koodi toteuttaa Polku -pelin graafisen käyttöliittymän tuoden siihen lisää
 * toiminnallisuuksia ja ominaisuuksia. Koodi perustuu annettuun pohjakoodiin
 * ,mikä sisältää pelin logiikan ja säännöt. Ohjelma koostuu pääasiassa
 * MainWindow luokasta, mikä luo käyttäjälle näkymän ruudulle.
 * Toiminnallisuuksia on pelilaudan luominen, ajastimen asettaminen ja
 * päivittäminen, siirtojen suorittaminen, tulostaulun lukeminen ja
 * kirjoittaminen tiedostoon ja näytölle, sekä erilaisten käyttöliittymä
 * painikkeiden toiminnallisuuksien käsittelyä.
 *
 * Käyttäjä kykenee toimimaan ohjelman kanssa käyttöliittymän kautta.
 *
 * Pelin säännöt, käyttöohjeet ja tarkempi kuvaus ja toiminnallisuus löytyvät
 * annetusta tiedostosta: instructions.txt
 *
 * ------------------------ Ohjelman kirjoittaja: ------------------------
 *
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 *
 * ------------------------ Muuta huomioitavaa: ------------------------
 *
 * Koodi on kirjoitettu englanniksi, jotta yhteläisyys pysyys muun koodin
 * ja annetunpohjan kanssa. Kuitenkin tekstit, kommentit ja kuvaukset on
 * kirjoitettu suomeksi, koska palautus on suomeksi. Tämän seurauksena
 * molempia kieliä löytyy koodista. Ehkä se helpottaa myös seurata mihin
 * olen tehnyt itse muutoksia valmiiseenpohjaan.
 *
 * Pyrin toteuttamaan 80 merkin rajaa hyödyntäen, koska sitä on toivottu
 * kurssin ohjeistuksessa. Jossain kohdin koodi saattaa olla vaikeammin
 * ymmärrettävää, koska se on katkaistu 80 merkin kohdalla, mutta pyrin
 * silti tekemään siitä selkeää ja menemään ohjeistuksen mukaisesti.
 *
 * */

int main(int argc, char *argv[])
{
    qRegisterMetaType<Point>("Point");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
