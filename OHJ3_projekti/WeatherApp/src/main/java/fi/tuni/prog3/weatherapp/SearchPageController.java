/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

import java.util.Map;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListCell;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.util.Callback;

/**
 * @author Rasmus Tuokko
 * 
 * Search page for the GUI. Page allows user to input a city or country and
 * searches the weather for the said input. The program automatically changes to
 * the main page of the program if the user's input was valid and weather data
 * was found. 
 *    Search page shows the user's search history and allows the user to select
 * locations to favorites via pressing a star-icon on search history. Favorites 
 * list is shown next to the search history list.
 *     User can erase locations from search history or favorites as they wish.
 *     After every action the user makes, above the search text field an info
 * label is shown telling the user info about their inputs.
 * 
*/
public class SearchPageController {
    
    @FXML
    private Label infoLabel;
    @FXML
    private ListView<String> historyListView;
    @FXML
    private ListView<String> favoritesListView;
    @FXML
    private TextField searchField;
    @FXML
    private Button deleteButton;
    
    private Stage mainStage;
    private final FromAPI fromAPI = new FromAPI();
    private SearchCallback searchCallback;
    
    @FXML
    private void initialize() {
        
        // Initializing the lists
        historyListView.setItems(FXCollections.observableArrayList());
        historyListView.setOnMouseClicked(e -> handleHistoryListClick(historyListView.getSelectionModel().getSelectedItem()));
        historyListView.setCellFactory(createCellFactory());
        
        favoritesListView.setItems(FXCollections.observableArrayList());
        favoritesListView.setOnMouseClicked(e -> handleFavoriteListClick(favoritesListView.getSelectionModel().getSelectedItem()));

        // Style settings
        historyListView.setStyle("-fx-font-size: 10pt;");
        favoritesListView.setStyle("-fx-font-size: 10pt;");
        infoLabel.setStyle("-fx-font-size: 11pt;");
        
        searchField.setOnKeyPressed(this::handleKeyPress);
    }
    
    private void handleKeyPress(KeyEvent event) {
        if (event.getCode() == KeyCode.ENTER) {
            handleSubmitButtonAction();
        }
    }

    @FXML
    private void handleSubmitButtonAction() {
        String location = "";
        
        if (searchField.getText() != null) {
            location = searchField.getText().trim();
        }
        if (location.equals("")) {
            infoLabel.setText("Invalid input. Enter country or city.");
            return;
        }
        // Check the input for its validity
        if (!location.matches("^[A-Za-zäöåÄÖÅ ]+$")) {
            infoLabel.setText("Invalid input. Enter only alphabets.");
            return;
        }
        
        try {
            Map.Entry<Double, Double> longAndLat = fromAPI.lookUpLocation(location);
            String locationPretty = "";
            for (int i = 0; i < location.length(); i++) {
                    if (i==0) {
                        locationPretty = locationPretty + Character.toUpperCase(location.charAt(i));
                    }
                    else {
                        locationPretty += Character.toLowerCase(location.charAt(i));
                    }
            }
            if (longAndLat != null && areCoordinatesValid(longAndLat)) {
                WeatherInfo weatherInfo = fromAPI.getCurrentWeather(longAndLat.getValue(), longAndLat.getKey());
                if (weatherInfo != null) {
                    // Add location to history list view
                    if (!historyListView.getItems().contains(locationPretty)) {
                        historyListView.getItems().add(locationPretty);
                    }
                    searchField.setText("");

                    if (searchCallback != null) {
                        searchCallback.onSearchCompleted(locationPretty);
                        Stage currentStage = (Stage) searchField.getScene().getWindow();
                        currentStage.setScene(mainScene);
                    }
                } else {
                    infoLabel.setText("Failed to fetch weather data.");
                }
            } else {
                infoLabel.setText("Location cannot be found or coordinates are faulty.");
            }
        } catch (Exception e) {
            infoLabel.setText("Error in fetching weather data.");
        }
    }
    
    private static boolean areCoordinatesValid(Map.Entry<Double, Double> coordinates) {
        double latitude = coordinates.getValue();
        double longitude = coordinates.getKey();
        return latitude >= -90 && latitude <= 90 && longitude >= -180 && longitude <= 180;
    }
    
    private Callback<ListView<String>, ListCell<String>> createCellFactory() {
        return param -> new ListCell<>() {
            @Override
            protected void updateItem(String item, boolean empty) {
                super.updateItem(item, empty);

                if (empty || item == null) {
                    setText(null);
                    setGraphic(null);
                } else {
                    setText(item);

                    Button favoriteButton = new Button();
                    // Initializing favorite-icon
                    ImageView favoriteIcon = new ImageView(new Image("file:./favoriteIcon.png"));
                    favoriteIcon.setFitHeight(20);
                    favoriteIcon.setFitWidth(20);

                    if (favoritesListView.getItems().contains(item)) {
                        favoriteButton.setGraphic(favoriteIcon);
                    } else {
                        // Initializing non-favorite-icon
                        ImageView nonFavoriteIcon = new ImageView(new Image("file:./nonFavoriteIcon.jpg"));
                        nonFavoriteIcon.setFitHeight(20);
                        nonFavoriteIcon.setFitWidth(20);
                        favoriteButton.setGraphic(nonFavoriteIcon);
                    }
                    favoriteButton.setOnMouseClicked(event -> handleFavoriteButtonAction(item, this, favoriteButton));
                    setGraphic(favoriteButton);
                }
            }
        };
    }
    
    private void handleFavoriteButtonAction(String city, ListCell<String> cell, Button favoriteButton) {
        
        if (!favoritesListView.getItems().contains(city)) {
            favoritesListView.getItems().add(city);
            // Update the buttons graphics
            ImageView fullHeartIcon = new ImageView(new Image("file:favoriteIcon.png"));
            fullHeartIcon.setFitHeight(20);
            fullHeartIcon.setFitWidth(20);
            favoriteButton.setGraphic(fullHeartIcon);
            infoLabel.setText(city + " added to favorites");
           
        } else {
            favoritesListView.getItems().remove(city);
            // Update the buttons graphics
            ImageView nonFavoriteIcon = new ImageView(new Image("file:nonFavoriteIcon.jpg"));
            nonFavoriteIcon.setFitHeight(20);
            nonFavoriteIcon.setFitWidth(20);
            favoriteButton.setGraphic(nonFavoriteIcon);
            infoLabel.setText(city + " removed from favorites.");
        }
    }

    private Scene mainScene;
    
    /**
     * Sets the main scene to the Search pages scene.
     * @param mainScene scene to be set.
     */
    public void setMainScene(Scene mainScene) {
        this.mainScene = mainScene;
    }

    @FXML
    private void handleGoBackButtonAction() {
        if (mainScene != null) {
            Stage currentStage = (Stage) searchField.getScene().getWindow();
            currentStage.setScene(mainScene);
        }
    }
    
    @FXML
    private void handleDeleteButton() {
        String cityName;
        
        // Check if the location was selected from search history or favorites,
        // this way we can deal with them both with just one function.
        if (historyListView.getSelectionModel().getSelectedItem() != null) {
            cityName = historyListView.getSelectionModel().getSelectedItem();
            historyListView.getItems().remove(cityName);
            infoLabel.setText(cityName + " erased succesfully from search history.");
        }
        else if (favoritesListView.getSelectionModel().getSelectedItem() != null) {
            cityName = favoritesListView.getSelectionModel().getSelectedItem();
            favoritesListView.getItems().remove(cityName);
            
            if (historyListView.getItems().contains(cityName)) {
                historyListView.requestFocus();
                historyListView.getSelectionModel().select(cityName);
            }
            infoLabel.setText(cityName + " erased succesfully from favorites.");
        }
        else {
            infoLabel.setText("First select the city you wish to erase!");
        }
    }

    private void handleFavoriteListClick(String city) {
        infoLabel.setText("");
        historyListView.getSelectionModel().clearSelection();
        searchField.setText(city);
    }
    
    private void handleHistoryListClick(String city) {
        infoLabel.setText("");
        favoritesListView.getSelectionModel().clearSelection();
        searchField.setText(city);
    }

    /**
     * Sets the history - and favorites lists.
     * @param historyList historyList to be set to historyListView.
     * @param favoritesList favoritesList to be set to favoritesListView.
     */
    public void setHistoryAndFavoriteList(ObservableList<String> historyList, ObservableList<String> favoritesList) {
        historyListView.setItems(historyList);
        favoritesListView.setItems(favoritesList);
    }
  
    /**
     * Sets the callback from the main page to this.searchCallback, so we can
     * easily move back to the main page.
     * @param callback callback from the main page to be set.
     */
    public void setSearchCallback(SearchCallback callback) {
        this.searchCallback = callback;
    }

}