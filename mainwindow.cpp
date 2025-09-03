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
    if(value == "0" || waitingForOperand) {
        value = digit;
        waitingForOperand = false;
    }
    else {
        value += digit;
    }
    updateDisplay(value);
}

void MainWindow::dotClicked() {
    QString value = ui->expression->text();
    if (waitingForOperand){
        value = "0";
        waitingForOperand = false;
    }
    if (!value.contains('.')) {
        value += '.';
    }
    updateDisplay(value);
}

void MainWindow::backspaceClicked() {
    if (waitingForOperand) return;
    QString value = ui->expression->text();
    if(value.size()>1) {
        value.chop(1);
    }
    else if(value.size() == 1) {
        value = "0";
        waitingForOperand = true;
    }
    updateDisplay(value);
}

void MainWindow::clearClicked() {
    waitingForOperand = true;
    leftOperand = 0.0;
    pendingOperator.clear();
    updateDisplay("0");
}

void MainWindow::operatorClicked() {
    auto *button = qobject_cast<QPushButton*>(sender());
    QString op = button->text();

    //convert op
    if (op.toLower() == "x") op = "*";
    else if (op == "÷") op = "/";

    double operand = ui->expression->text().toDouble();
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        applyPendingOperator(operand);
        updateDisplay(QString::number(leftOperand));
    }
    else if (!waitingForOperand) {
        leftOperand = operand;
    }

    pendingOperator = op;
    waitingForOperand = true;
}

void MainWindow::equalsClicked() {
    if (pendingOperator.isEmpty()) return;

    double right = ui->expression->text().toDouble();
    applyPendingOperator(right);
    updateDisplay(QString::number(leftOperand));
    pendingOperator.clear();
    waitingForOperand = true;
}

void MainWindow::applyPendingOperator(double rightOperand) {
    if (pendingOperator == "+") leftOperand += rightOperand;
    else if (pendingOperator == "-") leftOperand -= rightOperand;
    else if (pendingOperator == "*") leftOperand *= rightOperand;
    else if (pendingOperator == "/") {
        if (rightOperand != 0){
            leftOperand /= rightOperand;
        }
        else {
            abortOperation("Division by zero");
            return;
        }
    }
}

void MainWindow::on_something_clicked() {

}

