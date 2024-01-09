package fi.tuni.prog3.weatherapp;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

// Group2973 - WeatherApp - Sääsovellus
//
// Makers:
// Lassi Lappalainen
// Sakari Ollikainen
// Rasmus Tuokko

/**
 * The WeatherApp class serves as the entry point for a JavaFX-based weather application project. This class extends the Application class
 * and is responsible for initializing and launching the primary user interface of the application.
 *
 * Upon starting the application, this class executes the 'start' method, which is responsible for:
 * - Loading the main user interface layout from an FXML file, which defines the structure and design of the application's GUI.
 * - Creating a Scene with the loaded FXML layout, which serves as the root of the application's graphical user interface.
 * - Setting the scene for the primary stage (main window) of the application and displaying it to the user.
 *
 * The main interface, managed by the MainPageController, provides features such as displaying weather forecasts in hourly and daily formats,
 * managing user interaction through a tabbed interface for different cities, and allowing users to search for weather data. 
 * It also maintains user data across sessions, including favorites, search history, and open tabs.
 *
 * This application is a collaborative effort by Lassi Lappalainen, Sakari Ollikainen, and Rasmus Tuokko (Group2973). 
 * The WeatherApp offers an interactive and user-friendly platform for accessing and displaying weather information with nice looking, but simple UI.
 *
 * @see MainPageController
 */

public class WeatherApp extends Application   {
    
    @Override
    public void start(Stage primaryStage) throws Exception {
        // Load the FXML file
        Parent root = FXMLLoader.load(getClass().getResource("/fxml/MainPage.fxml"));
        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.setTitle("WeatherApp");
        primaryStage.show();
    }
}
