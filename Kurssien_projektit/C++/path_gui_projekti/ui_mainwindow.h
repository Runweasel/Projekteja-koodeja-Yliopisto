/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *event_log_browser;
    QPushButton *reset_button;
    QLabel *Event_log;
    QPushButton *quit_button;
    QLCDNumber *lcd_timer;
    QLCDNumber *lcd_made_moves;
    QLabel *Timer;
    QLabel *Made_moves;
    QPushButton *start_button;
    QPushButton *pause_button;
    QLabel *Target_moves;
    QSpinBox *target_spinbox;
    QPushButton *set_target_button;
    QLCDNumber *lcd_target_moves;
    QPushButton *undo_button;
    QTextBrowser *leaderboard_browser;
    QLabel *Leaderboard;
    QTextEdit *nickname_edit;
    QLabel *label;
    QPushButton *set_nickname_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1006, 565);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        event_log_browser = new QTextBrowser(centralwidget);
        event_log_browser->setObjectName(QString::fromUtf8("event_log_browser"));
        event_log_browser->setGeometry(QRect(20, 270, 221, 91));
        reset_button = new QPushButton(centralwidget);
        reset_button->setObjectName(QString::fromUtf8("reset_button"));
        reset_button->setGeometry(QRect(890, 50, 91, 41));
        Event_log = new QLabel(centralwidget);
        Event_log->setObjectName(QString::fromUtf8("Event_log"));
        Event_log->setGeometry(QRect(20, 240, 63, 20));
        quit_button = new QPushButton(centralwidget);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        quit_button->setGeometry(QRect(890, 450, 91, 41));
        lcd_timer = new QLCDNumber(centralwidget);
        lcd_timer->setObjectName(QString::fromUtf8("lcd_timer"));
        lcd_timer->setGeometry(QRect(20, 50, 101, 51));
        lcd_made_moves = new QLCDNumber(centralwidget);
        lcd_made_moves->setObjectName(QString::fromUtf8("lcd_made_moves"));
        lcd_made_moves->setGeometry(QRect(20, 170, 101, 51));
        Timer = new QLabel(centralwidget);
        Timer->setObjectName(QString::fromUtf8("Timer"));
        Timer->setGeometry(QRect(20, 20, 63, 20));
        Made_moves = new QLabel(centralwidget);
        Made_moves->setObjectName(QString::fromUtf8("Made_moves"));
        Made_moves->setGeometry(QRect(20, 140, 91, 20));
        start_button = new QPushButton(centralwidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(890, 130, 91, 41));
        pause_button = new QPushButton(centralwidget);
        pause_button->setObjectName(QString::fromUtf8("pause_button"));
        pause_button->setGeometry(QRect(890, 210, 91, 41));
        Target_moves = new QLabel(centralwidget);
        Target_moves->setObjectName(QString::fromUtf8("Target_moves"));
        Target_moves->setGeometry(QRect(140, 140, 101, 20));
        target_spinbox = new QSpinBox(centralwidget);
        target_spinbox->setObjectName(QString::fromUtf8("target_spinbox"));
        target_spinbox->setGeometry(QRect(840, 370, 41, 41));
        set_target_button = new QPushButton(centralwidget);
        set_target_button->setObjectName(QString::fromUtf8("set_target_button"));
        set_target_button->setGeometry(QRect(890, 370, 91, 41));
        lcd_target_moves = new QLCDNumber(centralwidget);
        lcd_target_moves->setObjectName(QString::fromUtf8("lcd_target_moves"));
        lcd_target_moves->setGeometry(QRect(140, 170, 101, 51));
        undo_button = new QPushButton(centralwidget);
        undo_button->setObjectName(QString::fromUtf8("undo_button"));
        undo_button->setGeometry(QRect(890, 290, 91, 41));
        leaderboard_browser = new QTextBrowser(centralwidget);
        leaderboard_browser->setObjectName(QString::fromUtf8("leaderboard_browser"));
        leaderboard_browser->setGeometry(QRect(695, 50, 181, 281));
        Leaderboard = new QLabel(centralwidget);
        Leaderboard->setObjectName(QString::fromUtf8("Leaderboard"));
        Leaderboard->setGeometry(QRect(740, 20, 101, 20));
        nickname_edit = new QTextEdit(centralwidget);
        nickname_edit->setObjectName(QString::fromUtf8("nickname_edit"));
        nickname_edit->setGeometry(QRect(20, 420, 221, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 390, 111, 20));
        set_nickname_button = new QPushButton(centralwidget);
        set_nickname_button->setObjectName(QString::fromUtf8("set_nickname_button"));
        set_nickname_button->setGeometry(QRect(20, 460, 111, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1006, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        reset_button->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        Event_log->setText(QCoreApplication::translate("MainWindow", "Event log:", nullptr));
        quit_button->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        Timer->setText(QCoreApplication::translate("MainWindow", "Timer:", nullptr));
        Made_moves->setText(QCoreApplication::translate("MainWindow", "Made moves:", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pause_button->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        Target_moves->setText(QCoreApplication::translate("MainWindow", "Target moves:", nullptr));
        set_target_button->setText(QCoreApplication::translate("MainWindow", "Set Target", nullptr));
        undo_button->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        Leaderboard->setText(QCoreApplication::translate("MainWindow", "Leaderboard:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Enter nickname:", nullptr));
        set_nickname_button->setText(QCoreApplication::translate("MainWindow", "Set nickname", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
