#include "calculatorlogic.h"
#include <QTextStream>

CalculatorLogic::CalculatorLogic(QWidget *parent) : QWidget(parent)
{

}

void CalculatorLogic::doCommand(QString q)
{
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
                QString popped = operandStack.pop();
                popped = popped.left(popped.size()-1);
                operandStack.push(popped);
                emit resultChanged(operandStack.top());
        }
    }
    else if(q == "AC"){
        while(!operandStack.empty())
            operandStack.pop();
        while(!operatorStack.empty())
            operatorStack.pop();
        buffer = "";
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
        if(!StackSize())
            return;
        if(operandStack.last().toDouble()<0)
            buffer+="(" + operandStack.last() + ")";
        else
            buffer+=operandStack.last();
        if(!operatorStack.empty()){
                while(!operatorStack.empty() &&(GetPrecedence(operatorStack.last()) >= GetPrecedence(q)))
                    Process();
            operatorStack.push(q);
        }
        else
            operatorStack.push(q);
        buffer+=q;
        emit resultChanged(operandStack.last());
    }
    else if(q=="="){
        if(!operandStack.empty()){            
            if(operandStack.last().toDouble()<0)
                buffer+="(" + operandStack.last() + ")";
            else
                buffer+=operandStack.last();
            while(operandStack.size()>1)
                Process();
            buffer+= "=" + operandStack.last();
            changes+=buffer+";";
            buffer = "";
            if(operandStack.last() == "0")
                emit resultChanged(operandStack.pop());
            else
                emit resultChanged(operandStack.last());
            emit resultHistoryChanged(changes);
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

void CalculatorLogic::Process(){
    double right = operandStack.pop().toDouble();
    QString operation = operatorStack.pop();
    double left = operandStack.pop().toDouble();
    operandStack.push(QString::number(Calculate(left, right, operation)));
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
