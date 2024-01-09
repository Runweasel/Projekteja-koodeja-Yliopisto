package fi.tuni.prog3.junitorder;


/**
 * An exception signalling an empty order.
 */

public class EmptyOrderException extends Exception {

    // Unique ID for serializing this exception (typical for all Serializable classes)
    private static final long serialVersionUID = 1L;

    /**
     * Constructs an EmptyOrderException with the provided message.
     *
     * @param msg the message.
     */
    public EmptyOrderException(String msg) {
        super(msg);
    }
}