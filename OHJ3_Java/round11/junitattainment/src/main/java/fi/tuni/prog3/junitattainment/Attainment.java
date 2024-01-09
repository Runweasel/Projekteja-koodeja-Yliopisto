package fi.tuni.prog3.junitattainment;

/**
 *
 * @author lassi
 */

public class Attainment implements Comparable<Attainment> {
    // Yksityiset jäsenmuuttujat kurssikoodin, opiskelijanumeron ja arvosanan tallentamiseksi
    private String courseCode;
    private String studentNumber;
    private int grade;

    // Julkinen rakentaja, joka ottaa vastaan kurssikoodin, opiskelijanumeron ja arvosanan
    // ja alustaa ne jäsenmuuttujiin
    public Attainment(String courseCode, String studentNumber, int grade) {
        
        System.out.println("Course Code: " + courseCode);
        System.out.println("Student Number: " + studentNumber);
        System.out.println("Grade: " + grade);
        System.out.println("");
        
        if (courseCode == null) {
            throw new IllegalArgumentException("Invalid course code");
        }
        if (studentNumber == null) {
            throw new IllegalArgumentException("Invalid student number");
        }
        if (grade < 0 || grade > 5) {
            throw new IllegalArgumentException("Invalid grade");
        }
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

    @Override
    public String toString() {
        return courseCode + " " + studentNumber + " " + grade;
    }

    @Override
    public int compareTo(Attainment other) {
        int result = this.studentNumber.compareTo(other.getStudentNumber());
        if (result == 0) {
            result = this.courseCode.compareTo(other.getCourseCode());
        }
        return result;
    }
}
