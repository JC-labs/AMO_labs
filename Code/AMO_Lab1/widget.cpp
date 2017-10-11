#include "widget.h"
#include "ui_widget.h"
#include "tasks.hpp"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->radioButton,&QRadioButton::clicked,this,&Widget::rb1);
    connect(ui->radioButton_2,&QRadioButton::clicked,this,&Widget::rb2);
    connect(ui->radioButton_3,&QRadioButton::clicked,this,&Widget::rb3);
    connect(ui->pushButton,&QRadioButton::clicked,this,&Widget::calc);
}

Widget::~Widget()
{
    delete ui;
}

float *Widget::toArray(QString s)
{
    QStringList l = s.split(',');
    float* r = new float[l.size()];
    for (int i = 0; i < l.size(); i++)
        r[i] = l[i].toFloat();
    return r;
}

void Widget::rb1()
{
    ui->label->setText("a =");
    ui->label_2->setText("b =");
    ui->label_3->setText("x =");
}

void Widget::rb2()
{
    ui->label->setText("i =");
    ui->label_2->setText("x =");
    ui->label_3->setText("c =");
}

void Widget::rb3()
{
    ui->label->setText("n =");
    ui->label_2->setText("a =");
    ui->label_3->setText("b =");
}

void Widget::calc()
{
    if (ui->radioButton->isChecked()) {
        float a = ui->lineEdit->text().toFloat();
        float b = ui->lineEdit_2->text().toFloat();
        float x = ui->lineEdit_3->text().toFloat();
        float r = task1(a,b,x);
        ui->lineEdit_4->setText(QString::number(r));
    } else if (ui->radioButton_2->isChecked()) {
        int i = ui->lineEdit->text().toInt();
        float b = ui->lineEdit_2->text().toFloat();
        float* x = toArray(ui->lineEdit_3->text());
        float r = task2(i,b,x);
        ui->lineEdit_4->setText(QString::number(r));
    } else if (ui->radioButton_3->isChecked()) {
        int a = ui->lineEdit->text().toFloat();
        float* b = toArray(ui->lineEdit_2->text());
        float* x = toArray(ui->lineEdit_3->text());
        float r = task3(a,b,x);
        ui->lineEdit_4->setText(QString::number(r));
    }
}
