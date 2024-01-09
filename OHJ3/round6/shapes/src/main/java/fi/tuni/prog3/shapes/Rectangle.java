package fi.tuni.prog3.shapes;


// Luokka Rectangle, joka toteuttaa rajapinnan IShapeMetrics ja 
// tallentaa suorakulmion korkeuden ja leveyden double-tyyppisinä arvoina.

public class Rectangle implements IShapeMetrics {

    private double height;
    private double width;

    // Rakennin Rectangle(double height, double width), joka asettaa pituuden ja leveyden.
    public Rectangle(double height, double width) {
        this.height = height;
        this.width = width;
    }

    // Jäsenfunktio String toString(), joka korvaa yliluokalta Object perityn oletusversion. 
    // Funktio palauttaa merkkijonon “Rectangle with height x and width y”, jossa 
    // x on suorakulmion korkeus ja y suorakulmion leveys kahden desimaalin tarkkuudella.
    @Override
    public String toString() {
        return String.format("Rectangle with height %.2f and width %.2f", height, width);
    }

    // Jäsenfunktio String name(), joka palauttaa merkkijonon “rectangle”.
    @Override
    public String name() {
        return "rectangle";
    }

    // Jäsenfunktio double area(), joka palauttaa suorakulmion pinta-alan.
    @Override
    public double area() {
        return height * width;
    }

    // Jäsenfunktio double circumference(), joka palauttaa suorakulmion piirin.
    @Override
    public double circumference() {
        return 2 * (height + width);
    }

}
