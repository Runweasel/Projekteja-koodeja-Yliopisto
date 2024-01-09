package fi.tuni.prog3.jsoncountries;

public class Country implements Comparable<Country> {
    
    // Luokka Country tallettaa maan nimen (merkkijono), pinta-alan (double), väkiluvun (long) ja bruttokansantuotteen (double).

    private String maa_nimi;
    private Double pinta_ala;
    private Long vakiluku;
    private Double BRT;

    public Country(String maa_nimi, double pinta_ala, long vakiluku, double BRT) {
        this.maa_nimi = maa_nimi;
        this.pinta_ala = pinta_ala;
        this.vakiluku = vakiluku;
        this.BRT = BRT;
    }

    // Toteuttaa rajapinnan Comparable<Country> niin, 
    // että vertailu perustuu maan nimeen String-luokan luonnollisen järjestyksen mukaisesti.

    @Override
    public int compareTo(Country toinen_maa) {
        return this.maa_nimi.compareTo(toinen_maa.maa_nimi);
    }

    // Julkinen jäsenfunktio String toString(), joka palauttaa maan tiedot esimerkkitulosteissa kuvatulla tavalla: 
    // ensin maan nimi, ja sen alla kahdella välilyönnillä sisennettyinä omilla riveillään pinta-ala, väkiluku ja bruttokansantuote. 
    // Double-arvot yhden desimaalin tarkkuudella.

    @Override
    public String toString() {
        return maa_nimi + "\n" +
            "  Area: " + String.format("%.1f", pinta_ala) + " km2\n" +
            "  Population: " + vakiluku + "\n" +
            "  GDP: " + String.format("%.1f", BRT) + " (2015 USD)\n";
    }

    // Julkiset jäsenfunktiot String getName(), double getArea(), long getPopulation() ja double getGdp(), 
    // jotka palauttavat nimiensä kuvaamat tiedot.

    public String getName() {
        return maa_nimi;
    }

    public double getArea() {
        return pinta_ala;
    }

    public long getPopulation() {
        return vakiluku;
    }

    public double getGdp() {
        return BRT;
    }

}