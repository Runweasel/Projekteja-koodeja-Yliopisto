#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>
#include "gameboard.hh"
#include <QGridLayout>
#include <QTimer>
#include <QTime>
#include <QLabel>

/*
* ------------------------ Ohjelman kirjoittaja: ------------------------
*
* Nimi: Lassi Lappalainen
* Opiskelijanumero: 150390123
* Käyttäjätunnus: kvlala
* E-Mail: lassi.lappalainen@tuni.fi
*
* -----------------------------------------------------------------------
* */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Määrittelee vakiot nappuloiden koolle ja pelilaudan koon.
    static const int BUTTON_SIZE = 80;
    static const int BOARD_WIDTH = COLUMS * BUTTON_SIZE;
    static const int BOARD_HEIGHT = ROWS * BUTTON_SIZE;
    static const int MIN_POSSIBLE_MOVES = 31;
    static const int TIME_SECONDS = 1000;

private slots:

    // Käsittelee QPushButtonin napsautuksen. Valitsee nappulan tai suorittaa
    // siirron, jos nappula on jo valittu. Jos siirto on virheellinen,
    // näyttää virheilmoituksen.
    void handle_button_clicked();

    // Palauttaa pelilaudan alkutilaan, tyhjentää siirtohistorian, nollaa
    // siirtojen määrän ja ajastimen. Asettaa pelin alkuasetukset.
    void on_reset_button_clicked();

    // Lopettaa ja sulkee ikkunan ja pelin.
    void on_quit_button_clicked();

    // Keskeyttää pelin ja ajastimen. Poistaa käytöstä kaikki pelilaudan
    // painikkeet ja näyttää viestin pelin keskeyttämisestä.
    void on_pause_button_clicked();

    // Aloittaa tai jatkaa peliä ja ajastinta. Alustaa pelin tarvittaessa ja
    // ottaa pelilaudan painikkeet uudelleen käyttöön.
    void on_start_button_clicked();

    // Asettaa pelaajalle tavoitearvon ja näyttää sen LCD-näytöllä.
    void on_set_target_button_clicked();

    // Peruu viimeisen siirron ja päivittää pelilaudan sekä siirtojen määrän.
    void on_undo_button_clicked();

    // Lukee kirjoitetun nimimerkin ja asettaa boolean-arvon, että nimimerkki
    // asetettu.
    void on_set_nickname_button_clicked();

private:

    // Lue, tallenna ja näytä tulostaulu tiedostosta "leaderboard.txt" ja
    // näytöllä. Lisää pelaajan tulokset tulostauluun ja kirjoita uudet
    // tulokset tiedostoon.
    void read_leaderboard();

    // Luo pelilaudan ja lisää sen ikkunaan. Luo pelilaudan soluille
    // QPushButtonit ja asettaa niiden sijainnin, koon, tyylisäännöt sekä
    // koordinaatit pelilaudalla. Lisäksi yhdistää QPushButtonit
    // handle_button_clicked -signaaliin.
    void make_board();

    // Asettaa ja käynnistää pelin ajastimen, jos peli on käynnissä ja ajastin
    // ei ole jo aktiivinen. Alustaa ajastimen ja yhdistää sen
    // update_timer -signaaliin.
    void set_up_timer();

    // Lisää kulunutta aikaa ja päivittää ajastimen näyttöä.
    void update_timer();

    // Suorittaa siirron antamalla valitun nappulan sijainnin, klikatun
    // nappulan sijainnin ja klikatun nappulan. Tallentaa siirtohistorian,
    // päivittää nappien ulkoasun, lisää siirtojen määrää ja tarkistaa, onko
    // peli päättynyt.
    void execute_move(Point selected_point, Point clicked_point,
                      QPushButton *clicked_button);

    // Palauttaa QPushButtonin, joka sijaitsee annetussa pisteessä.
    QPushButton* get_button_at(Point point);

    Ui::MainWindow *ui;

    // Ajastin ja kellonäyttö.
    QTimer* timer;
    QTime elapsed_time;
    QLabel* timer_label;

    // Valittu nappula.
    QPushButton* selected_button_ = nullptr;

    // Valitun nappulan tyyli.
    QString selected_button_style_sheet;

    // Pelilauta.
    GameBoard gameBoard;

    // Pelilaudan nappulat vektorissa.
    std::vector<QPushButton*> buttons_;

    // Siirtohistoria
    std::vector<std::tuple<Point, Point, QString>> move_history_;

    // Boolean-arvot pelin tilan seuraamiseen.
    bool has_chosen_color_ = false;
    bool game_started = false;
    bool target_set_ = false;
    bool nickname_set_ = false;

    // Siirtojen määrä ja tavoitearvo.
    int amount_of_moves = 0;
    int target_value_ = 31;

};
#endif // MAINWINDOW_HH
