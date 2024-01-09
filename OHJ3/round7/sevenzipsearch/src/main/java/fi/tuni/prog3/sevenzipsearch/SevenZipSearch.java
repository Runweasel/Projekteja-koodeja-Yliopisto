package fi.tuni.prog3.sevenzipsearch;

import java.util.Scanner;
import java.util.regex.Pattern;

import org.apache.commons.compress.archivers.sevenz.SevenZArchiveEntry;
import org.apache.commons.compress.archivers.sevenz.SevenZFile;

import java.io.File;
import java.io.IOException;

public class SevenZipSearch {
    public static void main(String[] args) {

        // Ohjelma tulostaa näytölle kehotteen File:, jonka jälkeen käyttäjältä luetaan tiedostonimi. 
        // Seuraavaksi tulostetaan näytölle kehote Query:, jonka jälkeen käyttäjältä luetaan haettava sana.
        // Tämän jälkeen tulostetaan vielä tyhjä rivi.

        Scanner lukija = new Scanner(System.in);

        // Tulostaa "File:" ja lukee tiedostonimen
        System.out.print("File:");
        String filename = lukija.nextLine();

        // Tulostaa tyhjän rivin
        System.out.println();

        // Tulostaa "Query:" ja lukee haettavan sanan
        System.out.print("Query:");
        String hakuSana = lukija.nextLine();

        // Tulostaa tyhjän rivin
        System.out.println();

        lukija.close();

        // Ohjelma selaa käyttäjän antaman 7z-tiedoston sisältämät tiedostot läpi ja
        // suorittaa hakusanahaun kussakin löytämässään tekstitiedostossa.

        try (SevenZFile sevenZFile = new SevenZFile(new File(filename))) {
            SevenZArchiveEntry merkinta;
            System.out.println();  // Ylimääräinen rivinvaihto

            while ((merkinta = sevenZFile.getNextEntry()) != null) {
                // Tarkista onko tiedoston nimen loppu ".txt"
                if (merkinta.getName().endsWith(".txt")) {
                    System.out.println(merkinta.getName());
            
                    // Lue tiedoston sisältö
                    byte[] sisalto  = new byte[(int) merkinta.getSize()];
                    sevenZFile.read(sisalto );

                    // Suorita hakusana-haku
                    suoritaHakuTekstissa(new String(sisalto ), hakuSana);

                    System.out.println();  // Ylimääräinen rivinvaihto
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }    
    }

    // Tiedostoa luetaan rivi kerrallaan, ja kultakin riviltä etsitään kaikki hakusanan esiintymät kirjainkoosta riippumatta.
    // Jos yksikin esiintymä löytyy, kyseinen rivi tulostetaan ruudulle muodossa “rivinumero: rivi”, 
    // missä rivinumero on kyseisen rivin rivinumero (tiedoston ensimmäisen rivin numero on 1)
    // ja rivi on kyseinen rivi esitettynä sellaisessa muodossa, että kaikki hakusanan esiintymät on muunnettu käyttämään isoja kirjaimia.


    public static void suoritaHakuTekstissa(String text, String hakuSana) {
        String[] rivit  = text.split("\n");
        String hakuSanaIsoilla  = hakuSana.toUpperCase();
        String hakuSanaPienilla  = hakuSana.toLowerCase();

        for (int i = 0; i < rivit.length; i++) {

            if (rivit[i].toLowerCase().contains(hakuSanaPienilla)) {
                // Muunna kaikki hakusanan esiintymät isoiksi kirjaimiksi
                String korostettuRivi  = rivit[i].replaceAll("(?i)" + Pattern.quote(hakuSana), hakuSanaIsoilla);
                System.out.printf("%d: %s%n", i + 1, korostettuRivi );
            }
        }
    }

}