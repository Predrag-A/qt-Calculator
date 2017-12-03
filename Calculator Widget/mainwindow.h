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
    void onBtnClicked();
    void onResultChanged(QString);
    void onResultHistoryChanged(QString);

private:
    Ui::MainWindow *ui;
    CalculatorLogic *logic;
    void ConnectElements();

};

#endif // MAINWINDOW_H
