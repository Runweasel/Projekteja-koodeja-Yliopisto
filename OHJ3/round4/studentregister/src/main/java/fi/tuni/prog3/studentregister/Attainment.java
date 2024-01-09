/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package fi.tuni.prog3.studentregister;

/**
 *
 * @author lassi
 */
public class Attainment {
    // Yksityiset jäsenmuuttujat kurssikoodin, opiskelijanumeron ja arvosanan tallentamiseksi
    private String courseCode;
    private String studentNumber;
    private int grade;

    // Julkinen rakentaja, joka ottaa vastaan kurssikoodin, opiskelijanumeron ja arvosanan
    // ja alustaa ne jäsenmuuttujiin
    public Attainment(String courseCode, String studentNumber, int grade) {
        this.courseCode = courseCode;
        this.studentNumber = studentNumber;
        this.grade = grade;
    }

    // Julkinen metodi kurssikoodin hankkimiseksi
    public String getCourseCode() {
        return courseCode;
    }

    // Julkinen metodi opiskelijanumeron hankkimiseksi
    public String getStudentNumber() {
        return studentNumber;
    }

    // Julkinen metodi arvosanan hankkimiseksi
    public int getGrade() {
        return grade;
    }
}
