package fi.tuni.prog3.json;

public class ValueNode extends Node{

    // Muuttujat:
    private Double numberValue;
    private Boolean booleanValue;
    private String stringValue;



    // Rakentaja ValueNode(), joka asettaa olion tiedoksi null-arvon.

    public ValueNode() {
        this.numberValue = null;
        this.booleanValue = null;
        this.stringValue = null;
    }

    // Rakentajat ValueNode(double value), ValueNode(boolean value) ja ValueNode(String value) asettavat olion tiedoksi jonkin edellä mainituista tyypeistä. 

    public ValueNode(double value) {
        this.numberValue = value;

        this.booleanValue = null;
        this.stringValue = null;
    }

    public ValueNode(boolean value) {
        this.booleanValue = value;

        this.numberValue = null;
        this.stringValue = null;
    }

    // Tehtävässä oletetaan, että ValueNode(String value)-rakentajalle ei anneta parametriksi null-arvoa.

    public ValueNode(String value) {
        this.stringValue = value;

        this.numberValue = null;
        this.booleanValue = null;
    }

    // Boolean-tyyppiset jäsenfunktiot isNumber(), isBoolean(), isString() ja isNull(), joista kukin tutkii onko olion tieto tiettyä tyyppiä. 
    // Esimerkiksi isString palauttaa true-arvon, jos ja vain jos olioon talletettu tieto on merkkijono.

    public boolean isNumber() {
        return numberValue != null;
    }

    public boolean isBoolean() {
        return booleanValue != null;
    }

    public boolean isString() {
        return stringValue != null;
    }

    public boolean isNull() {
        return numberValue == null && booleanValue == null && stringValue == null;
    }

    // Jäsenfunktiot double getNumber(), boolean getBoolean(), String getString() ja Object getNull(), joista kukin palauttaa olion sisältämän tiedon. 
    // Saantifunktion kutsujan vastuulla on varmistaa ennen kutsua oikea tietotyyppi tyypin tarkistavalla jäsenfunktiolla.
    // Esimerkiksi getBoolean()-funktiota kutsuttaessa oletetaan, että aiemmin on todettu isBoolean()-funktiolla tiedon tyypiksi boolean.

    public double getNumber() {
        if (!isNumber()) {
            throw new IllegalStateException("Tietotyyppi ei ole numero.");
        }
        return numberValue;
    }

    public boolean getBoolean() {
        if (!isBoolean()) {
            throw new IllegalStateException("Tietotyyppi ei ole boolean.");
        }
        return booleanValue;
    }

    public String getString() {
        if (!isString()) {
            throw new IllegalStateException("Tietotyyppi ei ole merkkijono.");
        }
        return stringValue;
    }

    public Object getNull() {
        if (!isNull()) {
            throw new IllegalStateException("Tieto ei ole null.");
        }
        return null;
    }

}