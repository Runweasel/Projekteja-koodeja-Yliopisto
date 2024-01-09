#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxE->setMaximum(5);
    ui->spinBoxE->setMinimum(0);

    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxN->setMinimum(0);

    ui->spinBoxG->setMaximum(MAX_G_POINTS);
    ui->spinBoxG->setMinimum(0);

    ui->spinBoxP->setMaximum(MAX_P_POINTS);
    ui->spinBoxP->setMinimum(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    N_Score_ = arg1;
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    G_Score_ = arg1;
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    P_Score_ = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    Exam_Score_ = arg1;
}

void MainWindow::on_calculatePushButton_clicked()
{
    double N_Score = ui->spinBoxN->value();
    double P_Score = ui->spinBoxP->value();
    double G_Score = ui->spinBoxG->value();
    double Exam_Score = ui->spinBoxE->value();

    int total = calculate_total_grade(N_Score, G_Score, P_Score, Exam_Score);
    QString total_ = QString::number(total);

    int weekly = score_from_weekly_exercises(N_Score, G_Score);
    QString weekly_ = QString::number(weekly);

    int project = score_from_projects(P_Score);
    QString project_ = QString::number(project);

    ui->textBrowser->setText("W-Score: " + weekly_ + "\n" + "P-Score: " + project_ + "\n" + "Total grade: " + total_);

}

