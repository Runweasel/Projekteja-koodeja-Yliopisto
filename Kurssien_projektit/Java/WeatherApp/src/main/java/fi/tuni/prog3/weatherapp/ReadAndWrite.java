/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonPrimitive;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;




/**
 * Many methods for reading writting and parsing data form JSON files
 * @author Sakari
 */
public class ReadAndWrite implements iReadAndWriteToFile {

    
    /**
     * Parses and saves the weather data from inputsream
     * @param inputStream JSON inputstream
     * @return WeatherInfo object
     * @throws java.io.IOException
     */
        @Override
        public WeatherInfo readAndParseCurrent(InputStream inputStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        StringBuilder response = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null) {
            response.append(line);
        }

        reader.close();

        JsonObject jsonResponse = JsonParser.parseString(response.toString()).getAsJsonObject();

        // Safely extract data from JSON and read to object
        JsonObject mainObject = jsonResponse.getAsJsonObject("main");
        double temperature = getJsonDouble(mainObject, "temp", 273.15) - 273.15;
        double feelsLike = getJsonDouble(mainObject, "feels_like", 273.15) - 273.15;
        double tempMin = getJsonDouble(mainObject, "temp_min", 273.15) - 273.15;
        double tempMax = getJsonDouble(mainObject, "temp_max", 273.15) - 273.15;
        int pressure = getJsonInt(mainObject, "pressure", 0);
        int humidity = getJsonInt(mainObject, "humidity", 0);

        JsonObject windObject = jsonResponse.getAsJsonObject("wind");
        double windSpeed = getJsonDouble(windObject, "speed", 0);

        JsonObject rainObject = jsonResponse.getAsJsonObject("rain");
        double rainAmount = getJsonDouble(rainObject, "1h", 0);
       
        JsonArray weatherArray = jsonResponse.getAsJsonArray("weather");
        JsonObject weatherItem = weatherArray.get(0).getAsJsonObject();
        String mainWeather = weatherItem.get("main").getAsString();
        String description = weatherItem.get("description").getAsString();
        String icon = weatherItem.get("icon").getAsString();
        
        // Find date for current weather and format it
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("E d.MM 'at' H:mm", Locale.forLanguageTag("en-US"));
        String date = now.format(formatter);

        return new WeatherInfo(temperature, feelsLike, tempMin, tempMax, pressure, humidity, windSpeed, rainAmount, mainWeather, description, icon, date);
    }
    
    /**
     * Parses and saves the weather data from inputsream
     * @param inputStream JSON inputstream
     * @return List<WeatherInfo> list of weather objects 
     * @throws java.io.IOException 
     */
    @Override 
    public List<WeatherInfo> readAndParseHourlyForecast(InputStream inputStream) throws IOException {
    // API response
    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
    StringBuilder response = new StringBuilder();
    String line;

    while ((line = reader.readLine()) != null) {
        response.append(line);
    }

    reader.close();

    // Parse JSON response
    JsonObject jsonResponse = JsonParser.parseString(response.toString()).getAsJsonObject();

    // Extract the list of hourly forecasts
    JsonArray forecastArray = jsonResponse.getAsJsonArray("list");
    List<WeatherInfo> forecastList = new ArrayList<>();

    // Loop through hourly forecasts and read JSON into objects
    // takes next 24 hours can be changed to anything
    for (int i = 0; i < Math.min(25, forecastArray.size()); i++) {
        JsonElement element = forecastArray.get(i);
        JsonObject forecastObject = forecastArray.get(i).getAsJsonObject();

        double temperature_in_K = forecastObject.getAsJsonObject("main").get("temp").getAsDouble();
        double feelsLike_in_K = forecastObject.getAsJsonObject("main").get("feels_like").getAsDouble();
        double tempMin_in_K = forecastObject.getAsJsonObject("main").get("temp_min").getAsDouble();
        double tempMax_in_K = forecastObject.getAsJsonObject("main").get("temp_max").getAsDouble();
        int pressure = forecastObject.getAsJsonObject("main").get("pressure").getAsInt();
        int humidity = forecastObject.getAsJsonObject("main").get("humidity").getAsInt();
        
        JsonElement windElement = forecastObject.getAsJsonObject("wind");
        double windspeed = (windElement != null && windElement.isJsonObject()) ? windElement.getAsJsonObject().get("speed").getAsDouble() : 0.0;

        JsonElement rainElement = forecastObject.getAsJsonObject("rain");
        double rainAmount = (rainElement != null && rainElement.isJsonObject() && rainElement.getAsJsonObject().has("1h")) ? rainElement.getAsJsonObject().get("1h").getAsDouble() : 0.0;

        // Extract other weather details
        String mainWeather = forecastObject.getAsJsonArray("weather").get(0).getAsJsonObject().get("main").getAsString();
        String description = forecastObject.getAsJsonArray("weather").get(0).getAsJsonObject().get("description").getAsString();
        String icon = forecastObject.getAsJsonArray("weather").get(0).getAsJsonObject().get("icon").getAsString();
        String notformatteddate = forecastObject.get("dt_txt").getAsString();
        
        //Format Date
        LocalDateTime dateTime = LocalDateTime.parse(notformatteddate, DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("E d.MM 'at' H:mm", Locale.forLanguageTag("en-US"));
        String date = dateTime.format(formatter);

        // Convert temperatures to Celsius
        double temperature = temperature_in_K - 273.15;
        double feelsLike = feelsLike_in_K - 273.15;
        double tempMin = tempMin_in_K - 273.15;
        double tempMax = tempMax_in_K - 273.15;

        // Create and add WeatherInfo object to the list
        forecastList.add(new WeatherInfo(temperature, feelsLike, tempMin, tempMax, pressure, humidity, windspeed, rainAmount, mainWeather, description, icon, date));
    }

    return forecastList;
}
   
    /**
     * Parses and saves the weather data from inputsream
     * @param inputStream JSON inputstream
     * @return List<WeatherInfo> list of weather objects
     * @throws java.io.IOException
     */
@Override
public List<WeatherInfo> readAndParsedaysForecast(InputStream inputStream) throws IOException {
    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
    StringBuilder response = new StringBuilder();
    String line;

    while ((line = reader.readLine()) != null) {
        response.append(line);
    }

    reader.close();

    // Parse JSON response
    JsonObject jsonResponse = JsonParser.parseString(response.toString()).getAsJsonObject();
    JsonArray forecastArray = jsonResponse.getAsJsonArray("list");
    List<WeatherInfo> forecastList = new ArrayList<>();

    // Loop through daily forecasts and extract info
    for (int i = 0; i < forecastArray.size(); i++) {
        JsonObject forecastObject = forecastArray.get(i).getAsJsonObject();

        JsonObject temperatureObject = forecastObject.getAsJsonObject("temp");
        double tempMin_in_K = temperatureObject.get("min").getAsDouble();
        double tempMax_in_K = temperatureObject.get("max").getAsDouble();
        JsonObject firstListItem = forecastArray.get(i).getAsJsonObject();
        int humidity = firstListItem.get("humidity").getAsInt();    


        JsonElement windElement = forecastObject.get("speed");
        double windSpeed = windElement.getAsJsonPrimitive().getAsDouble();
        JsonArray weatherArray = forecastObject.getAsJsonArray("weather");
        JsonObject weatherObject = weatherArray.get(0).getAsJsonObject();

        double rainAmount = 0.0;  // Default value if rain information is not available

        JsonElement rainElement = forecastObject.get("rain");
        
        if (rainElement != null && rainElement.isJsonPrimitive()) {
            rainAmount = rainElement.getAsJsonPrimitive().getAsDouble();
        }

        // Extract other weather details
        String mainWeather = weatherObject.get("main").getAsString();
        String description = weatherObject.get("description").getAsString();
        String icon = weatherObject.get("icon").getAsString();

        // Convert temperatures to Celsius
        double tempMin = tempMin_in_K - 273.15;
        double tempMax = tempMax_in_K - 273.15;
        
        long dtTimestamp = forecastObject.get("dt").getAsLong();
        LocalDateTime dateTime = LocalDateTime.ofInstant(Instant.ofEpochSecond(dtTimestamp), ZoneId.of("UTC"));

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("E d.MM", Locale.forLanguageTag("en-US"));
        String date = dateTime.format(formatter);

        // Create and add WeatherInfo object to the list
        forecastList.add(new WeatherInfo(0, 0, tempMin, tempMax, 0, humidity, windSpeed, rainAmount, mainWeather, description, icon, date ));
    }
    return forecastList;
}
    
    /**
     * Reads JSON from the current weather API.
     * @param responseCode API response
     * @param inputStream JSON inputstream
     * @return WeatherInfo object
     * @throws Exception if the method cannot find the file. 
     */
        @Override
    public WeatherInfo readFromAPI(int responseCode, InputStream inputStream) throws Exception {
    if (responseCode == HttpURLConnection.HTTP_OK) {
        return readAndParseCurrent(inputStream);
    } else {
        
        System.out.println("Error: " + responseCode);
        return null;
    }
}
    /**
     * Reads JSON of the forecat APIs
     * @param responseCode API response
     * @param inputStream JSON inputstream
     * @param flag flag for mode switching
     * @return List<WeatherInfo> List of info objects.
     * @throws Exception if the method cannot find the file.
     */
        @Override
    public List<WeatherInfo> readForecastFromAPI(int responseCode, InputStream inputStream, boolean flag) throws Exception {
    if (responseCode == HttpURLConnection.HTTP_OK) {
        if (flag){
           return readAndParseHourlyForecast(inputStream);  
        }
        else{
            return readAndParsedaysForecast(inputStream);
        }  
    } else {
        System.out.println("Error: " + responseCode);
        return null;
    }
}

    /**
     * Write the student progress as JSON into the given file.
     * @param data List for memory
     * @param fileName name of the file to write to.
     * @return true if the write was successful, otherwise false.
     * @throws Exception if the method e.g., cannot write to a file.
     */
    @Override
    public boolean writeToFileFromList(ObservableList<String> data, String fileName) throws Exception {
        try (FileWriter fileWriter = new FileWriter(fileName)) {
            JsonArray jsonArray = new JsonArray();

            for (String item : data) {
                JsonElement element = new JsonPrimitive(item);
                jsonArray.add(element);
            }
            fileWriter.write(jsonArray.toString());
            return true; // Writing successful
        } catch (IOException e) {
            e.printStackTrace();
            return false; 
            }
    
        }
    
    /**
     * Read memory from a JSON file.
     * Reads JSON of the forecat APIs
     * Checks for errors in data.
     * @param fileName name of the memory file
     * @return ObservableList<String> List of memory as string
     */
    @Override
    public ObservableList<String> readMemory(String fileName) {
        ObservableList<String> data = FXCollections.observableArrayList();
        File file = new File(fileName);

        // Check if the file exists, create it if it doesn't
        if (!file.exists()) {
            try {
                if (file.createNewFile()) {
                    System.out.println(fileName + " file created.");
                }
            } catch (IOException e) {
                System.out.println("Error creating " + fileName + " file.");
                e.printStackTrace();
            }
            return data; // Return empty list as the file was just created
        }

        // Read from the file if it exists
        try (FileReader fileReader = new FileReader(file)) {
            JsonElement jsonElement = JsonParser.parseReader(fileReader);

            // Check if the JSON element is an array, for 'corrupted' data
            if (jsonElement.isJsonArray()) {
                JsonArray jsonArray = jsonElement.getAsJsonArray();

                for (JsonElement element : jsonArray) {
                    String item = element.getAsString();
                    if (isValidData(item)) {
                        data.add(item);
                    } else {
                        System.out.println("Invalid data found in " + fileName + ": " + item);
                    }
                }
            } else {
                System.out.println("Invalid JSON format in " + fileName);
            }
        } catch (IOException e) {
            System.out.println("Error reading " + fileName + " file.");
            e.printStackTrace();
        }

        return data;
    }

    /**
     * Validates the data read from the file.
     * 
     * @param item The data item to validate.
     * @return true if the data is valid, false otherwise.
     */
    private boolean isValidData(String item) {
        // Implement your validation logic here
        // For example, checking if the string matches a certain pattern
        return item.matches("^[A-Za-zäöåÄÖÅ ]+$");
    }

    
    private double getJsonDouble(JsonObject jsonObject, String key, double defaultValue) {
        if (jsonObject != null && jsonObject.has(key)) {
            return jsonObject.get(key).getAsDouble();
        } else {
            return defaultValue;
        }
    }

    private int getJsonInt(JsonObject jsonObject, String key, int defaultValue) {
        if (jsonObject != null && jsonObject.has(key)) {
            return jsonObject.get(key).getAsInt();
        } else {
            return defaultValue;
        }
    }
    
}
