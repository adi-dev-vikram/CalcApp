#include "calcapp.h"
#include "ui_calcapp.h"
#include <QMessageBox>


double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool subTrigger = false;
bool addTrigger = true;

CalcApp::CalcApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalcApp)
{
    ui->setupUi(this);
    ui->display->setText(QString::number(calcVal));
    QPushButton *numButton[10];
    for (int i =0; i<10;++i)
    {
        QString buttonName = "Button" + QString::number(i);
        numButton[i] =CalcApp::findChild<QPushButton *>(buttonName);
        connect(numButton[i], SIGNAL(released()), this, SLOT(NumPressed()));

    }
    // Connect signals and slots for math buttons
       connect(ui->Add, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));
       connect(ui->Sub, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));
       connect(ui->Mult, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));
       connect(ui->Div, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));

       // Connect equals button
       connect(ui->Equals, SIGNAL(released()), this,
               SLOT(EqualButton()));
}

CalcApp::~CalcApp()
{
    delete ui;
}

void CalcApp::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->display->text();
    if((displayVal.toDouble()==0) ||(displayVal.toDouble()== 0.0 ))
    {
        ui->display->setText(butVal);
    }
    else {
        QString newVal = displayVal + butVal;
        double dblnewVal = newVal.toDouble();
        ui->display->setText(QString::number(dblnewVal,'g',16));
    }


}

void CalcApp::MathButtonPressed(){

    QString displayVal = ui->display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseSensitive)==0)
    {
        divTrigger=true;
        printf("hi1");
    }
    else if(QString::compare(butVal, "*", Qt::CaseSensitive)==0)
    {
        multTrigger=true;
        printf("hi2");
    }
    else if(QString::compare(butVal, "+", Qt::CaseSensitive)==0)
    {
        addTrigger=true;
        printf("hi3\n");
    }
    else {
        subTrigger=true;
        printf("hi4");
    }
    ui->display->setText("");

}

void CalcApp::EqualButton(){
    double solution =0.0;
    QString displayVal = ui->display->text();
    double dbldispVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger)
    {
        if(addTrigger)
        {
            solution = calcVal + dbldispVal;

        }
        else if (subTrigger)
        {
            solution = calcVal - dbldispVal;
        }
        else if (multTrigger)
        {
            solution = calcVal*dbldispVal;
        }
        else {
            if(dbldispVal==0)
            {
                QMessageBox::warning(
                       this,
                       tr("My App"),
                       tr("Can't Perform Divison. Zero Erro...") );
            }
            else {
                solution = calcVal/dbldispVal;

            }
        }
    }
    ui->display->setText(QString::number(solution));
    printf("%f", solution);
}

void CalcApp::ChangeNumberSign(){

    // Get the value in the display
    QString displayVal = ui->display->text();

    // Regular expression checks if it is a number
    // plus sign
    QRegExp reg("[-+]?[0-9.]*");

    // If it is a number change the sign
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        // Put solution in display
        ui->display->setText(QString::number(dblDisplayValSign));
    }

}
