/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.List;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

/**
 * Test class for ReadAndWrite. This class contains unit tests to verify the functionality of the ReadAndWrite methods for reading and writing weather data.
 */
public class ReadAndWriteTest {

    /**
     * Test parsing of current weather data from a JSON stream.
     */
    @Test
    public void testReadAndParseCurrent() throws Exception {

        String currentWeatherJson = "{\"main\":{\"temp\":298.15,\"feels_like\":298.15,\"temp_min\":297.15,\"temp_max\":299.15,\"pressure\":1015,\"humidity\":50},\"wind\":{\"speed\":3.5},\"rain\":{\"1h\":0.5},\"weather\":[{\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}]}";
        InputStream inputStream = new ByteArrayInputStream(currentWeatherJson.getBytes());

        ReadAndWrite instance = new ReadAndWrite();
        WeatherInfo result = instance.readAndParseCurrent(inputStream);

        assertNotNull(result);
        assertEquals(25.0, result.getTemperature()); // Check temperature in Celsius
        assertEquals(25.0, result.getFeelsLike()); // Check 'feels_like' temperature in Celsius
    }

    /**
     * Test parsing of hourly weather forecast data from a JSON stream.
     */
    @Test
    public void testReadAndParseHourlyForecast() throws Exception {
        String hourlyForecastJson = "{\"list\":[{\"main\":{\"temp\":298.15,\"feels_like\":298.15,\"temp_min\":297.15,\"temp_max\":299.15,\"pressure\":1015,\"humidity\":50},\"wind\":{\"speed\":3.5},\"rain\":{\"1h\":0.5},\"weather\":[{\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}],\"dt_txt\":\"2023-12-08 12:00:00\"}]}";
        InputStream inputStream = new ByteArrayInputStream(hourlyForecastJson.getBytes());

        ReadAndWrite instance = new ReadAndWrite();
        List<WeatherInfo> result = instance.readAndParseHourlyForecast(inputStream);

        assertNotNull(result);
        assertEquals(1, result.size());
    }

    /**
     * Test parsing of daily weather forecast data from a JSON stream.
     */
    @Test
    public void testReadAndParsedaysForecast() throws Exception {
        String dailyForecastJson = "{\"list\":[{\"temp\":{\"min\":297.15,\"max\":299.15},\"humidity\":50,\"speed\":3.5,\"rain\":0.5,\"weather\":[{\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}],\"dt\":\"1672531200\"}]}";
        InputStream inputStream = new ByteArrayInputStream(dailyForecastJson.getBytes());

        ReadAndWrite instance = new ReadAndWrite();
        List<WeatherInfo> result = instance.readAndParsedaysForecast(inputStream);

        assertNotNull(result);
        assertEquals(1, result.size());
    }

    /**
     * Test reading weather data from an API response for a successful HTTP request.
     */
    @Test
    public void testReadFromAPI() throws Exception {
        int responseCode = 200; // HTTP OK
        String currentWeatherJson = "{\"main\":{\"temp\":298.15,\"feels_like\":298.15,\"temp_min\":297.15,\"temp_max\":299.15,\"pressure\":1015,\"humidity\":50},\"wind\":{\"speed\":3.5},\"rain\":{\"1h\":0.5},\"weather\":[{\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}]}";
        InputStream inputStream = new ByteArrayInputStream(currentWeatherJson.getBytes());

        ReadAndWrite instance = new ReadAndWrite();
        WeatherInfo result = instance.readFromAPI(responseCode, inputStream);

        assertNotNull(result);
        assertEquals(25.0, result.getTemperature());
        assertEquals(25.0, result.getFeelsLike());
    }

    /**
     * Test reading weather forecast data from an API response, with a flag to determine the forecast type.
     */
    @Test
    public void testReadForecastFromAPI() throws Exception {
        int responseCode = 200;
        boolean flag = true; 

        String hourlyForecastJson = "{\"list\":[{\"main\":{\"temp\":298.15,\"feels_like\":298.15,\"temp_min\":297.15,\"temp_max\":299.15,\"pressure\":1015,\"humidity\":50},\"wind\":{\"speed\":3.5},\"rain\":{\"1h\":0.5},\"weather\":[{\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}],\"dt_txt\":\"2023-12-08 12:00:00\"}]}";
        InputStream inputStream = new ByteArrayInputStream(hourlyForecastJson.getBytes());

        ReadAndWrite instance = new ReadAndWrite();
        List<WeatherInfo> result = instance.readForecastFromAPI(responseCode, inputStream, flag);

        assertNotNull(result);
        assertEquals(1, result.size());
    }

    /**
     * Test writing a list of strings to a file, simulating saving of application data.
     */
    @Test
    public void testWriteToFileFromList() throws Exception {
        ObservableList<String> data = FXCollections.observableArrayList("Item 1", "Item 2", "Item 3");
        String fileName = "testFile.json";

        ReadAndWrite instance = new ReadAndWrite();
        boolean result = instance.writeToFileFromList(data, fileName);

        assertTrue(result);
    }

    /**
     * Test reading a list of strings from a file, simulating loading of application data.
     */
    @Test
    public void testReadMemory() {
        String fileName = "testFile.json";

        ReadAndWrite instance = new ReadAndWrite();
        ObservableList<String> result = instance.readMemory(fileName);

        assertNotNull(result);
    }
    
    /**
     * Test handling of non-successful HTTP response codes in readFromAPI method.
     */
    @Test
    public void testReadFromAPIWithErrorResponse() throws Exception {
        int responseCode = 404; // HTTP Not Found
        InputStream inputStream = new ByteArrayInputStream("".getBytes());

        ReadAndWrite instance = new ReadAndWrite();
        WeatherInfo result = instance.readFromAPI(responseCode, inputStream);

        assertNull(result, "Method should return null for non-200 response codes");
    }
    
}
