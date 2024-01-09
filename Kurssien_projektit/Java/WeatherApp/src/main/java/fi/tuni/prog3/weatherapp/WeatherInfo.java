/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

/**
 * @author Sakari
 * Object for saving weatherinfo
 */
public class  WeatherInfo {
    private double temperature;
    private double feelsLike;
    private double tempMin;
    private double tempMax;
    private int pressure;
    private int humidity;
    private double windspeed;
    private double rainAmount;
    private String mainWeather;
    private String description;
    private String icon;
    private String date;

    public WeatherInfo(double temperature, double feelsLike, double tempMin, double tempMax, int pressure, int humidity,double windspeed, double rainAmount, String mainWeather, String description, String icon, String date) {
        this.temperature = temperature;
        this.feelsLike = feelsLike;
        this.tempMin = tempMin;
        this.tempMax = tempMax;
        this.pressure = pressure;
        this.humidity = humidity;
        this.windspeed = windspeed;
        this.rainAmount = rainAmount;
        this.mainWeather = mainWeather;
        this.description = description;
        this.icon = icon;
        this.date = date;
    }

    public String getDate() {
        return date;
    }

    public double getTemperature() {
        return temperature;
    }

    public double getFeelsLike() {
        return feelsLike;
    }

    public double getTempMin() {
        return tempMin;
    }

    public double getTempMax() {
        return tempMax;
    }

    public int getPressure() {
        return pressure;
    }

    public int getHumidity() {
        return humidity;
    }
    
    public double getWindspeed() {
        return windspeed;
    }
    
    public double getRainAmount() {
        return rainAmount;
    }

    public String getMainWeather() {
        return mainWeather;
    }

    public String getDescription() {
        return description;
    }
    
    public String getIcon() {
        return icon;
    }

    @Override
    public String toString() {
        return "WeatherInfo{" +
                "temperature=" + temperature +
                ", feelsLike=" + feelsLike +
                ", tempMin=" + tempMin +
                ", tempMax=" + tempMax +
                ", pressure=" + pressure +
                ", humidity=" + humidity +
                ", windspeed=" + windspeed +
                ", mainWeather='" + mainWeather + '\'' +
                ", description='" + description + '\'' +
                '}';
    }
}
