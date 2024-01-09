
package fi.tuni.prog3.sudoku;

/**
 *
 * @author lassi
 */
public class Sudoku {
    private final char[][] ruudukko;
    
    // rivi eli i
    // sarake eli j

    public Sudoku() {
        ruudukko = new char[9][9];
        for (int rivi = 0; rivi < 9; ++rivi) {
            for (int sarake = 0; sarake < 9; ++sarake) {
                ruudukko[rivi][sarake] = ' ';
            }
        }
    }

    public void set(int rivi, int sarake, char c) {
        if (rivi < 0 || rivi >= 9 || sarake < 0 || sarake >= 9) {
            System.out.println("Trying to access illegal cell (" + rivi + ", " + sarake + ")!");
            return;
        }

        if ((c < '1' || c > '9') && c != ' ') {
            System.out.println("Trying to set illegal character " + c + " to (" + rivi+ ", " + sarake + ")!");
            return;
        }

        ruudukko[rivi][sarake] = c;
    }
    
    public boolean check() {
        
        // Tarkista rivit -- ruudukko[rivi][sarake]
        for (int rivi = 0; rivi < 9; ++rivi) {
            boolean[] nahty = new boolean[9];
            for (int sarake = 0; sarake < 9; ++sarake) {
            // ruudukko[0][1] eli toinen ruutu seuraavalla kierokselle
                char c = ruudukko[rivi][sarake];
                if (c >= '1' && c <= '9') {
                    if (nahty[c - '1']) {
                    System.out.println("Row " + rivi + " has multiple " + ruudukko[rivi][sarake] + "'s!");
                    return false;  // Luku on jo nähty tällä rivillä
                    }
                    nahty[c - '1'] = true;
                }
            }
        }
        
        // Tarkista sarakket -- ruudukko[sarake][rivi]
        for (int sarake = 0; sarake < 9; ++sarake) {
            boolean[] nahty = new boolean[9];
            for (int rivi = 0; rivi < 9; ++rivi) {
                // ruudukko[1][0] eli toinen ruutu seuraavalla kierokselle
                char c = ruudukko[rivi][sarake];
                if (c >= '1' && c <= '9') {
                    if (nahty[c - '1']) {
                        System.out.println("Column " + sarake + " has multiple " + ruudukko[rivi][sarake] + "'s!");
                        return false;
                    }
                    nahty[c - '1'] = true;
                }
            }
        }
        
        // Tarkista lohko eli 3x3. Käydään neljässä loopissa.
        for (int rivi1 = 0; rivi1 < 9; rivi1 += 3) {
            for (int sarake1 = 0; sarake1 < 9; sarake1 += 3) {
                
                boolean[] nahty = new boolean[9];
                
                for (int rivi_x1 = rivi1; rivi_x1 < rivi1 + 3; ++rivi_x1) {
                    for (int sarake_y1 = sarake1; sarake_y1 < sarake1 + 3; ++sarake_y1) {
                        char c = ruudukko[rivi_x1][sarake_y1];
                        if (c >= '1' && c <= '9') {
                            if (nahty[c - '1']) {
                                System.out.println("Block at (" + rivi1 + ", " + sarake1 + ") has multiple " + ruudukko[rivi_x1][sarake_y1] + "'s!");
                                return false;
                            }
                        nahty[c - '1'] = true;
                        }
                    }
                }
            }
        }
        // Palauta True jos kaikki kunnossa
        return true;
    }
    
    public void print() {
        // Tulosta ruudukko
        
        //Ylä-osa
        System.out.println("#####################################");
        
        for (int i = 0; i < 9; ++i) {
            System.out.print("#");
            for (int j = 0; j < 9; ++j) {
                System.out.print(" " + ruudukko[i][j]);
                if (j % 3 == 2) {
                    System.out.print(" #");
                } else {
                    System.out.print(" |");
                }
            }
            System.out.println();
            if (i % 3 == 2) {
                System.out.println("#####################################");
            } else {
                System.out.println("#---+---+---#---+---+---#---+---+---#");
            }
        }      
    }
}
