#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculatorlogic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onBtnClicked();                        //Slot that triggers when any button is clicked
    void onResultChanged(QString);              //Slot that triggers when resultChanged signal is emitted
    void onResultHistoryChanged(QString);       //Slot that triggers when resultHistoryChanged signal is emiitted

private:
    Ui::MainWindow *ui;

    CalculatorLogic *logic;                     //CalculatorLogic object instance
    void ConnectElements();                     //Method that connects all signals and slots

};

#endif // MAINWINDOW_H
