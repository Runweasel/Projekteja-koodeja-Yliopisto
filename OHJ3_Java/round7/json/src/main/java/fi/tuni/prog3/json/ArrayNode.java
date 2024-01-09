package fi.tuni.prog3.json;

import java.util.ArrayList;
import java.util.Iterator;

public class ArrayNode extends Node implements Iterable<Node>{

    // Toteuttaa rajapinnan Iterable<Node>.

    @Override
    public Iterator<Node> iterator() {
        return nodes.iterator();
    }

    private ArrayList<Node> nodes;

    // Oletusrakennin, joka alustaa tyhjän taulukon eli taulukon, joka ei vielä sisällä yhtään Node-oliota.

    public ArrayNode() {
        nodes = new ArrayList<>();
    }

    // Jäsenfunktio void add(Node node), joka lisää annetun Node-olion taulukon loppuun.

    public void add(Node node) {
        nodes.add(node);
    }

    // Jäsenfunktio int size(), joka palauttaa taulukon Node-olioiden lukumäärän.

    public int size() {
        return nodes.size();
    }

}