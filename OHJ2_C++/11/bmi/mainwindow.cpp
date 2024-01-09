#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "string"

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


void MainWindow::on_countButton_clicked()
{
    QString weight_ = ui->weightLineEdit->text();
    QString height_ = ui->heightLineEdit->text();

    if ( height_ == "0" || height_ == "" ){
        ui->resultLabel->setText("Cannot count.");
        return;
    }

    double weight = weight_.toInt();
    double height = height_.toInt();

    double BMI_ = weight/((height*height)/10000);

    QString BMI = QString::number(BMI_);

    ui->resultLabel->setText(BMI);

    if ( BMI_ > 25) {
        ui->infoTextBrowser->setText("You are overweight.");
        return;
    }

    if ( BMI_ <= 18.5) {
        ui->infoTextBrowser->setText("You are underweight.");
        return;
    }

    ui->infoTextBrowser->setText("Your weight is normal.");
    return;
}

