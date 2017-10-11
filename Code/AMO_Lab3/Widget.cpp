#include "Widget.h"
#include "ui_Widget.h"
#include "lagrangeinterpolatedfunction.h"
#include "newtoninterpolatedfunction.h"
#include <QtCharts>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ch = new QtCharts::QChart();
    ch->legend()->hide();

    chV = new QtCharts::QChartView(ch);
    chV->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chV);

    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::draw);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::sine);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::func);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::draw()
{
    QtCharts::QLineSeries* starting = new QtCharts::QLineSeries;
    QtCharts::QLineSeries* interpolatedN = new QtCharts::QLineSeries;
    QtCharts::QLineSeries* interpolatedN2 = new QtCharts::QLineSeries;

    QStringList sx = (ui->lineEdit->text().split(' '));
    QStringList sy = (ui->lineEdit_2->text().split(' '));
    if (sx.size() != sy.size())
        throw BadBoundsException();

    std::vector<float> x, y;
    for (auto it : sx)
        if (it != "")
            x.push_back(it.toFloat());
    for (auto it : sy)
        if (it != "")
            y.push_back(it.toFloat());

    for (size_t i = 0; i < x.size(); i++)
        (*starting) << QPointF(x[i], y[i]);

    NewtonInterpolatedFunction nf(x, y);

    float b = x.front() - 0.01f, e = x.back() + 0.01f;
    float step = (e - b) / 300.f;
    for (float i = b; i <= e; i += step)
        (*interpolatedN) << QPointF(i, nf(i));
    for (float i = b; i <= e; i += step * 30)
        (*interpolatedN2) << QPointF(i, nf(i));

    ch->removeAllSeries();
    //ch->addSeries(starting);
    ch->addSeries(interpolatedN);
    ch->addSeries(interpolatedN2);
    ch->createDefaultAxes();
    ui->verticalLayout->setStretch(0,1);
    ui->verticalLayout->setStretch(1,1);
    ui->verticalLayout->setStretch(2,1);
    ui->verticalLayout->setStretch(3,100);
}

#include <cmath>
void Widget::sine()
{
    QString sx, sy;
    for (float f = ui->lineEdit_3->text().toFloat(); f <= ui->lineEdit_4->text().toFloat(); f += ui->lineEdit_5->text().toFloat()) {
        sx += QString::number(f) + ' ';
        sy += QString::number(sinf(f)) + ' ';
    }
    ui->lineEdit->setText(sx);
    ui->lineEdit_2->setText(sy);
}

void Widget::func()
{
    QString sx, sy;
    for (float f = ui->lineEdit_3->text().toFloat(); f <= ui->lineEdit_4->text().toFloat(); f += ui->lineEdit_5->text().toFloat()) {
        sx += QString::number(f) + ' ';
        sy += QString::number(expf(-f + 1.f / f)) + ' ';
    }
    ui->lineEdit->setText(sx);
    ui->lineEdit_2->setText(sy);
}
