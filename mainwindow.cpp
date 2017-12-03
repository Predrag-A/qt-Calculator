#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logic = new CalculatorLogic(parent);
    ConnectElements();
}

MainWindow::~MainWindow()
{
    if(ui != nullptr)
        delete ui;
    if(logic != nullptr)
        delete logic;
}

void MainWindow::onBtnClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    logic->doCommand((btn->text()));

}

void MainWindow::onResultChanged(QString q)
{
    ui->result->setText(q);
}

void MainWindow::onResultHistoryChanged(QString q)
{
    ui->history->clear();
    QStringList resultList = q.split(";");
    for(int i=0;i<resultList.size();i++){
        ui->history->appendPlainText(resultList[i]);
    }
}

void MainWindow::ConnectElements()
{
    connect(ui->btn0,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn1,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn2,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn3,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn4,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn5,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn6,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn7,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn8,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btn9,SIGNAL(clicked()),this,SLOT(onBtnClicked()));

    connect(ui->btnAllClear,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnClear,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnDot,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnSign,SIGNAL(clicked()),this,SLOT(onBtnClicked()));

    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnMultiply,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    connect(ui->btnEquals,SIGNAL(clicked()),this,SLOT(onBtnClicked()));

    connect(logic,SIGNAL(resultChanged(QString)),this,SLOT(onResultChanged(QString)));
    connect(logic,SIGNAL(resultHistoryChanged(QString)),this,SLOT(onResultHistoryChanged(QString)));
}
