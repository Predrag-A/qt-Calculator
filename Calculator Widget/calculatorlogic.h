#ifndef CALCULATORLOGIC_H
#define CALCULATORLOGIC_H

#include <QWidget>
#include <QStack>

class CalculatorLogic : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorLogic(QWidget *parent = nullptr);

    QString changes;                    //String containing the history of changes
    QStack<QString> operandStack;       //Stack of operands
    QStack<QString> operatorStack;      //Stack of operators
    void doCommand(QString);            //Parses the input QString

signals:
    //No implementation for signals
    void resultChanged(QString);        //Signal that changes the result field
    void resultHistoryChanged(QString); //Signal that changes the history field

public slots:

private:
    double Calculate(double, double, QString);
    bool StackSize();
    int GetPrecedence(QString);
};

#endif // CALCULATORLOGIC_H
