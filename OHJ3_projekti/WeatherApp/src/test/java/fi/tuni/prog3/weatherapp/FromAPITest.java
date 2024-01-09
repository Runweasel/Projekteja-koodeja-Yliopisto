/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package fi.tuni.prog3.weatherapp;


import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.Map;

/**
 * Test class for FromAPI. This class contains unit tests to verify the correct functionality of the FromAPI methods.
 */
public class FromAPITest {

    /**
     * Test whether the lookUpLocation method returns non-null coordinates for a valid location.
     */
    @Test
    public void testLookUpLocation() {
        String loc = "Tampere"; 
        FromAPI instance = new FromAPI();
        Map.Entry<Double, Double> result = instance.lookUpLocation(loc);

        assertNotNull(result);
    }

    /**
     * Test whether the getCurrentWeather method returns non-null weather information for valid coordinates.
     */
    @Test
    public void testGetCurrentWeather() {
        double lat = 40.7128; 
        double lon = -74.0060; 
        FromAPI instance = new FromAPI();
        WeatherInfo result = instance.getCurrentWeather(lat, lon);

        assertNotNull(result);
        
    }

    /**
     * Test whether the getForecast1h method returns non-null hourly forecast information for valid coordinates.
     */
    @Test
    public void testGetForecast1h() {
        double lat = 40.7128; 
        double lon = -74.0060; 
        FromAPI instance = new FromAPI();
        List<WeatherInfo> result = instance.getForecast1h(lat, lon);

        assertNotNull(result);
        
    }

    /**
     * Test whether the getForecastdays method returns non-null daily forecast information for valid coordinates and count.
     */
    @Test
    public void testGetForecastdays() {
        double lat = 40.7128; 
        double lon = -74.0060; 
        int cnt = 5; 
        FromAPI instance = new FromAPI();
        List<WeatherInfo> result = instance.getForecastdays(lat, lon, cnt);

        assertNotNull(result); 
    }
    
    /**
     * Test whether the lookUpLocation method returns null for an invalid location.
     */
    @Test
    public void testLookUpLocationInvalid() {
        String loc = "InvalidLocation"; 
        FromAPI instance = new FromAPI();
        Map.Entry<Double, Double> result = instance.lookUpLocation(loc);

        assertNull(result, "Method should return null for invalid location");
    }

    /**
     * Test whether the getForecastdays method returns non-null results for valid coordinates and a valid count value.
     */
    @Test
    public void testGetForecastdaysWithValidCount() {
        double lat = 40.7128; 
        double lon = -74.0060; 
        int cnt = 5; // Valid count value
        FromAPI instance = new FromAPI();
        List<WeatherInfo> result = instance.getForecastdays(lat, lon, cnt);

        assertNotNull(result, "Result should not be null for a valid count");
    }
    
    /**
     * Test whether the getForecastdays method returns an empty result for valid coordinates but a negative count value.
     */
    @Test
    public void testGetForecastdaysWithNegativeCount() {
        double lat = 40.7128; 
        double lon = -74.0060; 
        int cnt = -1; // Negative count value
        FromAPI instance = new FromAPI();
        List<WeatherInfo> result = instance.getForecastdays(lat, lon, cnt);

        assertTrue(result.isEmpty(), "Result should be empty for a negative count");
    }

}
