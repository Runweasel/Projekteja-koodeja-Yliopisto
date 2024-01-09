package fi.tuni.prog3.streams;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.function.Consumer;
import java.util.stream.Stream;

public class MovieAnalytics {

    // Sisäinen säiliö elokuville
    private List<Movie> movies;

    // Rakentaja
    public MovieAnalytics() {
        this.movies = new ArrayList<>();
    }

    // Staattinen funktio showInfo
    public static Consumer<Movie> showInfo() {
        return movie -> System.out.println(movie.getTitle() + " (By " + movie.getDirector() + ", " + movie.getReleaseYear() + ")");
    }

    // Jäsenfunktio populateWithData
    public void populateWithData(String fileName) {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(";");
                Movie movie = new Movie(parts[0], Integer.parseInt(parts[1]), Integer.parseInt(parts[2]),
                        parts[3], Double.parseDouble(parts[4]), parts[5]);
                movies.add(movie);
            }
        } catch (IOException e) {
            System.out.println("Error reading the file: " + e.getMessage());
        }
    }

    // Jäsenfunktiot elokuvien suodattamiseen
    public Stream<Movie> moviesAfter(int year) {
    return movies.stream()
                 .filter(movie -> movie.getReleaseYear() >= year)
                 .sorted(Comparator.comparing(Movie::getReleaseYear)
                                    .thenComparing(Movie::getTitle));
}

public Stream<Movie> moviesBefore(int year) {
    return movies.stream()
                 .filter(movie -> movie.getReleaseYear() <= year)
                 .sorted(Comparator.comparing(Movie::getReleaseYear)
                                    .thenComparing(Movie::getTitle));
}

public Stream<Movie> moviesBetween(int yearA, int yearB) {
    return movies.stream()
                 .filter(movie -> movie.getReleaseYear() >= yearA && movie.getReleaseYear() <= yearB)
                 .sorted(Comparator.comparing(Movie::getReleaseYear)
                                    .thenComparing(Movie::getTitle));
}

public Stream<Movie> moviesByDirector(String director) {
    return movies.stream()
                 .filter(movie -> movie.getDirector().equals(director))
                 .sorted(Comparator.comparing(Movie::getReleaseYear)
                                    .thenComparing(Movie::getTitle));
}
}