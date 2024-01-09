/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package fi.tuni.prog3.studentregister;
import java.util.*;

/**
 *
 * @author lassi
 */
public class StudentRegister {

    private List<Student> students = new ArrayList<>();
    private List<Course> courses = new ArrayList<>();
    private List<Attainment> attainments = new ArrayList<>();

    public StudentRegister() {
        // Alustaa tyhjän StudentRegister-olion
    }

    public List<Student> getStudents() {
        students.sort(Comparator.comparing(Student::getName));
        return new ArrayList<>(students);
    }

    public List<Course> getCourses() {
        courses.sort(Comparator.comparing(Course::getName));
        return new ArrayList<>(courses);
    }

    public void addStudent(Student student) {
        students.add(student);
    }

    public void addCourse(Course course) {
        courses.add(course);
    }

    public void addAttainment(Attainment attainment) {
        attainments.add(attainment);
    }

    public void printStudentAttainments(String studentNumber, String order) {
        Optional<Student> studentOpt = students.stream()
                .filter(s -> s.getStudentNumber().equals(studentNumber))
                .findFirst();

        if (studentOpt.isPresent()) {
            Student student = studentOpt.get();
            System.out.println(student.getName() + " (" + studentNumber + "):");

            List<Attainment> studentAttainments = getStudentAttainments(studentNumber);

            if (order.equals("by name")) {
                studentAttainments.sort(Comparator.comparing(att -> getCourseNameByCode(att.getCourseCode())));
            } else if (order.equals("by code")) {
                studentAttainments.sort(Comparator.comparing(Attainment::getCourseCode));
            }

            for (Attainment att : studentAttainments) {
                String courseName = getCourseNameByCode(att.getCourseCode());
                System.out.println("  " + att.getCourseCode() + " " + courseName + ": " + att.getGrade());
            }
        } else {
            System.out.println("Unknown student number: " + studentNumber);
        }
    }

    public void printStudentAttainments(String studentNumber) {
        printStudentAttainments(studentNumber, "");
    }

    private List<Attainment> getStudentAttainments(String studentNumber) {
        return new ArrayList<>(attainments.stream()
                .filter(a -> a.getStudentNumber().equals(studentNumber))
                .toList());
    }

    private String getCourseNameByCode(String courseCode) {
        return courses.stream()
                .filter(c -> c.getCode().equals(courseCode))
                .findFirst()
                .map(Course::getName)
                .orElse("Unknown course code");
    }
}
