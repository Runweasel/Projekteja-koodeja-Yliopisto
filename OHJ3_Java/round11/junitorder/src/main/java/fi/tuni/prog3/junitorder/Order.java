package fi.tuni.prog3.junitorder;

import java.util.ArrayList;
import java.util.List;

import java.util.Iterator;
import java.util.Locale;
import java.util.NoSuchElementException;

public class Order {

    private final List<Entry> entries;

    public Order() {
        this.entries = new ArrayList<>();
    }

   public boolean addItems(Order.Item item, int count) throws IllegalArgumentException {
       if (count <= 0) {
           throw new IllegalArgumentException("The item unit count must be positive.");
       }
       for (Entry entry : entries) {
           if (entry.getItem().getName().equals(item.getName())) {
               if (entry.getItem().getPrice() != item.getPrice()) {
                   throw new IllegalStateException("An existing entry has the same item name but a different price.");
               }
               entry.count += count;
               return true;
           }
       }
       entries.add(new Entry(item, count));
       return true;
   }

   public boolean addItems(String name, int count) throws IllegalArgumentException,
    NoSuchElementException {
       if (count <= 0) {
           throw new IllegalArgumentException("The item unit count must be positive.");
       }
       boolean itemFound = false;
       for (Entry entry : entries) {
           if (entry.getItem().getName().equals(name)) {
               entry.count += count;
               itemFound = true;
               break;
           }
       }
       if (!itemFound) {
           throw new NoSuchElementException("The order does not contain an entry with the specified item name.");
       }
       return true;
   }

   public List<Entry> getEntries() {
       return new ArrayList<>(entries); // Returning a copy of the list
   }

   public int getEntryCount() {
       return entries.size();
   }

   public int getItemCount() {
       return entries.stream().mapToInt(Entry::getCount).sum();
   }

   public double getTotalPrice() {
       return entries.stream().mapToDouble(entry -> entry.getCount() * entry.getItem().getPrice()).sum();
   }

   public boolean isEmpty() {
       return entries.isEmpty();
   }

   public boolean removeItems(String name, int count) throws IllegalArgumentException,
    NoSuchElementException {
       if (count <= 0) {
           throw new IllegalArgumentException("The item unit count must be positive and not larger than the existing entry's item unit count.");
       }
       for (Iterator<Entry> iterator = entries.iterator(); iterator.hasNext(); ) {
           Entry entry = iterator.next();
           if (entry.getItem().getName().equals(name)) {
               if (count > entry.getCount()) {
                   throw new IllegalArgumentException("The count to remove is greater than the existing count.");
               }
               entry.count -= count;
               if (entry.count == 0) {
                   iterator.remove();
               }
               return true;
           }
       }
       throw new NoSuchElementException("The order does not contain an entry with the specified item name.");
   }

    public static class Entry {
        private final Item item; // The item of this entry.
        private int count; // The item unit count of this entry.

        public Entry(Item item, int count) throws IllegalArgumentException {

            if (count <= 0) {
                throw new IllegalArgumentException("Item unit count must be positive.");
            }
            this.item = item;
            this.count = count;
        }

        public String getItemName() {
            return item.getName();
        }

        public double getUnitPrice() {
            return item.getPrice();
        }

        public Item getItem() {
            return item;
        }

        public int getCount() {
            return count;
        }

        @Override
        public String toString() {
            return count + " units of " + item.toString();
        }
    }

    public static class Item {
        private final String name;
        private final double price;

        public Item(String name, double price) throws IllegalArgumentException {
            if (name == null) {
                throw new IllegalArgumentException("Name cannot be null.");
            }
            if (price < 0) {
                throw new IllegalArgumentException("Price cannot be negative.");
            }
            this.name = name;
            this.price = price;
        }

        public String getName() {
            return name;
        }

        public double getPrice() {
            return price;
        }

        @Override
        public String toString() {
            return String.format(Locale.US,"Item(%s, %.2f)", name, price);
        }

        public boolean equals(Order.Item other) {
            if (other == null) return false;
            return name.equals(other.name);
        }
    }
    
    
}