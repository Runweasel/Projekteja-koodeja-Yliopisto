package fi.tuni.prog3.datetime;

public class Date {

        private int year;
        private int month;
        private int day;
    
        // Julkinen rakentaja, joka ottaa vastaan päivämäärän
        // ja alustaa ne jäsenmuuttujiin
        public Date(int year, int month, int day) throws DateException {

            if (!isValidDate(year, month, day)) {
                throw new DateException(String.format("Illegal date %02d.%02d.%d", day, month, year));
            }

            this.year = year;
            this.month = month;
            this.day = day;
        }
    
        // Julkinen metodi vuoden hankkimiseksi
        public int getYear() {
            return year;
        }
    
        public int getMonth() {
            return month;
        }

        public int getDay() {
            return day;
        }

        public String toString() {

            return String.format("%02d.%02d.%d", day, month, year);
        }

        // Tarkistetaan, onko annettu päivämäärä laillinen
        private boolean isValidDate(int year, int month, int day) {

            if (month < 1 || month > 12) {
                return false;
            }

             int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            // Karkausvuoden tarkistus helmikuulle
            if (month == 2) {
                if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
                    daysInMonth[1] = 29;
                }
            }

            if (day < 1 || day > daysInMonth[month - 1]) {
                return false;
            }

            return true;
        }
}
