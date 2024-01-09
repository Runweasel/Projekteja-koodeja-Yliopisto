package fi.tuni.prog3.junitorder;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.List;

import java.util.NoSuchElementException;

public class JunitorderTest {

    private Order order;
    private Order.Item item1;
    private Order.Item item2;
    private Order.Item item3; // Added third item
    private Order.Item item;

    @BeforeEach
    public void setUp() {
        order = new Order();
        item = new Order.Item("Apple", 10.0);
        item1 = new Order.Item("Item1", 10.0);
        item2 = new Order.Item("Item2", 20.0);
        item3 = new Order.Item("Item3", 30.0); // Initialize item3
    }

    @Test
    @DisplayName("Adding multiple different items")
    public void testAddMultipleDifferentItems() {
        assertTrue(order.addItems(item1, 1));
        assertTrue(order.addItems(item2, 2));
        assertTrue(order.addItems(item3, 3));
        assertEquals(3, order.getEntryCount()); // Now we should have 3 entries
        assertEquals(6, order.getItemCount());  // And a total of 6 items
    }
    
    @Test
    @DisplayName("Adding and removing different items")
    public void testAddAndRemoveDifferentItems() {
        order.addItems(item1, 2);
        order.addItems(item2, 1);
        order.addItems(item3, 3);
        assertTrue(order.removeItems("Item2", 1));
        assertTrue(order.removeItems("Item3", 2));
        assertEquals(3, order.getItemCount()); // Should have 3 items left
    }
    
    @Test
    @DisplayName("Total price calculation with all items")
    public void testTotalPriceWithAllItems() {
        order.addItems(item1, 1); // 10.0 total
        order.addItems(item2, 1); // 20.0 total
        order.addItems(item3, 1); // 30.0 total
        assertEquals(60.0, order.getTotalPrice()); // 10.0 + 20.0 + 30.0 = 60.0
    }

    @Test
    @DisplayName("Item count is correct after adding same item with different instances")
    public void testItemCountAfterAddingSameItemWithDifferentInstances() {
        Order.Item anotherItem3 = new Order.Item("Item3", 30.0);
        order.addItems(item3, 1);
        order.addItems(anotherItem3, 2);
        assertEquals(3, order.getEntries().stream()
          .filter(entry -> "Item3".equals(entry.getItem().getName()))
          .findFirst().orElseThrow().getCount());
    }
    
    @Test
    @DisplayName("Checking if item3 is correctly added")
    public void testItem3AddedCorrectly() {
        assertTrue(order.addItems(item3, 1));
        assertEquals(1, order.getEntryCount());
        assertEquals("Item3", order.getEntries().get(0).getItem().getName());
    }

    @Test
    @DisplayName("Adding items with negative or zero count should throw IllegalArgumentException")
    public void testAddItemsWithInvalidCount() {
        assertThrows(IllegalArgumentException.class, () -> order.addItems(item1, -1));
        assertThrows(IllegalArgumentException.class, () -> order.addItems(item1, 0));
    }

    @Test
    @DisplayName("Adding items with different prices should throw IllegalStateException")
    public void testAddItemsWithDifferentPrice() {
        Order.Item itemWithDifferentPrice = new Order.Item("Item1", 15.0);
        assertDoesNotThrow(() -> order.addItems(item1, 1));
        assertThrows(IllegalStateException.class, () -> order.addItems(itemWithDifferentPrice, 1));
    }

    @Test
    @DisplayName("Adding items by name that do not exist should throw ItemNotFoundException")
    public void testAddItemsByNameNotFound() {
        assertThrows(NoSuchElementException.class, () -> order.addItems("NonExistingItem", 1));
    }

    @Test
    @DisplayName("Removing items decreases the count correctly")
    public void testRemoveItems() {
        order.addItems(item1, 3);
        assertTrue(order.removeItems("Item1", 1));
        assertEquals(2, order.getEntries().get(0).getCount());
    }

    @Test
    @DisplayName("Removing items that do not exist should throw ItemNotFoundException")
    public void testRemoveNonExistingItems() {
        assertThrows(NoSuchElementException.class, () -> order.removeItems("NonExistingItem", 1));
    }

    @Test
    @DisplayName("Removing more items than present should throw IllegalArgumentException")
    public void testRemoveTooManyItems() {
        order.addItems(item1, 1);
        assertThrows(IllegalArgumentException.class, () -> order.removeItems("Item1", 2));
    }

    @Test
    @DisplayName("Removing items with negative or zero count should throw IllegalArgumentException")
    public void testRemoveItemsWithInvalidCount() {
        assertThrows(IllegalArgumentException.class, () -> order.removeItems("Item1", -1));
        assertThrows(IllegalArgumentException.class, () -> order.removeItems("Item1", 0));
    }

    @Test
    @DisplayName("Order total price calculation")
    public void testTotalPriceCalculation(){
        order.addItems(item1, 2); // 20.0 total
        order.addItems(item2, 1); // 20.0 total
        assertEquals(40.0, order.getTotalPrice());
    }

    // Lisää testejä
    
    @Test
    @DisplayName("Equality of two items with the same name")
    public void testItemEquality() {
        Order.Item item3 = new Order.Item("Item1", 10.0);
        assertTrue(item1.equals(item3));
    }

    @Test
    @DisplayName("toString method of Item class")
    public void testItemToString() {
        String expected = "Item(Item1, 10.00)";
        String actual = item1.toString();
        System.out.println("Expected: " + expected);
        System.out.println("Actual: " + actual);
        assertEquals(expected, actual);
    }

    
    @Test
    @DisplayName("toString method of Entry class")
    public void testEntryToString() {
        Order.Entry entry = new Order.Entry(item1, 2);
        String expected = "2 units of Item(Item1, 10.00)";
        String actual = entry.toString();
        System.out.println("Expected: " + expected);
        System.out.println("Actual: " + actual);
        assertEquals(expected, actual);
    }

    @Test
    @DisplayName("Adding an item multiple times increments count correctly")
    public void testAddItemMultipleTimes() {
        order.addItems(item1, 1);
        order.addItems(item1, 2);
        assertEquals(3, order.getEntries().get(0).getCount());
    }

    @Test
    @DisplayName("Adding an item with a null name should throw IllegalArgumentException")
    public void testAddItemWithNullName() {
        assertThrows(IllegalArgumentException.class, () -> new Order.Item(null, 10.0));
    }

    @Test
    @DisplayName("Adding an item with a negative price should throw IllegalArgumentException")
    public void testAddItemWithNegativePrice() {
        assertThrows(IllegalArgumentException.class, () -> new Order.Item("Item3", -10.0));
    }

    @Test
    @DisplayName("Entry constructor with a negative count should throw IllegalArgumentException")
    public void testEntryConstructorWithNegativeCount() {
        assertThrows(IllegalArgumentException.class, () -> new Order.Entry(item1, -1));
    }
    
    @Test
    @DisplayName("Removing items until an entry is deleted from the order")
    public void testRemoveItemsUntilEntryIsDeleted() {
        order.addItems(item1, 1);
        order.removeItems("Item1", 1);
        assertTrue(order.isEmpty());
    }

    @Test
    @DisplayName("Total price is updated correctly after removing items")
    public void testTotalPriceAfterRemoval() {
        order.addItems(item1, 2); // 20.0 total
        order.addItems(item2, 1); // 20.0 total, 40.0 in total
        order.removeItems("Item1", 1); // -10.0, 30.0 expected total
        assertEquals(30.0, order.getTotalPrice());
    }

    @Test
    @DisplayName("Order is empty after adding and removing the same items")
    public void testOrderIsEmptyAfterAddAndRemove() {
        order.addItems(item1, 1);
        order.removeItems("Item1", 1);
        assertTrue(order.isEmpty());
    }
    
    @Test
    @DisplayName("Adding items with valid name and count should succeed")
    public void addItemsWithValidNameAndCount_shouldAddItemSuccessfully() {
        order.addItems(item, 1);
        assertTrue(order.addItems("Apple", 1));
        assertEquals(2, order.getItemCount());
    }

    @Test
    @DisplayName("Getting entries should return a copy of entries")
    public void getEntries_shouldReturnCopyOfEntries() {
        order.addItems(item, 1);
        List<Order.Entry> entries = order.getEntries();
        assertNotSame(entries, order.getEntries());
    }

    @Test
    @DisplayName("Entry count should be zero with no entries")
    public void getEntryCount_withNoEntries_shouldReturnZero() {
        assertEquals(0, order.getEntryCount());
    }

    @Test
    @DisplayName("Item count should return correct count with multiple entries")
    public void getItemCount_withMultipleEntries_shouldReturnCorrectCount() {
        order.addItems(item, 2);
        assertEquals(2, order.getItemCount());
    }

    @Test
    @DisplayName("Order should be empty on new initialization")
    public void isEmpty_onNewOrder_shouldReturnTrue() {
        assertTrue(order.isEmpty());
    }

    @Test
    @DisplayName("Order should not be empty after adding items")
    public void isEmpty_onNonEmptyOrder_shouldReturnFalse() {
        order.addItems(item, 1);
        assertFalse(order.isEmpty());
    }

}
