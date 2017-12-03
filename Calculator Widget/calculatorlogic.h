#ifndef CALCULATORLOGIC_H
#define CALCULATORLOGIC_H

#include <QWidget>
#include <QStack>

class CalculatorLogic : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorLogic(QWidget *parent = nullptr);

    void doCommand(QString);                    //Parses the input QString

signals:
    //No implementation for signals
    void resultChanged(QString);                //Signal that changes the result field
    void resultHistoryChanged(QString);         //Signal that changes the history field

public slots:

private:
    double Calculate(double, double, QString);  //Calculates two doubles depending on the operator
    bool StackSize();                           //Compares operandStack and operatorStack size
    int GetPrecedence(QString);                 //Returns precedence value of operators
    void Process();                             //Pops two operands and an operator, calculates and pushes the result

    QString changes;                            //String containing the history of changes
    QString buffer;                             //String containing current expression
    QStack<QString> operandStack;               //Stack of operands
    QStack<QString> operatorStack;              //Stack of operators
};

#endif // CALCULATORLOGIC_H
