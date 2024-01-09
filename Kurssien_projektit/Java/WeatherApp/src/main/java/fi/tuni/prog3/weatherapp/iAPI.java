
package fi.tuni.prog3.weatherapp;


import java.util.List;
import java.util.Map;

/**
 * Interface for extracting data from the OpenWeatherMap API.
 */
public interface iAPI {
    
    
    /**
     * Returns coordinates for a location.
     * @param loc Name of the location for which coordinates should be fetched.
     * @return Map.Entry<Double, Double>.
     */
    public Map.Entry<Double, Double> lookUpLocation(String loc);
    
    /**
     * Returns the current weather for the given coordinates.
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @return WeatherInfo object.
     */
    public WeatherInfo  getCurrentWeather(double lat, double lon);
    
    /**
     * Returns a forecast for the given coordinates for 1h intervals.
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @return List<WeatherInfo>.
     */
    public List<WeatherInfo> getForecast1h(double lat, double lon);
   
    /**
     * Returns a forecast avarages for the given coordinates for days intervals.
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param cnt How many days you want to get from the API.
     * @return List<WeatherInfo>.
     */
    public List<WeatherInfo> getForecastdays(double lat, double lon, int cnt);
    
}
