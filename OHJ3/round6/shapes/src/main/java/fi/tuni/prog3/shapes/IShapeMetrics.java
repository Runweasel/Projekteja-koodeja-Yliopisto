package fi.tuni.prog3.shapes;

public interface IShapeMetrics {

    //    Jäsenmuuttuja double PI, joka esittää piin likiarvon viiden desimaalin tarkkuudella.
    public static final double PI = 3.14159;

    // Abstraktit jäsenfunktiot String name(), double area() ja double circumference().
    public abstract String name();
    public abstract double area();
    public abstract double circumference();

}
