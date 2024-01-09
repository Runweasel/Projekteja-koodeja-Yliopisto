#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QPushButton>
#include <QGridLayout>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QStringList>

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Alusta kulunut aika ja näytä se LCD-näytöllä
    elapsed_time = QTime(0, 0);
    ui->lcd_timer->display(elapsed_time.toString("mm:ss"));

    // Poista tauko-, nollaus- ja kumoa-painikkeiden käytettävyys aluksi
    ui->pause_button->setDisabled(true);
    ui->reset_button->setDisabled(true);
    ui->undo_button->setDisabled(true);

    // Aseta pääikkunan taustaväri valkoiseksi
    this->setStyleSheet("background-color: white");

    // Aseta ohjeteksti tapahtumalogiin
    ui->event_log_browser->setText("Press Start button to play the game or you "
    "can set a target for yourself.");

    // Aseta tavoitteen alaraja ja oletusarvo
    ui->target_spinbox->setMinimum(MIN_POSSIBLE_MOVES);
    ui->target_spinbox->setValue(MIN_POSSIBLE_MOVES);

    // Luo pelilauta
    make_board();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_board()
{
    // Aseta pelilauta keskelle ikkunaa
    int boardX = (this->width() - BOARD_WIDTH) / 2;
    int boardY = (this->height() - BOARD_HEIGHT) / 2;

    QWidget *boardWidget = new QWidget(this);
    boardWidget->setGeometry(boardX, boardY, BOARD_WIDTH, BOARD_HEIGHT);

    // Käy läpi pelilaudan solut ja luo niille QPushButtonit
    for (unsigned int i = 0; i < ROWS; ++i) {

        // Jos solu on käyttämätön, jätä se luomatta
        for (unsigned int j = 0; j < COLUMS; ++j) {
            if (gameBoard.get_slot_type(i, j) == UNUSED) {
                continue;
            }

            // Luo uusi QPushButton ja aseta sen väri sen solutyypin mukaan
            QPushButton *button = new QPushButton;

            switch(gameBoard.get_slot_type(i, j)) {
                case RED:
                    button->setStyleSheet("background-color: red");
                    break;
                case GREEN:
                    button->setStyleSheet("background-color: green");
                    break;
                case UNUSED:
                    button->setEnabled(false);
                    break;
                case EMPTY:
                    button->setStyleSheet("background-color: white");
                    break;
            }

            // Aseta napin sijainti ja koko pelilaudalla
            button->setGeometry(j * BUTTON_SIZE, i * BUTTON_SIZE,
                                BUTTON_SIZE, BUTTON_SIZE);
            button->setParent(boardWidget);

            // Aseta napille koordinaatit (j, i) ja lisää se painikelistalle
            button->setProperty("point", QVariant::fromValue(
                                    Point{static_cast<int>(j),
                                          static_cast<int>(i)}));
            buttons_.push_back(button);

            connect(button, &QPushButton::clicked, this,
                    &MainWindow::handle_button_clicked);
        }
    }
}

void MainWindow::set_up_timer()
{
    // Tarkista, onko peli jo käynnissä, jotta useampia ajastimia
    // ei saada päälle samanaikaisesti.
    if (!game_started) {
           return;
       }

    // Tarkista, onko ajastin jo olemassa ja aktiivinen
   if (timer) {
       if (timer->isActive()) {
           return;
           }
       } else {
       elapsed_time = QTime(0, 0, 0);
       timer = new QTimer(this);
       connect(timer, &QTimer::timeout, this, &MainWindow::update_timer);
       }

   // Näytä kulunut aika LCD-näytöllä ja käynnistä ajastin
   ui->lcd_timer->display(elapsed_time.toString("mm:ss"));
   timer->start(TIME_SECONDS);
}

void MainWindow::update_timer()
{
    elapsed_time = elapsed_time.addSecs(1);
    QString elapsed_time_text = elapsed_time.toString("mm:ss");
    ui->lcd_timer->display(elapsed_time_text);
}

void MainWindow::execute_move(Point selected_point, Point clicked_point,
                              QPushButton *clicked_button)
{
    // Tallenna siirtohistoria undo-painiketta varten
    move_history_.push_back({selected_point, clicked_point,
                             selected_button_->styleSheet()});

    clicked_button->setStyleSheet(selected_button_->styleSheet());
    selected_button_->setStyleSheet("background-color: white;");

    // Lisää siirtojen määrää ja päivitä näyttö
    amount_of_moves++;
    std::string moves = std::to_string(amount_of_moves);
    ui->event_log_browser->setText("");
    ui->lcd_made_moves->display(amount_of_moves);
    ui->undo_button->setEnabled(true);

    // Tarkista, päättyykö peli eli käyttäjä voittaa
    if (gameBoard.is_game_over()) {

        timer->stop();
        ui->undo_button->setDisabled(true);
        ui->pause_button->setDisabled(true);

        // Jos nimimerkki laitettu lisätään se leaderboardiin, ja näytetään
        // tulokset.
        if (nickname_set_) {
            read_leaderboard();
        }
        // Poista käytöstä kaikki pelialustan painikkeet
        for (QPushButton *button : buttons_) {
            button->setDisabled(true);
        }
        // Jos siirrot ovat vähimmäismäärä, aseta taustaväri keltaiseksi
        if (amount_of_moves == MIN_POSSIBLE_MOVES) {
            this->setStyleSheet("background-color: yellow");
        }
        // Tarkista, onko tavoite asetettu ja näytä viesti sen mukaaisesti
        if (target_set_) {
            if (amount_of_moves > target_value_) {
                ui->event_log_browser->setText(
                            QString("You lost to your target! You made ") +
                            QString::fromStdString(moves) +
                            (" moves and in time: ") +
                            elapsed_time.toString("mm:ss"));
            }
            if (amount_of_moves <= target_value_) {
                ui->event_log_browser->setText(
                            QString("You won your target! You made ") +
                            QString::fromStdString(moves) +
                            (" moves and in time: ") +
                            elapsed_time.toString("mm:ss"));
            }
        }
        else {
            ui->event_log_browser->setText(
                        QString("You are a Winner! You made ") +
                        QString::fromStdString(moves) +
                        (" moves and in time: ") +
                        elapsed_time.toString("mm:ss"));
        }
    }
}

void MainWindow::read_leaderboard()
{
    // Avaa tulostaulun tiedosto
    QFile file("leaderboard.txt");

    // Jos tiedoston avaaminen epäonnistuu, näytä virheviesti
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        ui->leaderboard_browser->setText(
                    "Error: Unable to open leaderboard file");
        return;
    }
    QTextStream in(&file);

    // Lue tulostaulun tiedot tiedostosta ja tallenna ne QMap:iin
    QMap<QPair<int, QTime>, QString> leaderboard;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(" ");
        if (data.size() == 3) {
            int moves = data[1].toInt();
            QTime time = QTime::fromString(data[2], "mm:ss");
            leaderboard.insert(QPair<int, QTime>(moves, time), data[0]);
        }
    }

    // Lisää pelaajan tulokset tulostauluun
    QString nickname = ui->nickname_edit->toPlainText();
    int player_score = amount_of_moves;
    QTime player_time = elapsed_time;
    leaderboard.insert(QPair<int, QTime>(player_score, player_time), nickname);

    // Tyhjennä tiedosto ja kirjoita uudet tulokset
    file.resize(0);
    QTextStream out(&file);
    for (auto it = leaderboard.constBegin();it != leaderboard.constEnd(); ++it){
        out << it.value() << " " << it.key().first << " " <<
               it.key().second.toString("mm:ss") << "\n";
    }

    // Näytä tulostaulu käyttöliittymässä
    QString leaderboard_text;
    int rank = 1;
    for (auto it = leaderboard.constBegin(); it !=
         leaderboard.constEnd(); ++it, ++rank) {
        leaderboard_text += QString::number(rank) + ". " + it.value() + " " +
                QString::number(it.key().first) + " " +
                it.key().second.toString("mm:ss") + "\n";
    }
    ui->leaderboard_browser->setText(leaderboard_text);
    file.close();
}

void MainWindow::handle_button_clicked()
{
    // Jos peli ei ole käynnissä, älä etene. Käyttäjä voi kokeilla
    // pelilaudan näppäimiä ennen pelin alkamista.
    if (!game_started) {
            return;
    }

    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    // Hae Point-arvot klikatulle ja valitulle nappulalle
    Point clickedPoint = clickedButton->property("point").value<Point>();
    QString clickedButtonColor = clickedButton->styleSheet();

    if (!selected_button_) {
        if (!has_chosen_color_ && (clickedButtonColor.contains("red") ||
                                   clickedButtonColor.contains("green"))) {
            selected_button_ = clickedButton;
            has_chosen_color_ = true;

            // Tallenna valitun nappulan alkuperäinen tyylisääntö
            selected_button_style_sheet = selected_button_->styleSheet();

            // Lisää keltainen kehys valitun nappulan alkuperäiseen tyyliin.
            // Tällöin käyttäjä näkee valitun nappulan
            selected_button_->setStyleSheet(selected_button_style_sheet +
                                            ";border: 4px solid yellow;");
            ui->undo_button->setDisabled(true);
        }
    } else {

        // Jos nappula on jo valittu, suorita siirto ja nollaa valittu nappula.
        Point selectedPoint =selected_button_->property("point").value<Point>();
        selected_button_->setStyleSheet(selected_button_style_sheet);

        // Jos valittu ja klikattu nappula ovat samat, näytä virheilmoitus
        if (selectedPoint == clickedPoint) {
            ui->event_log_browser->setText("Choose again.");

        // Jos siirto onnistuu, suorita se
        } else if (gameBoard.move(selectedPoint, clickedPoint)) {
            execute_move(selectedPoint, clickedPoint, clickedButton);

        } else {
            ui->event_log_browser->setText("Incorrect move. Try again.");
        }

        // Nollaa valittu nappula ja valittu väri
        selected_button_ = nullptr;
        has_chosen_color_ = false;
    }
}

void MainWindow::on_reset_button_clicked()
{
    this->setStyleSheet("background-color: white");

    // Nollaa pelilauta, siirtohistoria, siirtojen määrä ja valittu nappi
    gameBoard.reset_board();
    move_history_.clear();
    amount_of_moves = 0;
    selected_button_ = nullptr;
    timer->stop();
    delete timer;
    timer = nullptr;
    elapsed_time = QTime(0, 0);

    // Käy läpi kaikki napit ja aseta niiden tilat ja ulkoasu vastaamaan
    // uutta pelilautaa
    for (QPushButton *button : buttons_) {
        Point point = button->property("point").value<Point>();
        button->setEnabled(true);
        int i = point.y;
        int j = point.x;

        switch(gameBoard.get_slot_type(i, j)) {
            case RED:
                button->setStyleSheet("background-color: red");
                break;
            case GREEN:
                button->setStyleSheet("background-color: green");
                break;
            case UNUSED:
                button->setEnabled(false);
                break;
            case EMPTY:
                button->setStyleSheet("background-color: white");
                break;
        }
    }

    // Asetetaan tila vastaamaan uutta peliä.
    ui->start_button->setEnabled(true);
    ui->set_nickname_button->setEnabled(true);
    ui->nickname_edit->setEnabled(true);
    ui->target_spinbox->setEnabled(true);
    ui->set_target_button->setEnabled(true);

    ui->pause_button->setDisabled(true);
    ui->undo_button->setDisabled(true);
    ui->reset_button->setDisabled(true);

    ui->lcd_target_moves->display(0);
    ui->lcd_made_moves->display(amount_of_moves);
    ui->event_log_browser->setText("Press Start button to play the game or "
    "you can set a target for yourself.");
    ui->lcd_timer->display(elapsed_time.toString("mm:ss"));

    target_set_ = false;
    nickname_set_ = false;
    has_chosen_color_ = false;
    game_started = false;

}

void MainWindow::on_pause_button_clicked()
{
    ui->event_log_browser->setText("Game is currently paused. "
    "Press Start button to continue.");
    ui->pause_button->setDisabled(true);
    ui->start_button->setEnabled(true);
    timer->stop();
    for (QPushButton *button : buttons_) {
        button->setDisabled(true);
        }
}

void MainWindow::on_start_button_clicked()
{
    // Poista aloitus-, tavoitteen asetus-, lempinimen asetus- ja
    // lempinimen kirjoituskentän käytettävyys
    ui->start_button->setDisabled(true);
    ui->target_spinbox->setDisabled(true);
    ui->set_target_button->setDisabled(true);
    ui->set_nickname_button->setDisabled(true);
    ui->nickname_edit->setDisabled(true);

    ui->pause_button->setEnabled(true);
    if (!move_history_.empty()) {
        ui->undo_button->setEnabled(true);
    }

    // Jos peliä ei ole vielä aloitettu, tee alustukset
    if (!game_started) {
        game_started = true;
        set_up_timer();
        ui->reset_button->setEnabled(true);
        ui->event_log_browser->setText("Good luck!");
    } else {

        // Jos peli on jo aloitettu, jatka aikaa ja ota painikkeet
        // uudelleen käyttöön
        if (timer) {
            timer->start(TIME_SECONDS);
            }
        for (QPushButton *button : buttons_) {
            button->setEnabled(true);
            }
    }
}

void MainWindow::on_set_target_button_clicked()
{
    // Aseta tavoitearvo ja näytä se LCD-näytöllä
    target_value_ = ui->target_spinbox->value();
    ui->lcd_target_moves->display(target_value_);
    target_set_ = true;
}

QPushButton* MainWindow::get_button_at(Point point)
{
    // Hae painike annetussa pisteessä
     for (QPushButton *button : buttons_) {
         Point button_point = button->property("point").value<Point>();
         if (button_point == point) {
             return button;
         }
     }
     return nullptr;
}

void MainWindow::on_undo_button_clicked()
{
    // Hae edellinen siirto ja poista se siirtohistoriasta
    auto previous_move = move_history_.back();
    move_history_.pop_back();

    Point origin = std::get<1>(previous_move);
    Point destination = std::get<0>(previous_move);
    QString destination_color = std::get<2>(previous_move);

    // Siirrä nappula takaisinpäin
    gameBoard.move(origin, destination);

    QPushButton *origin_button = get_button_at(origin);
    QPushButton *destination_button = get_button_at(destination);

    // Jos alkuperäinen ja kohdenappulat löytyvät, palauta niiden tyylit
    if (origin_button && destination_button) {
        origin_button->setStyleSheet(destination_button->styleSheet());
        destination_button->setStyleSheet(destination_color);
    }

    amount_of_moves--;
    ui->lcd_made_moves->display(amount_of_moves);

    // Jos siirtohistoria on tyhjä, poista kumoa-painikkeen käytettävyys
    if (move_history_.empty()) {
        ui->undo_button->setDisabled(true);
    }
}

void MainWindow::on_set_nickname_button_clicked()
{
    ui->set_nickname_button->setDisabled(true);
    ui->nickname_edit->setDisabled(true);

    // Aseta käyttäjänimen asetus tilaksi 'asetettu'
    nickname_set_ = true;
}

void MainWindow::on_quit_button_clicked()
{
    QApplication::quit();
}
