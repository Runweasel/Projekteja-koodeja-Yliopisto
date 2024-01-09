/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

import java.util.Scanner;

/**
 *
 * @author lassi
 */
public class Mean {

    public static void main(String[] args) {
        
        Scanner myScanner = new Scanner(System.in);
        
        System.out.println("Enter numbers:");
        
        String line = myScanner.nextLine();
        String[] numbers = line.split(" ");
        
        double sum = 0;
        
        for (int i = 0; i < numbers.length; i++) {
        double num = Double.parseDouble(numbers[i]);
        sum += num;
        }
        
        double mean = sum / numbers.length;
        
        System.out.println("Mean: " + mean);
    }
}
