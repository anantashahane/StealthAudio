#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QString"
#include "stealth.h"
#include <QtCore>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "/Users", "Wave Audio (*.wav)");
    ui->EncodeIn->setText(file);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "/Users", "Wave Audio (*.wav)");
    ui->EncodeOut->setText(file);
}

void MainWindow::on_pushButton_3_clicked()
{
    Stealth s;
    const char * filerrhndl = ".wav";
    if (ui->EncodeIn->text().length() == 0 || ui->EncodeOut->text().length() == 0)
    {
        QMessageBox::information(this,"Nothing to do", "File Not Selected");
    }
    else if(ui->EncodeMessage->text().length() == 0)
    {
        QMessageBox::information(this, "No Message", "No Message entered to encode.");
    }
    else if(!ui->EncodeIn->text().endsWith(filerrhndl) || !ui->EncodeOut->text().endsWith(filerrhndl))
    {
        QMessageBox::information(this, "File Error", "Please enter wave (*.wav) files to encode message.");
    }
    else
    {
        QString in = ui->EncodeIn->text();
        QString out = ui->EncodeOut->text();
        QString mes = ui->EncodeMessage->text();
        s.Setinput(in);
        s.Setoutput(out);
        s.Setmessage(mes);
        int i = s.Encode();
        if(i == 0)
        {
            QMessageBox::information(this,"Encodeing Status", "Encoding Successful.");
        }
    }
}



void MainWindow::on_pushButton_4_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "/Users", "Wave Audio (*.wav)");
    ui->DecodeFile->setText(file);
}

void MainWindow::on_pushButton_5_clicked()
{
    if (ui->DecodeFile->text().length() == 0)
    {
        QMessageBox::information(this,"Nothing to do", "File Not Selected");
    }
    else if (!ui->DecodeFile->text().endsWith(".wav"))
    {
        QMessageBox::information(this,"File Error", "Please enter wave (*.wav) files to decode message.");
    }
    Stealth s;
    QString in = ui->DecodeFile->text();
    s.Setinput(in);
    QString str = s.Decode();
    ui->DecodeMessage->setText(str);
}
