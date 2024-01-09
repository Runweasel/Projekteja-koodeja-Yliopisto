/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package fi.tuni.prog3.studentregister;

/**
 *
 * @author lassi
 */
public class Course {

    // Yksityiset jäsenmuuttujat kurssin koodin, nimen ja laajuuden (opintopisteet) tallentamiseksi
    private String code;
    private String name;
    private int credits;

    // Julkinen rakentaja, joka ottaa vastaan koodin, nimen ja opintopistemäärän
    // ja alustaa ne jäsenmuuttujiin
    public Course(String code, String name, int credits) {
        this.code = code;
        this.name = name;
        this.credits = credits;
    }

    // Julkinen metodi koodin hankkimiseksi
    public String getCode() {
        return code;
    }

    // Julkinen metodi nimen hankkimiseksi
    public String getName() {
        return name;
    }

    // Julkinen metodi opintopistemäärän hankkimiseksi
    public int getCredits() {
        return credits;
    }
}
