/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package fi.tuni.prog3.weatherapp;

/**
 * This interface is designed to be used as a callback for search operations, particularly for city searches.
 * It contains a single method, onSearchCompleted, which is called when a search operation is completed.
 * Implementing this interface allows for defining specific actions to be taken once a search is concluded,
 * such as updating the user interface with the newly found city's information.
 * 
 * @author Lassi, Rasmus
 */
public interface SearchCallback {
    void onSearchCompleted(String newCityName);
}

