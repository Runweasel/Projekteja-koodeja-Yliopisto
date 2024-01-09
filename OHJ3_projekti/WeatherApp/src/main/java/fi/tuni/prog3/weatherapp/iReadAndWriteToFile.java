/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

import java.io.InputStream;
import java.util.List;
import javafx.collections.ObservableList;

/**
 * Interface with methods to read from a file and write to a file.
 */
public interface iReadAndWriteToFile {
    
    /**
     * Reads JSON from the current weather API.
     * @param responseCode API response
     * @param inputStream JSON inputstream
     * @return WeatherInfo object
     * @throws Exception if the method cannot find the file. 
     */
    public WeatherInfo readFromAPI(int responseCode, InputStream inputStream) throws Exception; 
    
    /**
     * Reads JSON of the forecat APIs
     * @param responseCode API response
     * @param inputStream JSON inputstream
     * @param flag flag for mode switching
     * @return List<WeatherInfo> List of info objects.
     * @throws Exception if the method cannot find the file.
     */
    public List<WeatherInfo> readForecastFromAPI(int responseCode, InputStream inputStream, boolean flag) throws Exception;
    
    
    /**
     * Read memory from a JSON file.
     * Reads JSON of the forecat APIs
     * @param fileName name of the memory file
     * @return ObservableList<String> List of memory as string
     */
    public ObservableList<String> readMemory(String fileName);
    
    /**
     * Write the student progress as JSON into the given file.
     * @param data List for memory
     * @param fileName name of the file to write to.
     * @return true if the write was successful, otherwise false.
     * @throws Exception if the method e.g., cannot write to a file.
     */
    public boolean writeToFileFromList(ObservableList<String> data, String fileName) throws Exception;
    
    /**
     * Parses and saves the weather data from inputsream
     * @param inputStream JSON inputstream
     * @return WeatherInfo object
     * @throws Exception if the method cannot parse the data. 
     */
    public WeatherInfo readAndParseCurrent(InputStream inputStream) throws Exception;
    
    /**
     * Parses and saves the weather data from inputsream
     * @param inputStream JSON inputstream
     * @return List<WeatherInfo> list of weather objects
     * @throws Exception if the method cannot parse the data. 
     */
    public List<WeatherInfo> readAndParseHourlyForecast(InputStream inputStream) throws Exception;
    
    /**
     * Parses and saves the weather data from inputsream
     * @param inputStream JSON inputstream
     * @return List<WeatherInfo> list of weather objects
     * @throws Exception if the method cannot parse the data. 
     */
    public List<WeatherInfo> readAndParsedaysForecast(InputStream inputStream) throws Exception;
    
}
