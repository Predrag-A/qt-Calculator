#include "calculatorlogic.h"
#include <QTextStream>

CalculatorLogic::CalculatorLogic(QWidget *parent) : QWidget(parent)
{

}

void CalculatorLogic::doCommand(QString q)
{
    QTextStream out(stdout);

    if(q>="0" && q<="9"){
        if(operandStack.empty()){
            operandStack.push(q);
            emit resultChanged(q);
        }
        else {
            if(!StackSize()){
                operandStack.push(q);
                emit resultChanged(q);
            }
            else{
                QString popped = operandStack.pop();
                popped += q;
                operandStack.push(popped);
                emit resultChanged(popped);
            }
        }
    }
    else if(q=="±"){
        if(!operandStack.empty()){
            double temp = operandStack.pop().toDouble();
            temp = -temp;
            operandStack.push(QString::number(temp));
            emit resultChanged(QString::number(temp));
        }
    }
    else if(q == "C"){
        if(!operandStack.empty()){
                operandStack.pop();
                emit resultChanged("");
        }
    }
    else if(q == "AC"){
        while(!operandStack.empty())
            operandStack.pop();
        while(!operatorStack.empty())
            operatorStack.pop();
        emit resultChanged("");
    }
    else if(q == "√"){
        if(!operandStack.empty()){
            if(operandStack.last().toDouble()>0){
                QString result = QString::number(sqrt(operandStack.pop().toDouble()));
                operandStack.push(result);
                emit resultChanged(result);
            }
        }
    }
    else if(q=="."){
        if(!operandStack.empty()){
                if(!operandStack.last().contains(".")){
                    QString temp = operandStack.pop();
                    temp += ".";
                    operandStack.push(temp);
                    emit resultChanged(temp);
                }
        }
    }
    else if(q=="+" || q=="-" || q=="*" || q == "/"){
        if(!operatorStack.empty() && StackSize()){
            out << "Entered";
                while(!operatorStack.empty() &&(GetPrecedence(operatorStack.last()) >= GetPrecedence(q))){
                    out << "While";
                    double right = operandStack.pop().toDouble();
                    QString operation = operatorStack.pop();
                    double left = operandStack.pop().toDouble();
                    double result = Calculate(left, right, operation);
                    operandStack.push(QString::number(result));
                }
            out << "Finished";
            operatorStack.push(q);
        }
        else
            operatorStack.push(q);
    }
    else if(q=="="){
        if(!operandStack.empty()){
            double result;

            while(operandStack.size()>1){
                 double right = operandStack.pop().toDouble();
                 QString operation = operatorStack.pop();
                 double left = operandStack.pop().toDouble();
                 result = Calculate(left,right,operation);
                 changes+= QString::number(left) + operation + QString::number(right) + "=" + QString::number(result) + ";";
                 operandStack.push(QString::number(result));
                 emit resultChanged(QString::number(result));
                 emit resultHistoryChanged(changes);
            }
            //changes+= "=" + QString::number(result) + ";";
            //while(!operandStack.empty())
            //    operandStack.pop();
            //emit resultHistoryChanged(changes);
            //emit resultChanged("");
        }
    }
}

double CalculatorLogic::Calculate(double left, double right, QString operation){
    if(operation == "+")
        return left+right;
    if(operation == "-")
        return left-right;
    if(operation == "*")
        return left*right;
    return left/right;
}

bool CalculatorLogic::StackSize()
{
    if(operatorStack.size()+1 == operandStack.size())
        return true;
    return false;
}

int CalculatorLogic::GetPrecedence(QString op){
    if(op == "+" || op == "-")
        return 1;
    else return 2;
}
