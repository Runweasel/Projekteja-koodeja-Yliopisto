package fi.tuni.prog3.json;

/**
 * A class for representing a JSON value. The value can be either a double, a boolean, a String or null.
 */
public class ValueNode extends Node{

    // Muuttujat:
    private Double numberValue;
    private Boolean booleanValue;
    private String stringValue;

    /**
     * Constructs a JSON value node that stores the null value.
     */
    public ValueNode() {
        this.numberValue = null;
        this.booleanValue = null;
        this.stringValue = null;
    }

    /**
     * Constructs a JSON value node that stores the given double value.
     * @param value The double value to store in the new JSON value node.
     */
    public ValueNode(double value) {
        this.numberValue = value;
        this.booleanValue = null;
        this.stringValue = null;
    }

    /**
     * Constructs a JSON value node that stores the given boolean value.
     * @param value The boolean value to store in the new JSON value node.
     */
    public ValueNode(boolean value) {
        this.booleanValue = value;
        this.numberValue = null;
        this.stringValue = null;
    }

    /**
     * Constructs a JSON value node that stores the given string.
     * @param value The string to store in the new JSON value node.
     * @throws IllegalStateException if the parameter value is null.
     */
    public ValueNode(String value) {
        if(value == null) {
            throw new IllegalStateException("Value cannot be null");
        }
        this.stringValue = value;
        this.numberValue = null;
        this.booleanValue = null;
    }

    /**
     * Checks whether this value node stores a number (double).
     * @return true if this node stores a double value, otherwise false.
     */
    public boolean isNumber() {
        return numberValue != null;
    }

    /**
     * Checks whether this value node stores a boolean value.
     * @return true if this node stores a boolean value, otherwise false.
     */
    public boolean isBoolean() {
        return booleanValue != null;
    }

    /**
     * Checks whether this value node stores a string.
     * @return true if this node stores a string, otherwise false.
     */
    public boolean isString() {
        return stringValue != null;
    }

    /**
     * Checks whether this value node stores null.
     * @return true if this node stores null, otherwise false.
     */
    public boolean isNull() {
        return numberValue == null && booleanValue == null && stringValue == null;
    }

    /**
     * Returns the stored value as a number (double).
     * @return the stored number as a double value.
     * @throws IllegalStateException if the stored value is not a number.
     */
    public double getNumber() {
        if (!isNumber()) {
            throw new IllegalStateException("Tietotyyppi ei ole numero.");
        }
        return numberValue;
    }

    /**
     * Returns the stored value as a boolean value.
     * @return the stored boolean value.
     * @throws IllegalStateException if the stored value is not a boolean value.
     */
    public boolean getBoolean() {
        if (!isBoolean()) {
            throw new IllegalStateException("Tietotyyppi ei ole boolean.");
        }
        return booleanValue;
    }

    /**
     * Returns the stored value as a string.
     * @return the stored string.
     * @throws IllegalStateException if the stored value is not a string.
     */
    public String getString() {
        if (!isString()) {
            throw new IllegalStateException("Tietotyyppi ei ole merkkijono.");
        }
        return stringValue;
    }

    /**
     * Returns the stored value as null.
     * @return null.
     * @throws IllegalStateException if the stored value is not null.
     */
    public Object getNull() {
        if (!isNull()) {
            throw new IllegalStateException("Tieto ei ole null.");
        }
        return null;
    }
}