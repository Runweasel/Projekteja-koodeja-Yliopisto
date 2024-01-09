package fi.tuni.prog3.streams2;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;

public class MovieAnalytics2 {

    private List<Movie> movies;

    public MovieAnalytics2() {
        this.movies = new ArrayList<>();
    }

    public void populateWithData(String fileName) {
        try (BufferedReader reader = Files.newBufferedReader(Paths.get(fileName))) {
            movies = reader.lines()
                    .map(line -> line.split(";"))
                    .map(data -> new Movie(
                            data[0].trim(),
                            Integer.parseInt(data[1].trim()),
                            Integer.parseInt(data[2].trim()),
                            data[3].trim(),
                            Double.parseDouble(data[4].trim()),
                            data[5].trim()))
                    .collect(Collectors.toList());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void printCountByDirector(int n) {
        movies.stream()
                .collect(Collectors.groupingBy(Movie::getDirector, Collectors.counting()))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<String, Long>comparingByValue().reversed().thenComparing(Map.Entry::getKey))
                .limit(n)
                .forEach(entry -> System.out.println(entry.getKey() + ": " + entry.getValue() + " movies"));
    }

    public void printAverageDurationByGenre() {
        movies.stream()
                .collect(Collectors.groupingBy(Movie::getGenre, Collectors.averagingInt(Movie::getDuration)))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<String, Double>comparingByValue().thenComparing(Map.Entry::getKey))
                .forEach(entry -> System.out.printf("%s: %.2f%n", entry.getKey(), entry.getValue()));
    }

    public void printAverageScoreByGenre() {
        movies.stream()
                .collect(Collectors.groupingBy(Movie::getGenre, Collectors.averagingDouble(Movie::getScore)))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<String, Double>comparingByValue().reversed().thenComparing(Map.Entry::getKey))
                .forEach(entry -> System.out.printf("%s: %.2f%n", entry.getKey(), entry.getValue()));
    }
}