package fi.tuni.prog3.junitorder;

/**
 * An exception signaling an illegal (e.g., negative) item price.
 */
public class IllegalPriceException extends Exception {

    private static final long serialVersionUID = 1L;

    /**
     * Constructs an IllegalPriceException with the provided message.
     * @param msg the message.
     */
    public IllegalPriceException(String msg) {
        super(msg);
    }
}