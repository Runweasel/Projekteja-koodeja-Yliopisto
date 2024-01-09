/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package fi.tuni.prog3.weatherapp;


import java.util.List;
import java.util.Map;
import java.util.Scanner;

/**
 *
 * @author Sakari
 */
public class InfoTest {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter Country or City name: ");
        String loc = scanner.nextLine();
        scanner.close();

        // Create an instance of the FromAPI class
        FromAPI fromAPI = new FromAPI();

        Map.Entry<Double, Double> longAndLat = fromAPI.lookUpLocation(loc);

        // Replace these values with your actual latitude and longitude
        double longitude = longAndLat.getKey();
        double latitude = longAndLat.getValue();

        // Test 1: getCurrentWeather
        WeatherInfo currentWeather = fromAPI.getCurrentWeather(latitude, longitude);
        System.out.println("Date: "+ currentWeather.getDate());
        System.out.println("Current Weather Information:");
        System.out.println("Temperature: " + currentWeather.getTemperature() + "C");
        System.out.println("Feels Like: " + currentWeather.getFeelsLike() + "C");
        System.out.println("Min Temperature: " + currentWeather.getTempMin());
        System.out.println("Max Temperature: " + currentWeather.getTempMax());
        System.out.println("Pressure: " + currentWeather.getPressure());
        System.out.println("Humidity: " + currentWeather.getHumidity());
        System.out.println("Windspeed: " + currentWeather.getWindspeed()); // Add this line
        System.out.println("Rain Amount (1h): " + currentWeather.getRainAmount()); // Add this line
        System.out.println("Main Weather: " + currentWeather.getMainWeather());
        System.out.println("Description: " + currentWeather.getDescription());

        // Test 2: getForecast1h
        List<WeatherInfo> hourlyForecastList = fromAPI.getForecast1h(latitude, longitude);
        System.out.println("\nHourly Weather Forecast:");
        for (WeatherInfo forecast : hourlyForecastList) {
            System.out.println("Date: " + forecast.getDate());
            System.out.println("Temperature: " + forecast.getTemperature() + "C");
            System.out.println("Windspeed: " + forecast.getWindspeed()); // Add this line
            System.out.println("Humidity: " + forecast.getHumidity());
            System.out.println("Pressure: " + forecast.getPressure());
            System.out.println("Rain Amount (1h): " + forecast.getRainAmount()); // Add this line
            System.out.println("Main Weather: " + forecast.getMainWeather());
            System.out.println("Description: " + forecast.getDescription());
            System.out.println("------------------------");
        }

        // Test 3: getForecastdays for different amounts of days (1, 3, 5)
        for (int cnt : new int[]{1, 3, 10}) {
            List<WeatherInfo> forecastList = fromAPI.getForecastdays(latitude, longitude, cnt);

            System.out.println("\nForecast for " + cnt + " days:");
            for (WeatherInfo forecast : forecastList) {
                System.out.println("Date: " + forecast.getDate());
                System.out.println("max temp: " + forecast.getTempMax()+ "C");
                System.out.println("min temp: " + forecast.getTempMin()+ "C");
                System.out.println("Windspeed: " + forecast.getWindspeed()); // Add this line
                System.out.println("Rain Amount (day): " + forecast.getRainAmount()); // Add this line
                System.out.println("Humidity: " + forecast.getHumidity());
                System.out.println("Main Weather: " + forecast.getMainWeather());
                System.out.println("Description: " + forecast.getDescription());
                System.out.println("------------------------");
            }
        }
    }
        
}

