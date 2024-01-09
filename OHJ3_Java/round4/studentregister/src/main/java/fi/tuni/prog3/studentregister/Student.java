/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package fi.tuni.prog3.studentregister;

/**
 *
 * @author lassi
 */
public class Student {
        // Yksityiset jäsenmuuttujat opiskelijan nimen ja numeron tallentamiseksi
        private String name;
        private String studentNumber;
    
        // Julkinen rakentaja, joka ottaa vastaan nimen ja opiskelijanumeron
        // ja alustaa ne jäsenmuuttujiin
        public Student(String name, String studentNumber) {
            this.name = name;
            this.studentNumber = studentNumber;
        }
    
        // Julkinen metodi nimen hankkimiseksi
        public String getName() {
            return name;
        }
    
        // Julkinen metodi opiskelijanumeron hankkimiseksi
        public String getStudentNumber() {
            return studentNumber;
        }
}
