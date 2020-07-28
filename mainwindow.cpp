#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>
#include <iostream>
#include <QRandomGenerator64>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int lvl = 0; // 0 - easy, 1 - medium, 2 - hard;

void MainWindow::on_btn_easy_clicked()
{
    lvl = 0;
    ui->groupBox->setVisible(0);
    ui->label_2->setText("Pick a number between 0 and 50");
}

void MainWindow::on_btn_medium_clicked()
{
    lvl = 1;
    ui->groupBox->setVisible(0);
    ui->label_2->setText("Pick a number between 0 and 100");
}

void MainWindow::on_btn_hard_clicked()
{
    lvl = 2;
    ui->groupBox->setVisible(0);
    ui->label_2->setText("Pick a number between -500 and 500");
}

int value;
int tries = 0;

void MainWindow::on_pushButton_clicked()
{
    qsrand(time(NULL));

    if( lvl == 0 ){
        value = qrand()%51;     //easy (0 - 50)
    } else if ( lvl == 1 ){
        value = qrand()%101;    //medium (0 - 100)
    } else {
        value = qrand()%1001 - 500; //hard (-500 - 500)
    }

    ui->input->setEnabled(1);                                       //
    ui->pushButton->setVisible(0);                                  // Hiding button and set input to enable (game is starting)
    ui->tries->setText("Your attempts: "+QString::number(tries));   //

}

void MainWindow::on_input_editingFinished()
{
    QString string_ans = ui->input->text();
    int ans = string_ans.toInt();
    if(ans == value){
        ui->msg->setStyleSheet("color: green;");
        ui->msg->setText("WIN!");
        ui->pushButton_2->setVisible(1);
        ui->input->setEnabled(0);
    } else if (ans > value){
        ui->msg->setStyleSheet("color: red;");
        ui->msg->setText("YOUR NUMBER IS TOO HIGH");
    } else{
        ui->msg->setStyleSheet("color: red;");
        ui->msg->setText("YOUR NUMBER IS TOO LOW");
    }
    ui->input->setText("");
    tries++;
    ui->tries->setText("Your attempts: "+QString::number(tries));
}

void MainWindow::on_pushButton_2_clicked()
{
    tries = 0;
    ui->msg->clear();
    ui->tries->setText("Your attempts: "+QString::number(tries));
    ui->groupBox->setVisible(1);
    ui->pushButton_2->setVisible(0);
    ui->pushButton->setVisible(1);
}
