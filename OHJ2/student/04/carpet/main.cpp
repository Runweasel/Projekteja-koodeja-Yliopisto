
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <cctype>

/* Mysteerimatto
 *
 * Kuvaus:
 * Ohjelma toteuttaa mysteerimaton, jossa sovelletaan mallintunnistusta
 * (pattern matching). Matto koostuu erivärisistä ruuduista ja samoin
 * malli, mutta mallin koko on aina 2 x 2, eli se koostuu neljästä
 * väriruudusta. Ohjelma etsii mallin esiintymiä matosta.
 *   Ohjelma kysyy ensin maton kokoa (leveys ja pituus). Käyttäjältä
 * kysytään myös, täytetäänkö matto (ruudukko) satunnaisesti arvottavilla
 * vai käyttäjän luettelemilla väreillä. Ensimmäisessä vaihtoehdossa
 * käyttäjältä kysytään satunnaislukugeneraattorin siemenlukua ja
 * jälkimmäisessä häntä pyydetään syöttämään niin monta väriä, kuin matossa
 * on ruutuja, jolloin luetellaan värien alkukirjaimet yhtenä pitkänä
 * merkkijonona.
 *   Joka kierroksella käyttäjältä kysytään etsittävää mallia (neljän
 * merkin/värin muodostamaa merkkijonoa). Ohjelma tulostaa, kuinka monta
 * mallin esiintymää matosta löytyi ja mistä kohdista ne löytyivät.
 *   Ohjelma tarkistaa, oliko käyttäjän antamat värikoodit hyväksyttäviä.
 * Ohjelma päättyy, kun käyttäjä antaa lopetuskomennon (merkki 'q' tai 'Q').
 *
 * Ohjelman kirjoittaja
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 *
 * */

using namespace std;

enum Vari {PUNAINEN, VIHREA, SININEN, KELTAINEN, VALKOINEN};

struct Vari_Info {
    char kirjain;
};

const vector<Vari_Info> Varit = {
    { 'R' },
    { 'G' },
    { 'B' },
    { 'Y' },
    { 'W' },
};

vector<int> lue_maton_koko() {

    /*
     * Funktio lukee käyttäjän syöttämän leveyden ja korkeuden,
     * jossa arvot ovat eroteltuna välilyönnillä, ja muuntaa ne kahdeksi
     * kokonaislukuarvoksi tallennettavaksi vektoriksi. Jos syöte ei ole
     * kelvollinen, eli siinä ei ole kahta numeroa tai jos jokin luku on alle 2,
     * ohjelma antaa 'main'-funktiossa virheilmoituksen ja lopettaa suorituksen.
     * Funktio palauttaa luvut 'leveys' ja 'korkeus' vektoriin.
     *
     * */

    int leveys;
    int korkeus;
    cin >> leveys >> korkeus;
    return { leveys, korkeus };
}

char maton_aloitustapa() {

    /*
     * Funktio kysyy käyttäjältä maton luomiseen aloitustapaa. Käyttäjälle
     * annetaan kaksi vaihtoehtoa:
     *
     * - 'R' = väriruutujen arpominen satunnaisesti.
     * - 'I' = lukeminen käyttäjän syötteestä.
     *
     * Funktio lukee käyttäjän syötteen ja palauttaa 'R' jos käyttäjä syotti
     * 'r' tai 'R' ja 'I' jos käyttäjä syötti 'i' tai 'I'. Funktio jatkaa
     * kysymistä, kunnes saa hyväksyttävän syötteen.
     *
     * */

    while ( true ) {

        cout << "Select start (R for random, I for input): ";
        string syote = "";
        cin >> syote;

        if ( syote == "r" || syote == "R" ) {
            return 'R';
        }
        else if ( syote == "i" || syote == "I" )
            return 'I';
    }
}

bool syote_tarkastelu(string syote, unsigned long odotettu_vari_maara = 4) {

    /*
     * Funktio tarkastaa käyttäjän syötteen oikeellisuuden. Funktion ensimmäinen
     * parametri 'syote' on käyttäjän syöttämä merkkijono, joka sisältää värejä.
     * Funktion toinen parametri 'odotettu_vari_maara' on oletuksena 4, mikä
     * tarkoittaa, että funktio odottaa syötteessä olevan 4 väriä, ellei toisin
     * määritellä. Jos 'odotettu_vari_maara' ei täsmää 'syote' -merkkijonon
     * kokoon, tulostetaan virheilmoitus ja funktio palauttaa 'false'.
     *
     * Funktio alkaa tarkistamalla, onko 'syote' -merkkijonon pituus sama kuin
     * 'odotettu_vari_maara' parametrin arvo. Jos pituus ei täsmää, funktio
     * tulostaa virheilmoituksen ja palauttaa 'false'. Jos pituus täsmää,
     * funktio jatkaa värien yksitellen tarkistamista.
     *
     * Funktion käy läpi jokaisen 'syote' -merkkijonon merkin ja tarkistaa,
     * että se vastaa jotain Varit määritellyistä väreistä. Jos löytyy
     * vastaavuus, merkki merkiltä käydään läpi kaikki värilistassa olevat
     * värit, kunnes löytyy vastaavuus. Jos jokin merkki ei vastaa mitään
     * ennaltamääritellyistä väreistä, funktio tulostaa virheilmoituksen
     * ja palauttaa 'false'.
     *
     * Jos kaikki syötteen merkit ovat oikein, funktio palauttaa 'true'.
     *
     * */

    bool syote_oikeellinen = true;

    if ( syote.size() != odotettu_vari_maara ) {
        cout << " Error: Wrong amount of colors." << endl;
        syote_oikeellinen = false;
        return syote_oikeellinen;
    }

    for ( const char& kirjain : syote ) {

        bool loyty = false;
                for ( const Vari_Info& vari : Varit ) {
                    if ( kirjain == vari.kirjain ) {
                        loyty = true;
                    }
                }
                if ( !loyty ) {
                            syote_oikeellinen = false;
                            cout << " Error: Unknown color." << endl;
                            break;
                        }
    }
    return syote_oikeellinen;
}


vector<char> maton_generointi(vector<int> koko, char tapa) {

    /*
     * Funktio generoi char-vektorin, joka edustaa mattoa. Maton 'koko'
     * ja generointi-'tapa' annetaan funktiolle parametreina. Jos generointitapa
     * on 'R', funktio luo satunnaisesti värillisen maton käyttäen värilistaa
     * Varit. Värivalinta tapahtuu uniform_int_distribution - luokan avulla,
     * joka käyttää käyttäjän antamaa siemenarvoa satunnaisluvun generoimiseen.
     *
     * Jos generointitapa on 'I', funktio kysyy käyttäjältä käyttäjän antamaa
     * värijonoa ja tarkistaa, että onko 'syote_tarkastelu' funktion paluuarvona
     * 'true' eli syöte täsmää ehtoja. Luo sen jälkeen värillisen maton
     * käyttäen annettuja värejä.
     *
     * Funktio käyttää 'syote_tarkastelu' -funktiota tarkistaakseen
     * käyttäjän syötteen oikeellisuuden.
     * Funktio palauttaa matto-char-vektorin.
     *
     * */

    vector<char> maton_kuviointi;

    if ( tapa == 'R' ) {

        default_random_engine random_gen;
        uniform_int_distribution<int> jakauma(0, 4);

        cout << "Enter a seed value: ";
        int siemen_arvo;
        cin >> siemen_arvo;
        random_gen.seed(siemen_arvo);

        for( int y = 0; y < koko.at(1); ++y ) {
            for( int x = 0; x < koko.at(0); ++x ) {
               maton_kuviointi.push_back(Varit.at(jakauma(random_gen)).kirjain);
            }
        }
        return maton_kuviointi;
}

    else if ( tapa == 'I' ) {

        cout << "Input: ";
        string lista_vareista;
        cin >> lista_vareista;

        unsigned long montako_varia = koko.at(0) * koko.at(1);

        if ( syote_tarkastelu( lista_vareista, montako_varia ) ) {
            for ( const char& kirjain : lista_vareista ) {
                maton_kuviointi.push_back(kirjain);
            }
        }
        return maton_kuviointi;
    }
    return maton_kuviointi;
}


void kuvioiden_etsinta(vector<char> maton_kuviointi,
                       string haettava_kuvio, vector<int> koko) {

    /*
     * Funktio etsii tiettyä kuvioita kaksiulotteisesta merkkivektorista
     * 'matto'. Funktio ottaa vastaan käyttäjän antaman syötteen eli
     * 'haettava_kuvio'-merkkijonon, joka edustaa haettavaa kuviota,
     * sekä 'koko'-vektorin, joka sisältää matto-vektorin mitat.
     *
     * Funktio käy läpi jokaisen 'matto'-vektorin elementin ja tarkistaa,
     * vastaako se 'haettava_kuvio':n kahden ensimmäisen merkin kanssa.
     * Jos vastaavuus löytyy, funktio tarkistaa seuraavat kaksi merkkiä
     * 'haettava_kuvio'-merkkijonosta seuraavasta rivistä. Jos täydellinen
     * vastaavuus löytyy, funktio tulostaa vastaavuuden sijainnin ja lisää
     * lasketun vastaavuuksien määrän laskuria.
     * Lopuksi funktio tulostaa löydettyjen vastaavuuksien kokonaismäärän.
     *
     * */

    int vastaavuus_loyty = 0;
    for( int y = 0; y < koko.at(1); ++y ) {

        // Seuraavat if-lauseet näyttävät erikoisilta, mutta ajatuksena
        // on verrata käyttäjän 4 värin syötettä alkaen ensimmäisestä
        // ja verrata täsmääkö se 2x2 kuvioinnin kanssa matossa. Aloittaen
        // ensimmäisestä maton väristä siirtyen aina yhden oikealle kunnes
        // tilaa ei ole jolloin hypätään y-akselilla alaspäin. Jokaisen värin
        // kohdalla tehdään 2x2 kuviointi mitä verrataan syötteeseen.
        // Vektorissa arvot alkavat indeksillä 0, joten koordinaatistossa
        // täytyy lisätä +1 x- ja y-arvoihin. Koodi muodostaa matemaattisen
        // yhtälön. Asettelu johtuu 80 merkin rajasta.

   for( int x = 0; x < koko.at(0); ++x ) {
    if ( x + 1 < koko.at(0) && y + 1 < koko.at(1) ) {

     if ( haettava_kuvio.at(0) == maton_kuviointi.at(x+(y*koko.at(0)))
     && haettava_kuvio.at(1) == maton_kuviointi.at(x+(y*koko.at(0))+1) ) {

      if ( haettava_kuvio.at(2) ==
           maton_kuviointi.at(x+(y*koko.at(0))+koko.at(0))
           && haettava_kuvio.at(3) ==
           maton_kuviointi.at(x+(y*koko.at(0))+koko.at(0)+1) ) {

                   cout << " - Found at (" << x+1 << ", " << y+1 << ")" << endl;
                   ++vastaavuus_loyty;
                        }
                    }
            }
        }
}
    cout << " = Matches found: " << vastaavuus_loyty << endl;
    return;
}

void maton_tulostus(vector<int> koko, vector<char> maton_kuviointi ) {

    /*
     * Funktio tulostaa maton näytölle. Se saa syötteeksi makon koon, 'koko',
     * ja vektorin 'maton_kuviointi', joka sisältää maton väriruutujen
     * merkkiesityksen. Funktio käyttää kaksiuloitteista silmukkaa
     * tulostamiseen, jossa käydään läpi vektorin alkiot maton korkeuden
     * ja leveyden mukaisessa järjestyksessä. Funktio tulostaa jokaisen
     * väriruudun merkkiesityksen välilyonnillä erotettuna ja siirtyy uudelle
     * riville jokaisen rivin jälkeen. Funktion tulostama 'maton_kuviointi'
     * vastaa mallin mattoa.
     *
     * */

    int indeksi = 0;
    for( int y = 0; y < koko.at(1); ++y ) {
        for( int x = 0; x < koko.at(0); ++x ) {
            cout << " " << maton_kuviointi.at(indeksi);
            indeksi++;
        }
        cout << endl;
    }
    return;
}

int main() {

    /*
     * Luo maton käyttäjän antamien syötteiden perusteella ja antaa käyttäjän
     * hakea matosta tiettyjä värejä. Funktion ensimmäinen vaihe pyytää
     * käyttäjältä maton leveyttä ja korkeutta, tarkistaa että maton koko
     * on vähintään 2 x 2, ja pyytää käyttäjältä, millaisella tavalla
     * matto tulostetaan. Tämän jälkeen funktio generoi maton käyttäjän
     * antaman tulostustavan mukaisesti ja tulostaa sen näytölle. Lopuksi
     * funktio pyytää käyttäjältä neljää väriä ja etsii niitä vastaavat
     * kuviot matosta, ja tulostaa ne näytölle. Funktio palauttaa EXIT_SUCCESS
     * jos ohjelma suoritettiin onnistuneesti ja EXIT_FAILURE jos jokin virhe
     * havaittiin.
     *
     * */

    vector<char> maton_kuviointi;

    cout << "Enter carpet's width and height: ";

    vector<int> koko = lue_maton_koko();

    if ( koko.at(0) < 2 || koko.at(1) < 2 ) {
        cout << "Error: Carpet cannot be smaller than pattern." << endl;
        return EXIT_FAILURE;
    }

    while ( maton_kuviointi.size() == 0 ) {

        char tulostus_tapa = maton_aloitustapa();

        if ( tulostus_tapa == 'R' ) {
            maton_kuviointi = maton_generointi(koko, 'R');
        }
        else if ( tulostus_tapa == 'I' ) {
            maton_kuviointi = maton_generointi(koko, 'I');
        }
        }

    maton_tulostus(koko, maton_kuviointi);

    while ( true ) {

        // Jos syötetty siemen sisältää merkkejä tulee virheellinen
        // cin -syöte, joten while looppi sekoaa, joten tyhjennetään ja
        // välitetään vain int luvuista. Siemeneen voi siis syöttää
        // myös merkkejä.

        cin.clear();
        cin.ignore( numeric_limits<int>::max(), '\n' );

        cout << "Enter 4 colors, or q to quit: ";
        string syote;
        cin >> syote;

        int indeksi = 0;
        for ( auto kirjain : syote ) {
            syote.at(indeksi) = toupper(kirjain);
            indeksi++;
        }

        if ( syote == "q" || syote == "Q" ) {
            return EXIT_SUCCESS;
        }
        else if ( syote_tarkastelu(syote) ) {
            kuvioiden_etsinta(maton_kuviointi, syote, koko);
        }
    }
    }
