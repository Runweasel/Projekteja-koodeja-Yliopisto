#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>

/* Kirjasto
 *
 * Kuvaus:
 * Ohjelma toteuttaa kirjasto ohjelman eli kirjastojen kirjojen käyttöliittymän,
 * jossa sovelletaan hakualgoritmia hakemaan syötetiedostosta kirjastojen kirjat
 * ja lisätään ne sitten tietorakenteeseen. Tietorakenteesta haetaan käyttäjän
 * syöttämien komentojen perusteella haluttuja kirjoja, ja tulostetaan ne
 * käyttäjälle näkyviin komentojen perusteella.
 * Ohjelma ensiksi kysyy käyttäjältä syötetiedostoa mihin on tallennettuna
 * kirjasto ja niiden sisällä olevat kirjat, joille on annettu tiedot:
 * kirjailija, kirjan nimi ja varaukset. Jokainen tieto on ';'
 * merkillä eroteltuna. Mikäli syötiedosto on virheellinen, ohjelma ilmoittaa
 * siitä ja lopettaa toimintansa. Kun käyttäjä on syöttänyt toimivan
 * syötetiedoston, hän voi syöttää jonkin seuraavista komennoista,
 * quit, libraries, material, books, reservable tai loanable.
 * Virheellisessä komennossa käyttäjälle ilmoitetaan virheviesti ja hän voi
 * syöttää uudelleen, kunnes lopettaa ohjelman toiminnan.
 * Jokaisella komennolla on myös oletuksena tietty määrä parametrejä mitä
 * käyttäjä syöttää, ja jos parametrien määrä ei vastaa, käyttäjälle
 * ilmoitetaan virheviestillä.
 *
 *                 Komennot:
 *
 * quit:       Lopettaa ohjelman toiminnan.
 *
 * libraries:  Tulostaa tallennetut kirjastot aakkosjärjestyksessä.
 *
 * material:   Tulostaa aakkosjärjestyksessä allekkain kaikki annetun
 *             kirjaston kirjat.
 *
 * books:      Tulostaa kirjan nimen mukaisessa aakkosjärjestyksessä kaikki
 *             kyseinen tekijän kirjat, jotka löytyvät kyseisestä kirjastosta.
 *
 * reservable: Tulostaa lyhyimmän varausjonon halutun tekijän halutulle
 *             kirjalle ja sen alle aakkosjärjestyksessä kirjastot, joista
 *             löytyy kirja samanpituisella varausjonolla.
 *
 * loanable:   Tulostaa kaikkien kirjastojen kaikista kirjoista ne,
 *             jotka löytyvät hyllystä, aakkosjärjestyksessä ensiksi tekijän
 *             mukaan ja sitten teosten mukaan.
 *
 * Kun käyttäjän syöttämä komento on suoritettu, ohjelma tulostaa
 * kehotteen uudelleen. Tätä jatketaan kunnes käyttäjä syöttää käskyn quit.
 *
 *                 Ohjelman kirjoittajat:
 *
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 *
 * Nimi: Aura Porkka
 * Opiskelijanumero: 150181031
 * Käyttäjätunnus: ntaupo
 * E-mail: aura.porkka@tuni.fi
 *
 *
 *                 Muuta huomioitavaa:
 *
 * Koodissa on huomioitu 80 merkin raja, joka saattaa tehdä osasta riveistä
 * vaikeammin tulkittavia, mutta koska se on toivottu niin käytämme sitä.
 *
 * KIRJASTOVERRKO -tietorakenne on nimetty isoilla kirjaimilla, jotta sitä
 * olisi helppo seurata muiden samankaltaisten nimien joukossa ja se pysyy
 * vakiona ensimmäisen alustamisen jälkeen. Ilmeisesti se ei kuitenkaan ole
 * yleinen käytäntö.
 *
 * */

using namespace std;

struct Book
{
    string author;
    string title;
    int reservations;
};

struct SallitutKomennot {
    vector<string> komennot = {"quit", "libraries", "material",
                               "books", "loanable", "reservable"};
};

const int ODOTETTU_KENTTAMAARA_RIVILLA = 4;
const int VARAUSJONO_MAX = 100;

/*
 * Funktio 'jako_osiin' ottaa vastaan kolme parametria: merkkijonon "s", jonka
 * haluat jakaa osiin, erotinmerkin "erotin", jonka avulla merkkijono halutaan
 * jakaa osiin, ja bool-tietotyypin "ohita_tyhja", jonka oletusarvo on false.
 *
 * Funktio käy läpi merkkijonon "s" kaikki esiintymät erotinmerkin "erotin"
 * kohdalta käyttäen while-silmukkaa ja jakaa sen osiin substr()-funktiota
 * käyttäen. Jos parametri "ohita_tyhja" on true, tyhjät osat jätetään pois
 * tulosvektorista. Lopuksi funktio tarkistaa vielä, onko viimeinen osa
 * tyhjä, jos parametri "ohita_tyhja" on true, ja jos ei, se lisätään
 * tulosvektoriin.
 *
 * Funktio palauttaa vektorin, joka sisältää
 * merkkijonon "s" kaikki erotinmerkin perusteella jaetut osat.
 * */

vector<string> jako_osiin( const string& syote, const char erotin,
                          bool ohita_tyhja = false ){

    vector<string> tulos = {};
    string tmp = syote;

    while(tmp.find(erotin) != string::npos)
    {
        string uusi_osa = tmp.substr(0, tmp.find(erotin));
        tmp = tmp.substr(tmp.find(erotin)+1, tmp.size());
        if( not (ohita_tyhja and uusi_osa.empty()) )
        {
            tulos.push_back(uusi_osa);
        }
    }
    if( not (ohita_tyhja and tmp.empty()) )
    {
        tulos.push_back(tmp);
    }
    return tulos;
}

/*
 * Funktio 'virhetarkastelu' saa parametreinä kirjastojen_kirjat, joka sisältää
 * map-rakenteessa kirjastot ja niiden kirjat. Lisäksi funktio saa
 * parametreinä kaksi merkkijonoa kirjasto ja kirjailija, jotka ovat
 * oletuksena tyhjiä.
 *
 * Funktio tarkistaa ja vertaa annettuja tietoja map-tietorakenteeseen
 * ja tulostaa käyttäjälle virheilmoituksen mikäli annettu parametri
 * ei täsmää. Funktio keskeyttää toimintansa ensimmäisen virheen
 * löytyessä. Funktio myös tutkii onko map-tietorakenteessa tietoja ja
 * jos se on tyhjä, tulostetaan virheilmoitus.
 *
 * Virhetarkastelu funktiota hyödyntää main-funktion komennot ja niiden
 * rakentamaa tietorakennetta tarkastellaan täällä.
 * */

void virhetarkastelu( map<string, vector<Book>> kirjastojen_kirjat,
                     string kirjasto = "", string kirjailija = "" ) {

    bool kirjasto_ok = false;
    bool kirjailija_ok = false;

    // Tarkistaa, onko syötetty kirjasto kelvollinen
    if (kirjasto != "") {
        for (auto const& [nimi, kirjat] : kirjastojen_kirjat) {
            if (nimi == kirjasto) {
                kirjasto_ok = true;
                break;
            }
        }
        if (!kirjasto_ok) {
            cout << "Error: unknown library" << endl;
            return;
        }
    }
    // Tarkistaa, onko syötetty kirjailija kelvollinen
    if (kirjailija != "") {
        for (auto const& [nimi, kirjat] : kirjastojen_kirjat) {
            for (auto const& kirja : kirjat) {
                if (kirja.author == kirjailija) {
                    kirjailija_ok = true;
                    break;
                }
            }
            if (kirjailija_ok) {
                break;
            }
        }
        if (!kirjailija_ok) {
            cout << "Error: unknown author" << endl;
            return;
        }
    }
    if ( kirjastojen_kirjat.empty() ) {
        cout << "Book is not a library book" << endl;
        }
}

/*
 * Funktio 'onko_parametrien_maara_oikea' ottaa vastaan kolme parametria:
 * unsigned long -tyyppisen parametrin "parametrien_maara", joka kertoo
 * komentoriviparametrien määrän, unsigned long -tyyppisen parametrin
 * "odotettu_parametrien_maara", joka kertoo odotetun komentoriviparametrien
 * määrän, ja bool-tietotyypin parametrin "vahimmais_maara", jonka
 * oletusarvo on false.
 *
 * Funktio tarkistaa, onko komentoriviparametrien määrä yhtäsuuri kuin
 * odotettu_parametrien_maara + 1. Jos "vahimmais_maara" on true,
 * tarkistetaan, että parametrien määrä on suurempi tai yhtä suuri
 * kuin odotettu_parametrien_maara + 1.
 *
 * Jos tarkistus menee läpi, funktio palauttaa true. Muussa tapauksessa
 * funktio tulostaa virheilmoituksen
 * "Error: wrong number of parameters" ja palauttaa false.
 * */

bool onko_parametrien_maara_oikea( unsigned long parametrien_maara,
                                  unsigned long odotettu_parametrien_maara,
                                  bool vahimmais_maara = false ) {

    // Lisätään +1, jotta huomioidaan itse komento. Mainissa on helpompi
    // lukea mikä on syötteen, pois lukien komennon, parametrien määrä.

    if ( vahimmais_maara == true ) {
        if (parametrien_maara >= odotettu_parametrien_maara + 1) {
            return true;
    } else {
            cout << "Error: wrong number of parameters" << endl;
            return false;
        }
    }

    if (parametrien_maara == odotettu_parametrien_maara + 1) {
        return true;
    } else {
        cout << "Error: wrong number of parameters" << endl;
        return false;
    }
}

/*
 * Funktion 'kirjastoverkon_haku' parametrit ovat kaksi merkkijonoa "kirjasto"
 * ja "tekija", ja "KIRJASTOVERKKO", joka on tyyppiä "map<string, vector<Book>>"
 *
 * Funktio suorittaa erilaisia hakutoimintoja riippuen annetuista
 * parametreista. Jos parametrit "kirjasto" ja "tekija"
 * ovat molemmat tyhjiä, funktio palauttaa kaikki kirjastot.
 * Jos parametri "kirjasto" on annettu, mutta "tekija" on tyhjä,
 * funktio palauttaa kirjaston sisällön.
 * Jos "kirjasto" ja "tekija" on molemmat annettu,
 * funktio palauttaa vain ne kirjat, jotka ovat tietyltä tekijältä ja
 * tietystä kirjastosta.
 *
 * Funktio palauttaa map-tyyppisen rakenteen, joka sisältää kirjastojen
 * nimiä ja kirjoja niiden sisällä.
 * */

map<string, vector<Book>> kirjastoverkon_haku(
        map<string, vector<Book>>& KIRJASTOVERKKO,
        const string& kirjasto="", const string& tekija="" ) {

    map<string, vector<Book>> haetut_tiedot = {};

    if (kirjasto == "" && tekija == "") {
        for (const auto& kirjasto_nimi : KIRJASTOVERKKO) {
            haetut_tiedot.insert(kirjasto_nimi);
        }

    } else if (kirjasto != "" && tekija == "") {
        if (KIRJASTOVERKKO.find(kirjasto) != KIRJASTOVERKKO.end()) {
            haetut_tiedot[kirjasto] = KIRJASTOVERKKO.at(kirjasto);
        }

    } else if (kirjasto != "" && tekija != "") {
        if (KIRJASTOVERKKO.find(kirjasto) != KIRJASTOVERKKO.end()) {
            vector<Book> tekijan_kirjat;
            for (const auto& kirja : KIRJASTOVERKKO.at(kirjasto)) {
                if (kirja.author == tekija) {
                    tekijan_kirjat.push_back(kirja);
                }
            }
            haetut_tiedot[kirjasto] = tekijan_kirjat;
        }
    }
    return haetut_tiedot;
}

/*
 * Funktion 'useampi_kirjastoverkon_haku' parametreina on kirjastot map<string,
 * vector<Book>> - tietorakenne, joka sisältää eri kirjastojen nimet ja
 * niiden kokoelmat vector<Book> -muodossa.
 * kirjailija string (oletusarvo: tyhjä merkkijono) - kirjailijan nimi,
 * jonka mukaan kirjoja haetaan. Jos tätä parametria ei
 * anneta, funktio palauttaa kaikki kirjat kirjastosta.
 * kirjan_nimi string (oletusarvo: tyhjä merkkijono) - kirjan nimi,
 * jonka mukaan kirjoja haetaan. Jos tätä parametria ei anneta,
 * funktio hakee kaikki kirjat, jotka liittyvät annettuun kirjailijaan.
 *
 * Funktio hakee usean kirjaston kirjoja 'kirjastot'- mapista, joko kirjailijan
 * nimen tai kirjan nimen perusteella kirjastoverkon_haku -funktiosta
 * ja lisää ne sitten haetut_tiedot muuttujaan.
 *
 * Funktio palauttaa haetut_tiedot map<string, vector<Book>> -muodossa
 * haetut kirjat kullekin kirjastolle ehtojen mukaisesti.
 * */

map<string, vector<Book>> useampi_kirjastoverkon_haku( map<string,
                                                      vector<Book>> kirjastot,
                                                      string kirjailija = "",
                                                      string kirjan_nimi = "" ){

    map<string, vector<Book>> haetut_tiedot = {};

    for ( const auto& kirjasto : kirjastot ) {
        map<string, vector<Book>> kirjat
                = kirjastoverkon_haku(kirjastot, kirjasto.first, kirjailija);
        for ( auto& kirja : kirjat.at(kirjasto.first) ) {

            if ( kirjan_nimi == "" ) {
                haetut_tiedot[kirjasto.first].push_back(kirja);
            }
            else {
                if (kirja.title == kirjan_nimi) {
                    haetut_tiedot[kirjasto.first].push_back(kirja);
            }
            }
    }
}
    return haetut_tiedot;
}

/*
 * Funktio 'kirjastojen_tulostus' tulostaa kaikki annetussa
 * map<string, vector<Book>> -rakenteessa olevat kirjastojen nimet.
 * Funktiolla on yksi parametri, haetut_tiedot,
 * joka on map-rakenne, joka sisältää kirjastojen nimet ja niiden
 * kirjakokoelmat vector<Book> -muodossa.
 *
 * Funktio tulostaa kirjastojen nimen, eli avaimet haetut_tiedot
 * tietorakenteesta.
 * */

void kirjastojen_tulostus( map<string, vector<Book>> haetut_tiedot ) {

    for (const auto& kirjastot : haetut_tiedot) {
        cout << kirjastot.first << endl;
    }
}

/*
 * Funktio 'kirjaston_kirjojen_tulostus' tulostaa kirjaston kirjoja
 * haetut_tiedot-mapista kirjailijan mukaan aakkosjärjestyksessä.
 * Funktiolla on yksi parametri,
 * haetut_tiedot map<string, vector<Book>> - tietorakenne, joka sisältää eri
 * kirjastojen nimet ja niiden kokoelmat vector<Book> -muodossa.
 *
 * Funktion toiminta on seuraava: Funktio käy läpi jokaisen kirjaston kirjat,
 * jotka on tallennettu haetut_tiedot-mapissa. Kirjat järjestetään jokaisen
 * kirjailijan kohdalla kirjailijan nimen mukaan aakkosjärjestykseen
 * käyttämällä sort-funktiota. Sen jälkeen tulostetaan jokaisen
 * kirjailijan kirjat
 * */

void kirjaston_kirjojen_tulostus( map<string, vector<Book>> haetut_tiedot ) {

    if ( haetut_tiedot.empty() ) {
        return;
        }

    for (auto& kirjasto : haetut_tiedot) {
        sort(kirjasto.second.begin(), kirjasto.second.end(),
             [](const Book& eka_kirja,
             const Book& toka_kirja) {
            return eka_kirja.author < toka_kirja.author;
        });
        for (const auto& kirja : kirjasto.second) {
            cout << kirja.author << ": " << kirja.title << endl;
        }
    }
}

/*
 * Funktio 'kirjailijan_kirjojen_tulostus' tulostaa kirjailijan kirjat, jotka
 * on tallennettu haetut_tiedot-mapissa. Funktiolla on yksi parametri,
 * haetut_tiedot: map<string, vector<Book>> - tietorakenne, joka sisältää
 * kirjailijan kirjat vector<Book>-muodossa.
 *
 * Funktion toiminta on seuraava: Funktion ensimmäinen tarkistus on, että
 * jos haetut_tiedot on tyhjä, funktio palaa takaisin, koska on turha jatkaa
 * toimintaa. Jos se ei ole tyhjä, funktio käy läpi jokaisen kirjan
 * haetut_tiedot-mapissa ja järjestää kirjat otsikon mukaan aakkosjärjestykseen
 * sort-funktiolla. Tämän jälkeen se käy läpi jokaisen kirjan ja tulostaa
 * kirjan nimen ja sen saatavuustiedon.
 * */

void kirjailijan_kirjojen_tulostus( map<string, vector<Book>> haetut_tiedot ) {

    if ( haetut_tiedot.empty() ) {
        return;
        }

    for (auto& kirjasto : haetut_tiedot) {
        sort(kirjasto.second.begin(), kirjasto.second.end(),
             [](const Book& eka_kirja,
             const Book& toka_kirja) {
            return eka_kirja.title < toka_kirja.title;
        });
        for (const auto& kirja : kirjasto.second) {
            if (kirja.reservations == 0) {
                cout << kirja.title << " --- " << "on the shelf" << endl;
            } else {
                cout << kirja.title << " --- " << kirja.reservations
                     << " reservations" << endl;
            }
        }
    }
}

/*
 * Funktiolla 'muodosta_kirjan_nimi_syotteesta' on parametreina, rivin_osat
 * vector<string> - tietorakenne, joka sisältää merkkijonon osat, joista kirjan
 * nimi muodostetaan.
 *
 * Funktio ottaa vektorin rivin_osat string-tyypin osista ja muodostaa niistä
 * kirjan nimen. Funktio huomioi myös heittomerkien käytön ja poistaa ne
 * mikäli ne on syötetty. Funktio toimii osana reservable-komentoa.
 *
 * Funktio palauttaa string-tyyppisen arvon, joka sisältää
 * muodostetun kirjan nimen.
 * */

string muodosta_kirjan_nimi_syotteesta( vector<string> rivin_osat ) {

    string kirjan_nimi = "";
    for (size_t i = 2; i < rivin_osat.size(); i++) {
        kirjan_nimi += rivin_osat.at(i);
        if (i != rivin_osat.size() - 1) {
            kirjan_nimi += " ";
        }
    }
    vector<string> jaettu_nimi = jako_osiin(kirjan_nimi, '"');
    if (jaettu_nimi.size() > 1) {
        kirjan_nimi = jaettu_nimi.at(1);
    }
    return kirjan_nimi;
}

/*
 * Funktio 'lyhimman_varausjonon_tulostus' tulostaa kirjaston,
 * jossa on lyhin varausjono kirjalle haetusta tiedoista, haetut_tiedot-mapista.
 * Funktiolla on parametreina,
 * haetut_tiedot map<string, vector<Book>> - tietorakenne, joka sisältää
 * kirjaston nimen ja sen kirjojen kokoelman vector<Book>-muodossa.
 *
 * Funktion toiminta on seuraava: Funktio käy läpi jokaisen kirjaston kirjat,
 * jotka on tallennettu haetut_tiedot-mapissa, ja etsii pienimmän varausjonon
 * pienin_varausjono -muuttujan avulla. Sitten se poistaa kaikki kirjat,
 * joiden varausjonot ovat suuremmat kuin pienin varausjono. Tämän jälkeen
 * funktio tulostaa pienimmän varausjonon ja sen kirjaston jossa se on.
 * Lopuksi funktio tulostaa kaikki kirjastot joilla on
 * kyseinen pienin varausjono kirjalle.
 *
 * Funktio ottaa myös huomioon jos haetut_tiedot on tyhjä, jolloin on turha
 * jatkaa toimintaa. Myös jos varausjono on yli 100, jolloin tulostetaan
 * ilmoitus käyttäjälle.
 * */

void lyhimman_varausjonon_tulostus( map<string, vector<Book>> haetut_tiedot ) {

    if ( haetut_tiedot.empty() ) {
        return;
        }

    int pienin_varausjono = VARAUSJONO_MAX;
    for (const auto& kirjastot : haetut_tiedot) {
        for (const auto& kirja : kirjastot.second) {
            if (kirja.reservations < pienin_varausjono) {
                pienin_varausjono = kirja.reservations;
            }
        }
    }

    for (auto& kirjastot : haetut_tiedot) {
        auto& kirjat = kirjastot.second;
        kirjat.erase(remove_if(kirjat.begin(), kirjat.end(),
                               [pienin_varausjono](const Book& kirja) {
            return kirja.reservations > pienin_varausjono;
        }), kirjat.end());
    }

    if ( pienin_varausjono == 0 ) {
        cout << "on the shelf" << endl;
    } else if ( pienin_varausjono >= VARAUSJONO_MAX) {
        cout << "Book is not reservable from any library" << endl;
        return;
    } else {
        cout << pienin_varausjono << " reservations" << endl;
    }

    for (const auto& kirjastot : haetut_tiedot) {
            for (const auto& kirja : kirjastot.second) {
                if (kirja.reservations == pienin_varausjono) {
                    cout << "--- " << kirjastot.first << endl;
                }
            }
        }
}

/*
 * Funktio 'hyllyssa_olevien_kirjojen_tulostus' tulostaa kaikki
 * 'hyllyssä' olevat kirjat haetut_tiedot-mapista.
 * Funktiolla on yksi parametri, haetut_tiedot map<string, vector<Book>> -
 * tietorakenne, joka sisältää eri kirjastojen nimet ja niiden
 * kokoelmat vector<Book> -muodossa.
 * */

void hyllyssa_olevien_kirjojen_tulostus( map<string, vector<Book>>
                                        haetut_tiedot ) {

    vector<Book> kaikki_kirjat = {};

    // Tehdään erillinen vektori kaikki_kirjat, johon lisätään haetut_tiedot
    // tietorakenteen sisältävät kirjat eri kirjastoista, jolloin voidaan
    // asettaa ne helposti aakkosjärjestykseen hyödyntäen sort-funktiota.

    for (auto& kirjasto : haetut_tiedot) {
        kaikki_kirjat.insert(kaikki_kirjat.end(),
                             kirjasto.second.begin(), kirjasto.second.end());
    }
    sort(kaikki_kirjat.begin(), kaikki_kirjat.end(),
         [](const Book& eka_kirja, const Book& toka_kirja) {
        return tie(eka_kirja.author, eka_kirja.title)
                < tie(toka_kirja.author, toka_kirja.title);
    });

    for (const auto& kirja : kaikki_kirjat) {
        if (kirja.reservations == 0) {
            cout << kirja.author << ": " << kirja.title << endl;
        }
    }
}

/*
 * Funktio 'lisaa_kirja_tietorakenteeseen' ottaa vastaan
 * kaksi parametria: "KIRJASTOVERKKO", joka on
 * map-tietotyyppinen tietorakenne, johon tallennetaan kirjastoja ja niiden
 * kokoelmia, sekä merkkijonon "tiedoston_rivi", joka sisältää yhden kirjan
 * tiedot.
 *
 * Funktion tehtävänä on tarkistaa, että tiedostorivillä on
 * tarvittava määrä kenttiä ja että ne eivät ole tyhjiä. Jos tarkistus menee
 * läpi, funktion hajottaa tiedostorivin eri kenttiin jakamalla sen
 * ';' -merkin perusteella. Sen jälkeen funktion lisää kirjan tiedot
 * tietorakenteeseen. Jos kyseinen kirjasto löytyy jo tietorakenteesta,
 * funktion lisää kirjan sen kokoelmaan. Jos kyseinen kirja löytyy jo
 * kokoelmasta, funktion päivittää sen varausmäärän uusimmaksi.
 * Jos kirjaa ei löydy kokoelmasta, funktion lisää sen uutena kirjana
 * kokoelmaan. Jos kyseistä kirjastoa ei löydy tietorakenteesta, funktion
 * luo sille uuden merkinnän ja lisää kirjan sen kokoelmaan.
 *
 * Funktion palauttaa true, jos kirjan lisäys onnistuu, ja
 * false, jos se epäonnistuu.
 * */

bool lisaa_kirja_tietorakenteeseen( map<string, vector<Book>>& KIRJASTOVERKKO,
                                   const string& tiedoston_rivi ) {

    vector<string> merkkijonot = jako_osiin(tiedoston_rivi, ';', true);

    if (merkkijonot.size() != ODOTETTU_KENTTAMAARA_RIVILLA) {
        cout << "Error: empty field" << endl;
        return false;
    }
    for (unsigned long i = 0; i < ODOTETTU_KENTTAMAARA_RIVILLA; i++) {
        if (merkkijonot.at(i).empty()) {
            cout << "Error: empty field" << endl;
            return false;
        }
    }
    string kirjasto = merkkijonot.at(0);
    string kirjailija = merkkijonot.at(1);
    string kirjan_nimi = merkkijonot.at(2);
    int varaukset = 0;

    if (merkkijonot.at(3) != "on-the-shelf") {
        varaukset = stoi(merkkijonot.at(3));
    }
    Book kirja = { kirjailija, kirjan_nimi, varaukset };

    if (KIRJASTOVERKKO.find(kirjasto) != KIRJASTOVERKKO.end()) {

        // Kirjasto löytyy jo kirjasto verkosta, lisätään kirja sen kokoelmaan.
        // Jos kirja löytyy, päivitetään sen varaus tilanne viimeisimpään.
        // Jos kirjalla on sama nimi, mutta kirjailija on eri,
        // lisätään se uutena kirjana.

        vector<Book>& kirjasto_info = KIRJASTOVERKKO.at(kirjasto);
        bool kirja_loyty = false;

        for (auto& kirja : kirjasto_info) {
            if ( kirja.title == kirjan_nimi && kirja.author == kirjailija ) {
                kirja_loyty = true;
                kirja.reservations = varaukset;
                break;
            }
        }
        if (!kirja_loyty) {
            kirjasto_info.push_back(kirja);
        }
    }
    else {
        // Kirjasto ei ole kirjastoverkossa, luodaan sille uusi merkintä.
        vector<Book> kirjasto_info;
        kirjasto_info.push_back(kirja);
        KIRJASTOVERKKO.insert(make_pair(kirjasto, kirjasto_info));
    }
    return true;
}

/*
 * Funktio 'lue_syotetiedosto' ottaa vastaan
 * kaksi parametria: map-tietorakenteen
 * "KIRJASTOVERKKO", joka sisältää kirjojen tietoja, ja merkkijonon
 * "tiedoston_nimi", joka sisältää tiedoston nimen, josta kirjojen
 * tiedot halutaan lukea.
 *
 * Funktio yrittää avata tiedoston ja tarkistaa, onko
 * tiedoston avaaminen onnistunut. Jos tiedoston avaaminen ei onnistu,
 * funktio tulostaa virheilmoituksen ja palauttaa false. Jos tiedosto
 * avataan onnistuneesti, funktio käy tiedoston läpi ja lähettää jokaisen
 * rivin parametrina lisaa_kirja_tietorakenteeseen()-funktiolle, joka
 * yrittää lisätä kirjan tiedot KIRJASTOVERKKO-tietorakenteeseen. Jos
 * kirjan lisääminen ei onnistu, funktio palauttaa false.
 *
 * Kun kaikki rivit on käyty läpi onnistuneesti, tiedosto suljetaan
 * ja funktio palauttaa true.
 * */

bool lue_syotetiedosto( map<string, vector<Book>>& KIRJASTOVERKKO,
                       const string& tiedoston_nimi ) {

    ifstream syotetiedosto(tiedoston_nimi);

    if (!syotetiedosto) {
        cout << "Error: input file cannot be opened" << endl;
        return false;
    }

    string rivi = "";
    while (getline(syotetiedosto, rivi)) {
        bool onnistuuko_kirjojen_lisaaminen =
                lisaa_kirja_tietorakenteeseen(KIRJASTOVERKKO, rivi);
        if (!onnistuuko_kirjojen_lisaaminen) {
            return false;
        }
    }
    syotetiedosto.close();
    return true;
}

/*
 * Main-funktio toimii ohjelman käyttöliittymänä. Käyttäjä syöttää
 * syötetiedoston mistä haetaan tiedot tietorakenteeseen KIRJASTOVERKKO,
 * mikä toimii sen jälkeen tiedon hakujen kohteena. Onnistuneen haun jälkeen,
 * Käyttäjä voi sitten syöttää ennalta määrättyjä komentoja, mitkä tarkistetaan
 * parametrien määrän osalta. Jos virhetarkastelut menevät läpi,
 * käyttäjän komennon perusteella haetaan tiedot käyttäen hakualgoritmiä ja
 * kirjastoverkon_haku-funktiota ja lisätään tiedot "haetut_tiedot" tai
 * "haetut_kirjastot" tietorakenteeseen. "haetut_tiedot" tietorakenne sisältää
 * halutut kirjat, kirjastot ja "haetut_kirjastot" kirjastot kirjoineen.
 * Nämä viedään eri tulosta-funktioihin komennosta riipuen, joka tulostaa
 * käyttäjän hakemat tiedot näytölle.
 * */

int main()
{
    // Tietorakenne, mikä sisältää syötetiedoston tiedot.
    // Tästä tietorakenteesta haetaan tietoa.
    map<string, vector<Book>> KIRJASTOVERKKO = {};

    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    bool onnistuuko_tiedoston_lukeminen =
            lue_syotetiedosto(KIRJASTOVERKKO, tiedoston_nimi);
        if (!onnistuuko_tiedoston_lukeminen) {
            return EXIT_FAILURE;
        }
    while(true)
    {
        string rivi = "";
        cout << "lib> ";
        getline(cin, rivi);
        vector<string> rivin_osat = jako_osiin(rivi, ' ', true);

        if( rivin_osat.size() == 0 ) {
            continue;
        }

        SallitutKomennot sallitut = {};
        string komento = rivin_osat.at(0);

        if (find(sallitut.komennot.begin(), sallitut.komennot.end(), komento)
                == sallitut.komennot.end()) {
                    cout << "Error: unknown command" << endl;
                    continue;
                }

        map<string, vector<Book>> haetut_tiedot = {};
        map<string, vector<Book>> haetut_kirjastot = {};

        if( komento == "quit" &&
                onko_parametrien_maara_oikea(rivin_osat.size(), 0) )
        {
            return EXIT_SUCCESS;
        }
        else if( komento == "libraries" &&
                 onko_parametrien_maara_oikea(rivin_osat.size(), 0) )
        {
            haetut_kirjastot = kirjastoverkon_haku(KIRJASTOVERKKO);
            kirjastojen_tulostus(haetut_kirjastot);
        }
        else if( komento == "loanable" &&
                 onko_parametrien_maara_oikea(rivin_osat.size(), 0) )
        {
            haetut_kirjastot = kirjastoverkon_haku(KIRJASTOVERKKO);
            haetut_tiedot = useampi_kirjastoverkon_haku(haetut_kirjastot);
            hyllyssa_olevien_kirjojen_tulostus(haetut_tiedot);
        }
        else if ( komento == "material" &&
                  onko_parametrien_maara_oikea(rivin_osat.size(), 1) )
        {
            string kirjasto = rivin_osat.at(1);
            haetut_tiedot = kirjastoverkon_haku(KIRJASTOVERKKO, kirjasto);
            virhetarkastelu(KIRJASTOVERKKO, kirjasto);
            kirjaston_kirjojen_tulostus(haetut_tiedot);
        }
        else if ( komento == "books" &&
                  onko_parametrien_maara_oikea(rivin_osat.size(), 2) )
        {
            string kirjasto = rivin_osat.at(1);
            string kirjailija = rivin_osat.at(2);
            haetut_tiedot =
                    kirjastoverkon_haku(KIRJASTOVERKKO, kirjasto, kirjailija);
            virhetarkastelu(KIRJASTOVERKKO, kirjasto, kirjailija);
            kirjailijan_kirjojen_tulostus(haetut_tiedot);
        }
        else if (komento == "reservable" &&
                 onko_parametrien_maara_oikea(rivin_osat.size(), 2, true ))
        {
            string kirjailija = rivin_osat.at(1);
            string kirjan_nimi = muodosta_kirjan_nimi_syotteesta(rivin_osat);
            haetut_kirjastot = kirjastoverkon_haku(KIRJASTOVERKKO);
            haetut_tiedot = useampi_kirjastoverkon_haku
                    (haetut_kirjastot, kirjailija, kirjan_nimi);
            virhetarkastelu(haetut_tiedot);
            lyhimman_varausjonon_tulostus(haetut_tiedot);
            }
        }
}
