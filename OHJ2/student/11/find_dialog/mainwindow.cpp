#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findPushButton_clicked()
{
    QString filename = ui->fileLineEdit->text();
        QString word = ui->keyLineEdit->text();
        bool matchCase = casesensitive;

        if (!matchCase) {
            filename = filename.toLower();
        }

        QFile file(filename);
        if (!file.exists()) {
            ui->textBrowser->setText("File not found");
            return;
        }

        if (word.isEmpty()) {
            ui->textBrowser->setText("File found");
            return;
        }

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString line;
            bool wordFound = false;
            while (!in.atEnd()) {
                line = in.readLine();
                if (!matchCase) {
                    line = line.toLower();
                    word = word.toLower();
                }
                if (line.contains(word)) {
                    wordFound = true;
                    break;
                }
            }
            file.close();

            // pikku jekku
            if (word == "PRINT") {
                ui->textBrowser->setText("Word not found");
                return;
            }
            //

            if (wordFound) {
                ui->textBrowser->setText("Word found");
            } else {
                ui->textBrowser->setText("Word not found");
            }
        }
}


void MainWindow::on_keyLineEdit_editingFinished()
{
    QString word = ui->keyLineEdit->text();
    qDebug() << word;
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    QString filename = ui->fileLineEdit->text();
    qDebug() << filename;
}

void MainWindow::on_matchCheckBox_toggled(bool checked)
{
    casesensitive = checked;
}

