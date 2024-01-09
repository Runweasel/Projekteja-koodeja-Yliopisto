package fi.tuni.prog3.wordle;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import javafx.geometry.Insets;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;


public class Wordle extends Application {

    private List<String> wordList;
    private String currentWord;
    private GridPane grid;
    private Label infoBox;
    private Button newGameBtn;
    private int currentAttempt;
    private VBox root;
    

    @Override
    public void start(Stage primaryStage) {
        readWordsFromFile();
        if (wordList.isEmpty()) {
            infoBox = new Label("Word list is empty.");
            return;
        }

        currentWord = wordList.get(0);
        grid = createGrid(currentWord.length());
        infoBox = new Label();
        newGameBtn = new Button("Start new game");
        newGameBtn.setOnAction(e -> startNewGame());

        setupIds();
        
        // Kuluttaa Enter-näppäimen painalluksen newGameBtn:lle.
        newGameBtn.addEventFilter(KeyEvent.KEY_PRESSED, event -> {
            if (event.getCode() == KeyCode.ENTER) {
                event.consume();
            }
        });

        root = new VBox(grid, infoBox, newGameBtn);
        Scene scene = new Scene(root);
        scene.setOnKeyPressed(event -> {
            if (event.getCode().isLetterKey()) {
                handleLetterInput(event.getText().charAt(0));
            } else if (event.getCode() == KeyCode.BACK_SPACE) {
                handleBackspace();
            } else if (event.getCode() == KeyCode.ENTER) {
                event.consume();
                handleSubmit();
            }
        });

        primaryStage.setScene(scene);
        primaryStage.setTitle("Wordle Game");
        primaryStage.show();
        // Pyydä kohdistus ruudukkoon, jotta nappi ei olisi aluksi kohdistuksen kohteena.
        grid.requestFocus();
    }

    private void readWordsFromFile() {
        wordList = new ArrayList<>();
        File file = new File("words.txt");
        try (Scanner scanner = new Scanner(file)) {
            while (scanner.hasNextLine()) {
                String word = scanner.nextLine().trim().toUpperCase();
                wordList.add(word);
            }
        } catch (FileNotFoundException e) {
        }
    }

    private GridPane createGrid(int wordLength) {
        GridPane newGrid = new GridPane();
        for (int i = 0; i < 6; i++) { // 6 yritystä
            for (int j = 0; j < wordLength; j++) {
                Label label = new Label();
                label.setMinSize(50, 50);
                label.setStyle("-fx-border-color: black; -fx-alignment: center;");
                label.setId(i + "_" + j);
                GridPane.setConstraints(label, j, i);
                newGrid.getChildren().add(label);
            }
        }
        newGrid.setGridLinesVisible(true);
        newGrid.setFocusTraversable(true);
        return newGrid;
    }

    private void setupIds() {
        infoBox.setId("infoBox");
        newGameBtn.setId("newGameBtn");
    }

    private void startNewGame() {
        currentWord = getNextWord();
        currentAttempt = 0;
        GridPane newGrid = createGrid(currentWord.length());

        root.getChildren().remove(grid);
        root.getChildren().add(0, newGrid);
        grid = newGrid;

        infoBox.setText("");
        grid.setDisable(false);
        grid.requestFocus(); // Laitetaan focus gridille
    }
    
    private String getNextWord() {
        int currentIndex = wordList.indexOf(currentWord);
        int nextIndex = (currentIndex + 1) % wordList.size();
        return wordList.get(nextIndex);
    }

    private void handleLetterInput(char letter) {
        if (currentAttempt < 6) {
            String attempt = getCurrentAttemptString();
            if (attempt.length() < currentWord.length()) {
                Label label = (Label) grid.lookup("#" + currentAttempt + "_" + attempt.length());
                label.setText(String.valueOf(letter).toUpperCase());
            }
        }
    }

    private String getCurrentAttemptString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < currentWord.length(); i++) {
            Label label = (Label) grid.lookup("#" + currentAttempt + "_" + i);
            sb.append(label.getText());
        }
        return sb.toString();
    }

    private void handleBackspace() {
        if (currentAttempt < 6) {
            String attempt = getCurrentAttemptString();
            if (!attempt.isEmpty()) {
                int lastCharIndex = attempt.length() - 1;
                Label label = (Label) grid.lookup("#" + currentAttempt + "_" + lastCharIndex);
                label.setText("");
            }
        }
    }

    private void handleSubmit() {
        String attempt = getCurrentAttemptString();
        if (attempt.length() == currentWord.length()) {
            if (attempt.equals(currentWord)) {
                infoBox.setText("Congratulations, you won!");
                colorRow(currentAttempt, Color.GREEN);
                //disableInput();
            } else {
                if (currentAttempt < 5) {
                    colorAttempt(attempt);
                    currentAttempt++;
                } else {
                    
                    colorAttempt(attempt);
                    infoBox.setText("Game over, you lost!");
                }
            }
        } else {
            infoBox.setText("Give a complete word before pressing Enter!");
        }
    }

    private void colorRow(int row, Color color) {
        for (int i = 0; i < currentWord.length(); i++) {
            Label label = (Label) grid.lookup("#" + row + "_" + i);
            label.setBackground(new Background(new BackgroundFill(color, CornerRadii.EMPTY, Insets.EMPTY)));
        }
    }

    private void colorAttempt(String attempt) {
        for (int i = 0; i < attempt.length(); i++) {
            Color color;
            if (attempt.charAt(i) == currentWord.charAt(i)) {
                color = Color.GREEN;
            } else if (currentWord.contains(String.valueOf(attempt.charAt(i)))) {
                color = Color.ORANGE;
            } else {
                color = Color.GRAY;
            }
            Label label = (Label) grid.lookup("#" + currentAttempt + "_" + i);
            // Varmistetaan, että tausta käyttää oikeaa väriä
            label.setBackground(new Background(new BackgroundFill(color, CornerRadii.EMPTY, Insets.EMPTY)));
        }
    }
    
    public static void main(String[] args) {
        launch(args);
    }
}