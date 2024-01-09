/**
 *
 * @author lassi
 */

import java.util.Arrays;
import java.util.Scanner;

public class Median {
    
    public static void main(String[] args) {
        
        Scanner myScanner = new Scanner(System.in);
        
        System.out.println("Enter numbers:");
        
        String line = myScanner.nextLine();
        String[] numberStrings = line.split(" ");
        
        double[] numbers = new double[numberStrings.length];
        
        for (int i = 0; i < numberStrings.length; i++) {
            numbers[i] = Double.parseDouble(numberStrings[i]);
        }
        
        // Tällä saa järjestetyn taulukon...
        Arrays.sort(numbers);
        
        if (numbers.length % 2 == 0) {
            // Otetaan kaksi keskimmäistä lukua ja lasketaan niiden keskiarvo
            // ja tulostetaan se...
            double mid1 = numbers[(numbers.length / 2) - 1];
            double mid2 = numbers[numbers.length / 2];
            System.out.println("Median: " + (mid1 + mid2) / 2);
        } else {
            // Tulostetaan keskimmäinen arvo jos pariton määrä lukuja
            System.out.println("Median: " + numbers[numbers.length / 2]);
        }
    }
}
