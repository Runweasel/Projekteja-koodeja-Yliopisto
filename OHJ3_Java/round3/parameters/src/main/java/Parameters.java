import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;


public class Parameters {

    public static void main(String[] args) {
        System.out.println("Parameters:");
        
        // Tehdään käyttäjän syötteille alustus
        // Käyttäjä voi siis syöttää tietoa kunnes hän syöttää
        // tyhjän välin.

        Scanner scanner = new Scanner(System.in);
        List<String> parameters = new ArrayList<>();
        String line;

        while (true) {
            line = scanner.nextLine();
            if (line.isBlank()) {
                 break;
            }
             parameters.add(line);
        }
        
        // Tehdään listasta aakkosjärjestetty
        Collections.sort(parameters);
        
        // Maximi pituus syötteelle.
        // Tehdään se vertailemalla lambda-funktiolla ja otetaan talteen
        // pisin
        int maxPituus = 0;
        for (String parameter : parameters) {
            maxPituus = Math.max(maxPituus, parameter.length());
        }

        // Tutkitaan leveys mitä numerot vaativat eli kuinka monta
        // merkkiä numero vie. 
        int maxLeveysNumeroille = String.valueOf(parameters.size()).length();

        String reunus = "#".repeat(maxLeveysNumeroille + maxPituus + 7);
        String rivin_tiedot = "# %" + maxLeveysNumeroille + "d | %-" + maxPituus + "s #";

        System.out.println(reunus);
        for (int i = 0; i < parameters.size(); i++) {
            System.out.printf(rivin_tiedot, i + 1, parameters.get(i));
            // System.out.println (); tulostaa uudelle riville tai tekee tyhjän rivin.
            System.out.println();
            if (i < parameters.size() - 1) {
                System.out.println("#" + "-".repeat(maxLeveysNumeroille + 2) + "+" + "-".repeat(maxPituus + 2) + "#");
            }
        }
        System.out.println(reunus);
    }
}