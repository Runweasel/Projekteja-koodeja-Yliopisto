package fi.tuni.prog3.weatherapp;

import java.io.IOException;
import java.io.InputStream;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.geometry.Pos;
import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;
import java.util.Map;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.scene.control.Button;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.image.Image;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;

/**
 * @author Lassi Lappalainen
 * 
 * The MainPageController class serves as the central controller for the primary interface of a weather application. 
 * This class is responsible for initializing and managing the main user interface components, including the tab pane for displaying weather data, 
 * search button, and display areas for weather forecasts.
 *
 * Upon initialization, the controller sets up various listeners, particularly for tab selection changes, to dynamically update weather information 
 * and forecasts based on user interaction. It also handles the initialization of observable lists for search history, favorites, and open tabs, 
 * reading existing data from files using the ReadAndWrite class.
 *
 * The controller allows users to create new tabs for different cities, each with a custom close button. It manages the user's interactions with these 
 * tabs, such as selecting different cities and closing tabs, updating the displayed weather information accordingly.
 *
 * Additionally, the MainPageController is responsible for the persistence of user preferences and data. It saves user favorites, search history, and 
 * tab states upon application closure, ensuring a seamless user experience across sessions.
 *
 * The class also includes methods for displaying detailed weather forecasts in both hourly and daily formats, presented in an HBox layout. These forecasts 
 * include temperature ranges, humidity, wind speed, and descriptions, each visually represented in a styled card format.
 *
 * Overall, the MainPageController plays a crucial role in providing a dynamic and responsive user interface for the weather application, enriching the 
 * user experience with its interactive and intuitive design.
 */

public class MainPageController implements Initializable, SearchCallback {

    private ObservableList<String> searchHistory = FXCollections.observableArrayList();
    private ObservableList<String> favorites = FXCollections.observableArrayList();
    private ObservableList<String> openTabs = FXCollections.observableArrayList();
    private ObservableList<String> lastOpenedTab = FXCollections.observableArrayList();
    private boolean isInitializing = true;

    @FXML
    private TabPane tabPane;
    @FXML
    private Label AppLabel;
    @FXML
    private HBox weatherHBox;
    @FXML
    private HBox weatherHBoxHourly;
    @FXML
    private Button searchButton;
    @FXML
    private Label helpLabel;

    /**
    * Initializes the MainPageController. This method sets up the application's main UI elements and listeners.
    * It loads user preferences from files, including favorites, search history, and previously opened tabs.
    * The method also configures the behavior of the tab pane to update weather information and forecast 
    * display based on the selected tab. Additionally, it sets up a help label to guide users when no tabs are open.
    * Finally, it includes logic to save user preferences upon closing the application.
    *
    * @param url The location used to resolve relative paths for the root object, or null if the location is not known.
    * @param rb The resources used to localize the root object, or null if the root object was not localized.
    */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        AppLabel.setText("Weather App");

        // Listener for tab selection changes
        tabPane.getSelectionModel().selectedItemProperty().addListener((observable, oldTab, newTab) -> {
            if (newTab != null && !isInitializing) {
                WeatherTabContent content = (WeatherTabContent) newTab.getContent();
                updateWeatherInfo(content.getCityName(), new FromAPI(), content.weatherInfoTextFlow, content.iconImageView);
                displayWeatherForecast(content.getCityName());
                lastOpenedTab.clear();
                lastOpenedTab.add(content.getCityName());
            }
        });

        ReadAndWrite readAndWrite = new ReadAndWrite();

        // Initialize lists
        favorites = FXCollections.observableArrayList();
        searchHistory = FXCollections.observableArrayList();
        openTabs = FXCollections.observableArrayList();

        // Try reading each file separately
        try {
            favorites.addAll(readAndWrite.readMemory("favorites"));
        } catch (Exception e) {
            System.out.println("Error reading 'favorites' file.");
            e.printStackTrace();
        }

        try {
            searchHistory.addAll(readAndWrite.readMemory("searchHistory"));
        } catch (Exception e) {
            System.out.println("Error reading 'searchHistory' file.");
            e.printStackTrace();
        }

        try {
            openTabs.addAll(readAndWrite.readMemory("openTabs"));
        } catch (Exception e) {
            System.out.println("Error reading 'openTabs' file.");
            e.printStackTrace();
        }
        
        // Read the last opened tab
        try {
            lastOpenedTab.addAll(readAndWrite.readMemory("lastOpenedTab"));
        } catch (Exception e) {
            System.out.println("Error reading 'lastOpenedTab' file.");
            e.printStackTrace();
        }
        
        // Open tabs based on the openTabs list
        openTabs.forEach(this::createTabForCity);
        isInitializing = false;

        // Select the last opened tab if it exists
        if (!lastOpenedTab.isEmpty()) {
            String lastOpenedCity = lastOpenedTab.get(0);
            tabPane.getTabs().stream()
                .filter(tab -> ((WeatherTabContent) tab.getContent()).getCityName().equals(lastOpenedCity))
                .findFirst()
                .ifPresent(tab -> {
                    tabPane.getSelectionModel().select(tab);
                    displayWeatherForecast(lastOpenedCity);
                });
        } else if (!tabPane.getTabs().isEmpty()) {
            tabPane.getSelectionModel().selectFirst();
            displayWeatherForecast(((WeatherTabContent) tabPane.getTabs().get(0).getContent()).getCityName());
        }
        
        helpLabel.setText("No tabs open. Please use the search button to find countries.");
        
        if (tabPane.getTabs().isEmpty()) {
            helpLabel.setVisible(true);
            helpLabel.setManaged(true);
        } else {
            helpLabel.setVisible(false);
            helpLabel.setManaged(false);
        }
        
        tabPane.getTabs().addListener((ListChangeListener<Tab>) c -> {
            if (tabPane.getTabs().isEmpty()) {
                helpLabel.setVisible(true);
                helpLabel.setManaged(true); // Make sure the label takes up space when visible
            } else {
                helpLabel.setVisible(false);
                helpLabel.setManaged(false); // Don't take up space when not visible
            }
        });

        // Use Platform.runLater for setting the close request
        Platform.runLater(() -> {
            Stage mainStage = (Stage) tabPane.getScene().getWindow();
            mainStage.setOnCloseRequest(event -> {
                try {
                    readAndWrite.writeToFileFromList(favorites, "favorites");
                    readAndWrite.writeToFileFromList(searchHistory, "searchHistory");
                    readAndWrite.writeToFileFromList(openTabs, "openTabs");
                    readAndWrite.writeToFileFromList(lastOpenedTab, "lastOpenedTab");
                } catch (Exception e) {
                    System.out.println("Error occurred while writing to files.");
                    e.printStackTrace();
                }
            });
        });
        
    }
    
    /**
    * Handles the completion of a search action by creating a new tab with weather information for the searched city.
    * If a tab with the same city name already exists, it is closed to avoid duplicates. A new tab is then created,
    * displaying weather information for the newly searched city. This tab is added to the tab pane and selected.
    * The city name is also added to the list of open tabs if it's not already present.
    *
    * @param newCityName The name of the city for which the search was completed.
    */
    @Override
    public void onSearchCompleted(String newCityName) {
        Platform.runLater(() -> {
            // Check for existing tab with the same name and close it
            tabPane.getTabs().removeIf(tab -> {
                HBox hbox = (HBox) tab.getGraphic();
                Label label = (Label) hbox.getChildren().get(0);
                return label.getText().equals(newCityName);
            });

            // Create and add the new tab
            Tab newTab = new Tab();
            WeatherTabContent tabContent = createTabContent(newCityName);
            newTab.setContent(tabContent);
            setupTabWithCloseButton(newTab, newCityName);
            tabPane.getTabs().add(newTab);
            tabPane.getSelectionModel().select(newTab);
            
            if (!openTabs.contains(newCityName)) {
                openTabs.add(newCityName);
            }
        });
    }
    
    class WeatherCard extends VBox {
        /**
        * Constructs a WeatherCard, a custom component extending VBox, for displaying weather information.
        * The card includes various weather details such as temperature, humidity, wind speed, and description,
        * tailored based on the forecast type (daily or hourly). Each weather parameter is displayed with its
        * own style settings, and an icon representing the weather condition is also shown if available.
        *
        * @param forecast The WeatherInfo object containing the weather details to be displayed.
        * @param forecastType A String indicating the type of forecast ('daily' or 'hourly') which determines
        *                     the display format of the weather data.
        */
        public WeatherCard(WeatherInfo forecast, String forecastType) {
            super(10);
            setStyle("-fx-padding: 10; -fx-border-color: #cccccc; -fx-border-radius: 10; -fx-background-radius: 10; -fx-background-color: #ffffff; -fx-effect: dropshadow(three-pass-box, rgba(0,0,0,0.1), 10, 0, 0, 10);");

            Label dateLabel = new Label(forecast.getDate());
            dateLabel.setStyle("-fx-font-weight: bold; -fx-font-size: 18px;");

            TextFlow temperatureFlow = new TextFlow();
            temperatureFlow.setStyle("-fx-font-size: 16px;");

            if ("daily".equals(forecastType)) {
                Text tempRangeText = new Text("Temp Range: ");
                Text tempMinText = new Text(String.format("%.1f°C", forecast.getTempMin()));
                Text separatorText = new Text(" ... ");
                Text tempMaxText = new Text(String.format("%.1f°C", forecast.getTempMax()));

                tempMinText.setStyle(forecast.getTempMin() <= 0 ? "-fx-fill: blue;" : "-fx-fill: red;");
                tempMaxText.setStyle(forecast.getTempMax() <= 0 ? "-fx-fill: blue;" : "-fx-fill: red;");

                temperatureFlow.getChildren().addAll(tempRangeText, tempMinText, separatorText, tempMaxText);
            } else {
                Text tempText = new Text("Temp: ");
                Text tempValueText = new Text(String.format("%.1f°C", forecast.getTemperature()));
                tempValueText.setStyle(forecast.getTemperature() <= 0 ? "-fx-fill: blue;" : "-fx-fill: red;");
                temperatureFlow.getChildren().addAll(tempText, tempValueText);
            }

            Label humidityLabel = new Label("Humidity: " + forecast.getHumidity() + "%");
            humidityLabel.setStyle("-fx-font-size: 14px;");

            Label windLabel = new Label("Wind: " + forecast.getWindspeed() + " m/s");
            windLabel.setStyle("-fx-font-size: 14px;");

            String rainfallType = forecastType.equals("daily") ? "1d" : "1h";
            Label rainfallLabel = new Label(String.format("Rainfall (%s): %.1f mm", rainfallType, forecast.getRainAmount()));
            rainfallLabel.setStyle("-fx-font-size: 14px;");

            Label descriptionLabel = new Label("Description: " + forecast.getDescription());
            descriptionLabel.setStyle("-fx-font-size: 14px;");

            String iconFilename = getIconFilename(forecast.getDescription(), forecast.getIcon());
            String iconPath = "/weather_icons/" + iconFilename;
            InputStream is = getClass().getResourceAsStream(iconPath);
            if (is != null) {
                ImageView weatherIcon = new ImageView(new Image(is));
                weatherIcon.setFitWidth(55);
                weatherIcon.setPreserveRatio(true);
                getChildren().add(weatherIcon);
            }

            getChildren().addAll(dateLabel, temperatureFlow, humidityLabel, windLabel, rainfallLabel, descriptionLabel);
        }
    }
    
    class WeatherTabContent extends AnchorPane {
        TextFlow weatherInfoTextFlow;
        ImageView iconImageView;
        String cityName;

        /**
        * Constructs a WeatherTabContent object, an extension of AnchorPane, to display weather information for a specific city.
        * This class holds the components necessary to present detailed weather information, including a TextFlow for textual data,
        * an ImageView for weather icons, and the name of the city for which the weather data is displayed.
        *
        * @param layout The AnchorPane layout that contains the initial components for this tab content.
        * @param weatherInfoTextFlow The TextFlow component used to display textual weather information.
        * @param iconImageView The ImageView component used to display the weather icon.
        * @param cityName The name of the city for which the weather information is being displayed.
        * @throws IllegalArgumentException if the provided city name is null or empty.
        */
        public WeatherTabContent(AnchorPane layout, TextFlow weatherInfoTextFlow, ImageView iconImageView, String cityName) {
            super.getChildren().addAll(layout.getChildren());
            this.weatherInfoTextFlow = weatherInfoTextFlow;
            this.iconImageView = iconImageView;
            if (cityName != null && !cityName.isEmpty()) {
                this.cityName = cityName;
            } else {
                throw new IllegalArgumentException("City name cannot be null or empty");
            }
        }

        /**
        * Retrieves the name of the city associated with this WeatherTabContent.
        * 
        * @return A String representing the name of the city.
        */
        public String getCityName() {
            return cityName;
        }
    }
    
    private void createTabForCity(String cityName) {
        if (!openTabs.contains(cityName)) {
            openTabs.add(cityName);
        }
        Tab newTab = new Tab();
        WeatherTabContent tabContent = createTabContent(cityName);
        newTab.setContent(tabContent);
        setupTabWithCloseButton(newTab, cityName);
        tabPane.getTabs().add(newTab);

        FromAPI fromAPI = new FromAPI();
        Map.Entry<Double, Double> longAndLat = fromAPI.lookUpLocation(cityName);

        if (longAndLat == null) {
            System.out.println("Unable to retrieve location data for: " + cityName);
            return; // Exit the method to avoid NullPointerException
        }

        displayWeatherForecast(cityName);

        if (!isInitializing) {
            lastOpenedTab.clear();
            lastOpenedTab.add(cityName);
        }
    }

    private void setupTabWithCloseButton(Tab tab, String cityName) {
        // Create a button with an 'X' label
        Button closeButton = new Button("X");
        closeButton.setOnAction(event -> {
            tabPane.getTabs().remove(tab);
            openTabs.remove(cityName);
            if (tabPane.getTabs().isEmpty()) {
                helpLabel.setVisible(true);
                weatherHBox.getChildren().clear();
                weatherHBoxHourly.getChildren().clear();
            }
            if (tabPane.getSelectionModel().getSelectedItem() == null && !tabPane.getTabs().isEmpty()) {
                WeatherTabContent firstTabContent = (WeatherTabContent) tabPane.getTabs().get(0).getContent();
                updateWeatherInfo(firstTabContent.getCityName(), new FromAPI(), firstTabContent.weatherInfoTextFlow, firstTabContent.iconImageView);
            } else if (tabPane.getTabs().isEmpty()) {
                weatherHBox.getChildren().clear();
                weatherHBoxHourly.getChildren().clear();
            }   
            if (lastOpenedTab.contains(cityName)) {
                lastOpenedTab.clear();
            }
        });

        closeButton.setStyle("-fx-font-size: 6pt; -fx-padding: 1px 2px; -fx-background-radius: 4px; -fx-border-radius: 4px;");
        Label titleLabel = new Label(cityName);
        HBox tabHBox = new HBox(titleLabel, closeButton);
        tabHBox.setSpacing(5);
        tabHBox.setAlignment(Pos.CENTER_LEFT);
        tab.setGraphic(tabHBox);
    }

    private void displayWeatherForecast(String location) {
        // Clear the previous content
        weatherHBoxHourly.getChildren().clear();
        weatherHBox.getChildren().clear();

        FromAPI fromAPI = new FromAPI();
        Map.Entry<Double, Double> longAndLat = fromAPI.lookUpLocation(location);
        
        // Check if longAndLat is null
        if (longAndLat == null) {
            // Handle the null case, possibly update the UI to show an error message
            System.out.println("Unable to retrieve location data for: " + location);
            return; // Exit the method to avoid NullPointerException
        }

        double longitude = longAndLat.getKey();
        double latitude = longAndLat.getValue();
        

        // Display hourly forecast
        List<WeatherInfo> forecastListHourly = fromAPI.getForecast1h(latitude, longitude);
        displayForecast(forecastListHourly, weatherHBoxHourly, "hourly");

        // Display daily forecast
        List<WeatherInfo> forecastListDaily = fromAPI.getForecastdays(latitude, longitude, 8);
        displayForecast(forecastListDaily, weatherHBox, "daily");
    }

    private void displayForecast(List<WeatherInfo> forecastList, HBox weatherHBox, String forecastType) {
        if (forecastList != null && !forecastList.isEmpty()) {
            for (WeatherInfo forecast : forecastList) {
                WeatherCard card = new WeatherCard(forecast, forecastType);
                weatherHBox.getChildren().add(card);
            }
        } else {
            System.out.println("Failed to retrieve forecast information.");
        }
    }
    
    private static WeatherInfo formatWeatherInfo(WeatherInfo weatherInfo) {
        return weatherInfo;
    }

    private WeatherTabContent createTabContent(String cityName) {
        AnchorPane centerSection = new AnchorPane();
        centerSection.setId("center-section");

        StackPane labelContainer = new StackPane();
        labelContainer.setId("label-container");
        AnchorPane.setTopAnchor(labelContainer, 10.0);
        AnchorPane.setLeftAnchor(labelContainer, 0.0);
        AnchorPane.setRightAnchor(labelContainer, 0.0);

        Text weatherLabelPart = new Text("Current weather in ");
        weatherLabelPart.setFont(Font.font("Cambria Math", FontWeight.NORMAL, 20));

        Text cityText = new Text(cityName);
        cityText.setFont(Font.font("System", FontWeight.BOLD, 20));

        TextFlow currentWeatherTextFlow = new TextFlow(weatherLabelPart, cityText);
        labelContainer.getChildren().add(currentWeatherTextFlow);

        ImageView iconImageView = new ImageView();
        iconImageView.setFitWidth(100);
        iconImageView.setPreserveRatio(true);

        TextFlow weatherInfoTextFlow = new TextFlow();
        weatherInfoTextFlow.setId("weather-info-textflow");

        HBox weatherDataBox = new HBox(8);
        weatherDataBox.setAlignment(Pos.CENTER);
        weatherDataBox.getChildren().addAll(iconImageView, weatherInfoTextFlow);

        AnchorPane.setTopAnchor(weatherDataBox, 60.0);
        AnchorPane.setLeftAnchor(weatherDataBox, 0.0);
        AnchorPane.setRightAnchor(weatherDataBox, 0.0);

        centerSection.getChildren().addAll(labelContainer, weatherDataBox);

        WeatherTabContent tabContent = new WeatherTabContent(centerSection, weatherInfoTextFlow, iconImageView, cityName);
        updateWeatherInfo(cityName, new FromAPI(), weatherInfoTextFlow, iconImageView);

        return tabContent;
    }

    private void updateWeatherInfo(String location, FromAPI fromAPI, TextFlow weatherInfoTextFlow, ImageView iconImageView) {
        try {
            Map.Entry<Double, Double> longAndLat = fromAPI.lookUpLocation(location);
            if (longAndLat != null) {
                WeatherInfo weatherInfo = fromAPI.getCurrentWeather(longAndLat.getValue(), longAndLat.getKey());
                if (weatherInfo != null) {

                    WeatherInfo formattedWeatherInfo = formatWeatherInfo(weatherInfo);

                    Text temperatureLabel = new Text("Temperature: ");
                    temperatureLabel.setFont(new Font("System", 20));

                    Text temperatureValue = new Text(String.format("%.1f°C\n", formattedWeatherInfo.getTemperature()));
                    temperatureValue.setFont(new Font("System", 20));
                    temperatureValue.setStyle(formattedWeatherInfo.getTemperature() <= 0 ? "-fx-fill: blue;" : "-fx-fill: red;");

                    Text feelsLikeLabel = new Text("Feels like: ");
                    feelsLikeLabel.setFont(new Font("System", 14));

                    Text feelsLikeValue = new Text(String.format("%.1f°C\n", formattedWeatherInfo.getFeelsLike()));
                    feelsLikeValue.setFont(new Font("System", 14));
                    feelsLikeValue.setStyle(formattedWeatherInfo.getFeelsLike() <= 0 ? "-fx-fill: blue;" : "-fx-fill: red;");

                    // Create Text nodes for the other weather information
                    Text otherInfoText = new Text(String.format("Humidity: %s\nWind speed: %s \nRainfall (1h): %s \nDescription: %s",
                            formattedWeatherInfo.getHumidity() + "%",
                            formattedWeatherInfo.getWindspeed() + " m/s",
                            formattedWeatherInfo.getRainAmount() + " mm",
                            formattedWeatherInfo.getDescription()));
                    otherInfoText.setFont(new Font("System", 14));

                    // Clear and add new content to TextFlow
                    weatherInfoTextFlow.getChildren().clear();
                    weatherInfoTextFlow.getChildren().addAll(temperatureLabel, temperatureValue, feelsLikeLabel, feelsLikeValue, otherInfoText);


                    // Handling the icon image
                    String iconFilename = getIconFilename(weatherInfo.getDescription(), weatherInfo.getIcon());
                    String iconPath = "/weather_icons/" + iconFilename;
                    InputStream is = getClass().getResourceAsStream(iconPath);

                    if (is != null) {
                        Image weatherImage = new Image(is);
                        iconImageView.setImage(weatherImage);
                    } else {
                        System.out.println("Image not found: " + iconPath);
                    }      

                } else {
                    Text errorText = new Text("Search for weather data failed.");
                    weatherInfoTextFlow.getChildren().clear();
                    weatherInfoTextFlow.getChildren().add(errorText);
                }
            } else {
                Text errorText = new Text("The location was not found or the coordinates are incorrect.");
                weatherInfoTextFlow.getChildren().clear();
                weatherInfoTextFlow.getChildren().add(errorText);
            }
        } catch (Exception e) {
            e.printStackTrace();
            Text errorText = new Text("Error updating weather info.");
            weatherInfoTextFlow.getChildren().clear();
            weatherInfoTextFlow.getChildren().add(errorText);
        }
    }
    
    private String getIconFilename(String description, String iconCode) {
    description = description.toLowerCase();

    if (iconCode.equals("01d")) return "clear_sky_day.png";
    if (iconCode.equals("01n")) return "clear_sky_night.png";
    
    switch (description) {
        case "few clouds":
        case "scattered clouds":
            return "broken_clouds.png";
        case "shower rain":
            return "shower_rain.png";
        case "rain":
            return "rain.png";
        case "thunderstorm":
            return "thunderstorm.png";
        case "snow":
            return "snow.png";
        case "mist":
        case "fog":
            return "mist.png";
        case "thunderstorm with rain":
        case "light thunderstorm":
        case "thunderstorm with light rain":
            return "thunderstorm_with_rain.png";
        case "thunderstorm with light drizzle":
        case "thunderstorm with drizzle":
        case "thunderstorm with heavy drizzle":
            return "thunderstorm_with_drizzle.png";
        case "thunderstorm with heavy rain":
        case "heavy thunderstorm":
        case "ragged thunderstorm":
            return "thunderstorm_with_heavy_rain.png";
        case "light intensity drizzle":
        case "drizzle":
        case "light intensity drizzle rain":
        case "moderate rain":
        case "light intensity shower rain":
            return "light_intensity_drizzle.png";
        case "heavy intensity drizzle":
        case "drizzle rain":
        case "heavy intensity drizzle rain":
        case "heavy intensity rain":
        case "ragged shower rain":
            return "heavy_intensity_drizzle.png";
        case "light rain":
            return "light_rain.png";
        case "shower rain and drizzle":
        case "heavy shower rain and drizzle":
        case "shower drizzle":
        case "extreme rain":
        case "very heavy rain":
        case "heavy intensity shower rain":
            return "shower_rain_and_drizzle.png";
        case "freezing rain":
        case "light rain and snow":
            return "freezing_rain.png";
        case "light snow":
            return "light_snow.png";
        case "heavy snow":
            return "heavy_snow.png";
        case "sleet":
        case "light shower sleet":
        case "shower sleet":
        case "rain and snow":
            return "sleet.png";
        case "light shower snow":
        case "shower snow":
        case "heavy shower snow":
            return "light_shower_snow.png";
        case "smoke":
        case "dust":
        case "volcanic ash":
            return "smoke.png";
        case "haze":
            return "haze.png";
        case "sand/dust whirls":
        case "sand":
            return "sand_dust_whirls.png";
        case "squalls":
            return "squalls.png";
        case "tornado":
            return "tornado.png";
        case "overcast clouds":
        case "broken clouds":
            return "overcast_clouds.png";
        default:
            return "default.png";
        }
    }

    @FXML
    private void openSearchPage() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/SearchPage.fxml"));
            Parent searchRoot = loader.load();
            Scene searchScene = new Scene(searchRoot);

            SearchPageController searchPageController = loader.getController();
            searchPageController.setMainScene(searchButton.getScene());
            searchPageController.setHistoryAndFavoriteList(searchHistory, favorites);
            searchPageController.setSearchCallback(this);

            Stage currentStage = (Stage) searchButton.getScene().getWindow();
            currentStage.setScene(searchScene);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
}