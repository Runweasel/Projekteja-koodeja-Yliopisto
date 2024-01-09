package fi.tuni.prog3.wordgame;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class WordGame {
    
    // Muuttujat...

    private ArrayList<String> saved_words;
    private boolean isActive;
    private WordGameState state;
    private String chosenWord;

    // Rakennin...
    public WordGame(String wordFilename) {

        saved_words = new ArrayList<>();
        isActive = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(wordFilename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                saved_words.add(line.trim());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    // Sisäinen staattinen luokka...
    public static class WordGameState {

        private String word;
        private int mistakes;
        private int mistakeLimit;
        private int missingChars;

        // Kätketty rakentaja
        private WordGameState(String word, int mistakes, int mistakeLimit, int missingChars) {
            this.word = word;
            this.mistakes = mistakes;
            this.mistakeLimit = mistakeLimit;
            this.missingChars = missingChars;
        }

        // Julkiset funktiot
        public String getWord() {
            return word;
        }

        public int getMistakes() {
            return mistakes;
        }

        public int getMistakeLimit() {
            return mistakeLimit;
        }

        public int getMissingChars() {
            return missingChars;
        }
    }

    // Jäsenfunktiot...
    public void initGame(int wordIndex, int mistakeLimit) {

        int N = saved_words.size();
        String chosenWord = saved_words.get(wordIndex % N);

        String displayWord = "_".repeat(chosenWord.length());
        state = new WordGameState(displayWord, 0, mistakeLimit, chosenWord.length());

        this.chosenWord = saved_words.get(wordIndex % N);

        isActive = true;
    }

    public boolean isGameActive() {
        return isActive;
    }

    public WordGameState getGameState() throws GameStateException {

        if (isActive == false) {
            throw new GameStateException("There is currently no active word game!");
        } 
        else return state;
    }

    public WordGameState guess(char c) throws GameStateException {

        if (!isActive) {
            throw new GameStateException("There is currently no active word game!");
        }
    
        char lowerC = Character.toLowerCase(c);
        String lowerChosenWord = chosenWord.toLowerCase();
        StringBuilder newDisplayWord = new StringBuilder(state.getWord());
        boolean found = false;
        for (int i = 0; i < lowerChosenWord.length(); i++) {
            if (lowerChosenWord.charAt(i) == lowerC && newDisplayWord.charAt(i) == '_') {
                newDisplayWord.setCharAt(i, chosenWord.charAt(i));
                state.missingChars--;
                found = true;
            }
        }

        if (!found) {
            state.mistakes++;
        }
         
        state.word = newDisplayWord.toString();

        if (state.missingChars == 0 || state.mistakes > state.mistakeLimit) {
            state.word = chosenWord;
            isActive = false;
        }

        return state;
    }
    
    public WordGameState guess(String word) throws GameStateException {

        if (!isActive) {
            throw new GameStateException("There is currently no active word game!");
        }
    
        String lowerWord = word.toLowerCase();
        String lowerChosenWord = chosenWord.toLowerCase();
    
        if (lowerWord.equals(lowerChosenWord)) {
            state.word = word;
            state.missingChars = 0;
        } else {
            state.mistakes++;
        }
    
        if (state.missingChars == 0 || state.mistakes > state.mistakeLimit) {
            state.word = chosenWord;  // Tämä rivi paljastaa oikean sanan, kun käyttäjän arvaus on väärä.
            isActive = false;
        }
    
        return state;
    }
}