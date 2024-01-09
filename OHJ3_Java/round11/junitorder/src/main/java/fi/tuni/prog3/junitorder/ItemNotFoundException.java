package fi.tuni.prog3.junitorder;

/**
 * An exception signaling that an item is not found.
 */
public class ItemNotFoundException extends Exception {

    // Unique ID for serializing this exception (typical for all Serializable classes)
    private static final long serialVersionUID = 1L;

    /**
     * Constructs an ItemNotFoundException with the provided message.
     * @param msg the message.
     */
    public ItemNotFoundException(String msg) {
        super(msg);
    }
}