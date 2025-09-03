#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void dotClicked();
    void backspaceClicked();
    void clearClicked();
    void operatorClicked();
    void equalsClicked();
    void on_something_clicked();

private:
    void abortOperation(const QString &msg);
    void applyPendingOperator(double rightOperand);
    void updateDisplay(const QString &text);

    Ui::MainWindow *ui;
    double leftOperand = 0.0;
    QString pendingOperator;
    bool waitingForOperand = true;
};
#endif // MAINWINDOW_H
