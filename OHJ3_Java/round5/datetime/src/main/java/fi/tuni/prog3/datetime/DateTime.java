package fi.tuni.prog3.datetime;

public class DateTime extends Date
{

    private int hour;
    private int minute;
    private int second;

    public DateTime(int year, int month, int day, int hour, int minute, int second) throws DateException {

        super(year, month, day);

        if (!isValidTime(hour, minute, second)) {
            throw new DateException(String.format("Illegal time %02d:%02d:%d", hour, minute, second));
        }

        this.hour = hour;
        this.minute = minute;
        this.second = second;
    }

    // Julkiset metodit

    public int getHour() {
        return hour;
    }

    public int getSecond() {
        return second;
    }

    public int getMinute() {
        return minute;
    }

    public String toString() {
        return String.format("%s %02d:%02d:%02d", super.toString(), hour, minute, second);
    }

    // Tarkistetaan, onko annettu päivämäärä laillinen
    private boolean isValidTime(int hour, int minute, int second) {

        if (hour < 0 || hour > 23) {
            return false;
        }

        if (minute < 0 || minute > 59) {
            return false;
        }

        if (second < 0 || second > 59) {
            return false;
        }

        return true;
    }
    
}
