package fi.tuni.prog3.json;

import java.util.Iterator;
import java.util.TreeMap;

public class ObjectNode extends Node implements Iterable<String>{

    // Toteuttaa rajapinnan Iterable<String>. 
    //Iteroi kaikkien talletettujen avain–alkio-parien avaimet String-merkkijonojen luonnollisessa järjestyksessä.

    private TreeMap<String, Node> avain_alkio_parit;

    @Override
    public Iterator<String> iterator() {
        return avain_alkio_parit.keySet().iterator();
    }

    // Oletusrakennin, joka alustaa olion siten, että sillä ei ole vielä yhtään avain-alkioparia.

    public ObjectNode() {
        avain_alkio_parit = new TreeMap<>();
    }

    // Jäsenfunktio Node get(String key), joka palauttaa avaimen key arvoa vastaavan Node-olion.
    // Paluuarvo on null-arvo sellaisenaan, jos avainta vastaavaa paria ei ole.
    // Palauta siis null-arvo vain haun epäonnistumisen merkkinä.
    // Null-arvon sisältävä ValueNode-olio palautetaan, jos avain liittyy sellaiseen.

    public Node get(String key) {
        return avain_alkio_parit.get(key);
    }

    // Jäsenfunktio void set(String key, Node node), joka lisää parametrien kuvaaman avain–alkio-parin.
    // Mahdollinen vanha saman avaimen alkio korvautuu uudella.

    public void set(String key, Node node) {
        avain_alkio_parit.put(key, node);
    }

    // Jäsenfunktio int size(), joka palauttaa avain–alkio-parien lukumäärän.

    public int size() {
        int lukumäärä = avain_alkio_parit.size();
        return lukumäärä;
    }


    
}