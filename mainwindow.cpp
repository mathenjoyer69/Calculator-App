#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Calculator");

    const QList<QPushButton*> digitButtons = {
        ui->zero, ui->one, ui->two, ui->three, ui->four,
        ui->five, ui->six, ui->seven, ui->eight, ui->nine
    };

    for (auto *b : digitButtons){
        connect(b, &QPushButton::clicked, this, &MainWindow::digitClicked);
    }
    connect(ui->Add, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->Sub, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->Mult, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->Div, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    connect(ui->Equals, &QPushButton::clicked, this, &MainWindow::equalsClicked);
    connect(ui->dot, &QPushButton::clicked, this, &MainWindow::dotClicked);
    connect(ui->Backspace, &QPushButton::clicked, this, &MainWindow::backspaceClicked);
    connect(ui->Clear, &QPushButton::clicked, this, &MainWindow::clearClicked);

    ui->expression->setText("0");
    ui->expression->setReadOnly(true);
    ui->expression->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplay(const QString &text) {
    ui->expression->setText(text);
}

void MainWindow::abortOperation(const QString &msg) {
    QMessageBox::warning(this, "Failure", msg);
}

void MainWindow::digitClicked() {
    auto *button = qobject_cast<QPushButton*>(sender());
    const QString digit = button->text();

    QString value = ui->expression->text();
    if(value == "0") {
        value = digit;
    }
    else {
        value += digit;
    }
    updateDisplay(value);
}

void MainWindow::dotClicked() {
    QString value = ui->expression->text();
    value += '.';
    updateDisplay(value);
}

void MainWindow::backspaceClicked() {
    QString value = ui->expression->text();
    if(value.size()>1) {
        value.chop(1);
    }
    else if(value.size() == 1) {
        value = "0";
    }
    updateDisplay(value);
}

void MainWindow::clearClicked() {
    updateDisplay("0");
}

void MainWindow::operatorClicked() {

}

void MainWindow::equalsClicked() {

}

void MainWindow::applyPendingOperator(double rightOperand) {

}









