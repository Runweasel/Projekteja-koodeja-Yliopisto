/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;


/**
 * Connects and read the JSON file from API with other methods
 * @author Sakari
 */


public  class FromAPI implements iAPI {
     private ReadAndWrite readAndWrite = new ReadAndWrite(); 

     
     /**
     * Returns coordinates for a location.
     * @param loc Name of the location for which coordinates should be fetched.
     * @return Map.Entry<Double, Double>.
     */
    @Override
    public Map.Entry<Double, Double> lookUpLocation(String loc) {
        try {
            // Connect to API
            String apiKey = "888acf8f67ca6781e6eeb48e54f5d20b";
            
            String apiUrl = "http://api.openweathermap.org/geo/1.0/direct?q=" + loc + "&limit=1&appid=" + apiKey;

            URL url = new URL(apiUrl);
            
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();

            connection.setRequestMethod("GET");

            int responseCode = connection.getResponseCode();

            if (responseCode == HttpURLConnection.HTTP_OK) {
                // Read the response
                BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                StringBuilder response = new StringBuilder();
                String line;

                while ((line = reader.readLine()) != null) {
                    response.append(line);
                }

                reader.close();
                // Parse response
                JsonArray jsonArray = JsonParser.parseString(response.toString()).getAsJsonArray();
                
                // Check if the JSON array is empty
                if (jsonArray.size() == 0) {
                    return null;
                }

                JsonObject firstResult = jsonArray.get(0).getAsJsonObject();

                double latitude = firstResult.get("lat").getAsDouble();
                double longitude = firstResult.get("lon").getAsDouble();

            return new AbstractMap.SimpleEntry<>(longitude, latitude);
            } else {
                System.out.println("Error: " + responseCode);
                return null;
            }
        } catch (UnknownHostException e) {
            System.out.println("No Internet connection available.");
            return null;
        } catch (IOException e) {
            System.out.println("Error connecting to the API: " + e.getMessage());
            return null;
        }
    }

    /**
     * Returns the current weather for the given coordinates.
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @return WeatherInfo object.
     */
     @Override
    public WeatherInfo getCurrentWeather(double lat, double lon) {
        try {
            // Connect to API
            String apiKey = "888acf8f67ca6781e6eeb48e54f5d20b";

            String apiUrl = "https://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + apiKey;

            URL url = new URL(apiUrl);

            HttpURLConnection connection = (HttpURLConnection) url.openConnection();

            connection.setRequestMethod("GET");
            
            int responseCode = connection.getResponseCode();

            InputStream inputStream = connection.getInputStream();

            // Use readFromAPI to parse the data
            WeatherInfo info = readAndWrite.readFromAPI(responseCode, inputStream);

            connection.disconnect();

            return info;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }   

    /**
     * Returns a forecast for the given coordinates for 1h intervals.
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @return List<WeatherInfo>.
     */
        @Override
    public List<WeatherInfo> getForecast1h(double lat, double lon) {
    List<WeatherInfo> forecastList = new ArrayList<>();
    try {
        // connect to API
        String apiKey = "888acf8f67ca6781e6eeb48e54f5d20b";

        String apiUrl = "https://pro.openweathermap.org/data/2.5/forecast/hourly?lat=" + lat + "&lon=" + lon + "&appid=" + apiKey;

            URL url = new URL(apiUrl);

            HttpURLConnection connection = (HttpURLConnection) url.openConnection();

            connection.setRequestMethod("GET");

            int responseCode = connection.getResponseCode();

            InputStream inputStream = connection.getInputStream();

            // Uses readForecatsFromAPI to parse the data
            forecastList = readAndWrite.readForecastFromAPI(responseCode, inputStream, true);

            connection.disconnect();
        } catch (Exception e) {
            e.printStackTrace();
        }
    return forecastList;
    }
    
    /**
     * Returns a forecast avarages for the given coordinates for days intervals.
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param cnt How many days you want to get from the API.
     * @return List<WeatherInfo>.
     */
     @Override
    public List<WeatherInfo> getForecastdays(double lat, double lon, int cnt) {
        
        if (cnt <= 0) {
        // Handle invalid count. Return an empty list or a custom error.
        return new ArrayList<>();
        }
        List<WeatherInfo> forecastList = new ArrayList<>();
        try {

            // connect to API
            String apiKey = "888acf8f67ca6781e6eeb48e54f5d20b";

            String apiUrl = "https://api.openweathermap.org/data/2.5/forecast/daily?lat=" + lat +
                                "&lon=" + lon + "&cnt=" + cnt + "&appid=" + apiKey;

            URL url = new URL(apiUrl);

            HttpURLConnection connection = (HttpURLConnection) url.openConnection();

            connection.setRequestMethod("GET");

            int responseCode = connection.getResponseCode();

            InputStream inputStream = connection.getInputStream();

            // Uses readForecatsFromAPI to parse the data
            forecastList = readAndWrite.readForecastFromAPI(responseCode, inputStream, false);

            connection.disconnect();
            } catch (Exception e) {
                e.printStackTrace();
            }
        return forecastList;
    }
    
}
