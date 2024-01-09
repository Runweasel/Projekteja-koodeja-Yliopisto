package fi.tuni.prog3.shapes;

public class Circle implements IShapeMetrics {

    private double radius;

    // Rakennin Circle(double radius), joka asettaa säteen arvon.
    public Circle(double radius) {
        this.radius = radius;
    }

    // Jäsenfunktio String toString(), joka korvaa yliluokalta Object perityn oletusversion. 
    // Funktio palauttaa merkkijonon “Circle with radius: x”, jossa x on säteen arvo kahden desimaalin tarkkuudella.
    @Override
    public String toString() {
        return String.format("Circle with radius: %.2f", radius);
    }

    // Jäsenfunktio String name(), joka palauttaa merkkijonon “circle”.
    @Override
    public String name() {
        return "circle";
    }

    // Jäsenfunktio double area(), joka palauttaa ympyrän pinta-alan, jonka laskennassa on käytetty piin likiarvoa PI.
    @Override
    public double area() {
        return PI * radius * radius;
    }

    // Jäsenfunktio double circumference(), joka palauttaa ympyrän piirin, jonka laskennassa on käytetty piin likiarvoa PI.
    @Override
    public double circumference() {
        return 2 * PI * radius;
    }

}