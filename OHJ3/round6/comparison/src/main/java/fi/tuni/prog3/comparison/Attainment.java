package fi.tuni.prog3.comparison;

import java.util.Comparator;

public class Attainment implements Comparable<Attainment> {

    // Rakennin Attainment(String courseCode, String studentNumber, int grade) alustaa 
    // Attainment-olioon rakentimen parametreina saamat kurssikoodin, opiskelijanumeron ja arvosanan.

    private String courseCode; 
    private String studentNumber; 
    private int grade;

    public Attainment(String courseCode, String studentNumber, int grade) {
        this.courseCode = courseCode;
        this.studentNumber = studentNumber;
        this.grade = grade;
    }

    // Jäsenfunktiot getCourseCode(), getStudentNumber() ja getGrade() palauttavat suorituksen kurssikoodin ja opiskelijanumeron, 
    // jotka ovat String-merkkijonoja sekä arvosanan, joka on int-arvo.

    public String getCourseCode() {
        return courseCode;
    }

    public String getStudentNumber() {
        return studentNumber;
    }

    public int getGrade() {
        return grade;
    }

    // Jäsenfunktio String toString(), joka korvaa yliluokalta Object perityn oletusversion. 
    // Funktio palauttaa kurssisuoritusta kuvaavan muotoa “kurssikoodi opiskelijanumero arvosana” olevan merkkijonon.

    @Override
    public String toString() {
        return courseCode + " " + studentNumber + " " + grade;
    }


    // Toteuta funktio compareTo siten, että se vertailee ensisijaisesti opiskelijanumeroita ja toissijaisesti kurssikoodeja. 
    // Tee sekä opiskelijanumeron että kurssikoodin vertailu String-luokan compareTo-funktiolla.

    @Override
    public int compareTo(Attainment other) {
        int comparisonResult = this.studentNumber.compareTo(other.studentNumber);

        if (comparisonResult == 0) {
            comparisonResult = this.courseCode.compareTo(other.courseCode);
        }

        return comparisonResult;
    }

    // Julkiset luokkavakiot:

    // Comparator<Attainment> CODE_STUDENT_CMP
    // Rajapinnan Comparator<Attainment> toteuttava olio, jonka jäsenfunktio compare vertailee 
    // kahta Attainment-oliota ensisijaisesti kurssikoodin ja toissijaisesti opiskelijanumeron perusteella.

    public static final Comparator<Attainment> CODE_STUDENT_CMP = new Comparator<Attainment>() {

        @Override
        public int compare(Attainment o1, Attainment o2) {
            int comparisonResult = o1.getCourseCode().compareTo(o2.getCourseCode());


            if (comparisonResult == 0) {
                comparisonResult = o1.getStudentNumber().compareTo(o2.getStudentNumber());
            }

            return comparisonResult;
        }
    };

    // Comparator<Attainment> CODE_GRADE_CMP
    // Rajapinnan Comparator<Attainment> toteuttava olio, jonka jäsenfunktio compare vertailee 
    // kahta Attainment-oliota ensisijaisesti kurssikoodin ja toissijaisesti kurssiarvosanan perusteella. 
    // Kurssiarvosanoja verrataan käänteisesti (tulevat laskevaan järjestykseen).

    public static final Comparator<Attainment> CODE_GRADE_CMP = new Comparator<Attainment>() {
        
        @Override
        public int compare(Attainment o1, Attainment o2) {
            int comparisonResult = o1.getCourseCode().compareTo(o2.getCourseCode());

            if (comparisonResult == 0) {
                comparisonResult = o2.getGrade() - o1.getGrade();
            }

            return comparisonResult;
        }

    };


}