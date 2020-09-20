#ifndef CALCAPP_H
#define CALCAPP_H

#include <QMainWindow>

namespace Ui {
class CalcApp;
}

class CalcApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalcApp(QWidget *parent = nullptr);
    ~CalcApp();

private:
    Ui::CalcApp *ui;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
};

#endif // CALCAPP_H
