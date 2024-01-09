package fi.tuni.prog3.junitattainment;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author lassi
 */
public class AttainmentTest {
    
    public AttainmentTest() {
    }
    
    @BeforeAll
    public static void setUpClass() {
    }
    
    @AfterAll
    public static void tearDownClass() {
    }
    
    @BeforeEach
    public void setUp() {
    }
    
    @AfterEach
    public void tearDown() {
    }

    // Testaa, että kun Attainment-olio on luotu, funktioiden getCourseCode, 
    // getStudentNumber ja getGrade palauttamat arvot täsmäävät rakentajalle 
    // välitettyjen arvojen kanssa.
    
    @Test
    public void testValuesReturnedByGettersMatchConstructorParameters() {
        // Arrange
        String expectedCourseCode = "PROG3";
        String expectedStudentNumber = "123456";
        int expectedGrade = 4;
        
        // Act
        Attainment attainment = new Attainment(expectedCourseCode, expectedStudentNumber, expectedGrade);
        
        // Assert
        assertEquals(expectedCourseCode, attainment.getCourseCode(), "CourseCode mismatch!");
        assertEquals(expectedStudentNumber, attainment.getStudentNumber(), "StudentNumber mismatch!");
        assertEquals(expectedGrade, attainment.getGrade(), "Grade mismatch!");
    }

    @Test
    public void testConstructorExceptions() {
        assertThrows(IllegalArgumentException.class, () -> new Attainment(null, "123456", 5));
        assertThrows(IllegalArgumentException.class, () -> new Attainment("PROG3", null, 5));
        assertThrows(IllegalArgumentException.class, () -> new Attainment("PROG3", "123456", 6));
        assertThrows(IllegalArgumentException.class, () -> new Attainment("PROG3", "123456", -1));
    }

    @Test
    public void testToString() {
        Attainment a = new Attainment("C123", "12345", 4);
        assertEquals("C123 12345 4", a.toString());
    }

    @Test
    public void testCompareTo() {
        Attainment instance1 = new Attainment("PROG3", "123456", 4);
        Attainment instance2 = new Attainment("PROG3", "123457", 3);
        Attainment instance3 = new Attainment("PROG4", "123456", 2);
                
        assertTrue(instance1.compareTo(instance2) < 0);
        assertTrue(instance1.compareTo(instance3) < 0);
        assertTrue(instance2.compareTo(instance1) > 0);
        assertTrue(instance3.compareTo(instance1) > 0);
        
        assertEquals(0, instance1.compareTo(instance1));
    }
}
