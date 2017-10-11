#include "widget.h"
#include "ui_widget.h"
#include <random>
#include <chrono>
#include <QtCharts/QtCharts>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ch = new QtCharts::QChart();
    ch->legend()->hide();

    chV = new QtCharts::QChartView(ch);    
    chV->setRenderHint(QPainter::Antialiasing);
    chV->hide();

    b = new QPushButton("Back");
    b->hide();

    ui->verticalLayout_4->addWidget(chV);
    ui->verticalLayout_4->addWidget(b);

    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::generateRandom);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::sort);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::chart);
    connect(b, &QPushButton::clicked, this, &Widget::unchart);
}

Widget::~Widget()
{
    delete ui;
}

float* fillArray(size_t n) {
    std::random_device seed;
    std::mt19937_64 g(seed());
    std::uniform_real_distribution<float> d;
    float* res = new float[n];
    for (size_t i = 0; i < n; i++)
        res[i] = d(g);
    return res;
}

template<typename Type>
void sortBubble(Type* array, size_t size) {
     for (size_t c = 0 ; c < size - 1; c++) {
         for (size_t d = 0 ; d < size - c - 1; d++) {
             if (array[d] > array[d + 1]) {
                 Type swap = array[d];
                 array[d] = array[d + 1];
                 array[d + 1] = swap;
             }
         }
     }
}

void Widget::generateRandom()
{
    size_t n = ui->lineEdit->text().toLongLong();
    float* t = fillArray(n);
    QString s;
    for (size_t i = 0; i < n; i++)
        s += QString::number(t[i]) + " \t";
    ui->textEdit->setText(s);
}

void Widget::sort()
{
    QStringList s;
    s = ui->textEdit->toPlainText().split(' ');
    size_t size = s.size();
    float* a = new float[size];
    for (size_t i = 0; i < size; i++)
        a[i] = s[i].toFloat();

    auto start_time = std::chrono::high_resolution_clock::now();
    sortBubble(a, size);
    auto finish_time = std::chrono::high_resolution_clock::now();

    QString str;
    for (size_t i = 0; i < size; i++)
        str += QString::number(a[i]) + " \t";
    ui->textEdit_2->setText(str);

    QString time = QString::number(std::chrono::duration_cast<std::chrono::nanoseconds>
                                   (finish_time - start_time).count()) + "ns";
    ui->lineEdit_2->setText(time);
    time = QString::number(std::chrono::duration_cast<std::chrono::milliseconds>
                           (finish_time - start_time).count()) + "ms";
    ui->lineEdit_3->setText(time);
}

template<typename T>
T* copy(T* a, size_t n) {
    T* r = new T[n];
    for (size_t i = 0; i < n; i++)
        r[i] = a[i];
    return r;
}

QtCharts::QLineSeries* generateChart(QStringList s)
{
    QtCharts::QLineSeries *res = new QtCharts::QLineSeries;

    size_t size = s.size();
    float* a = new float[size];
    for (size_t i = 0; i < size; i++)
        a[i] = s[i].toFloat();

    for (size_t i = 2; i < size; i+= size/100) {
        float* t = copy(a, i);

        auto start_time = std::chrono::high_resolution_clock::now();
        sortBubble(t,i);
        auto finish_time = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>
                                           (finish_time - start_time).count();

        res->append(i, time);
    }
    return res;
}

void Widget::chart()
{
    ui->label->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->pushButton->hide();\
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->groupBox->hide();\
    ui->groupBox_2->hide();
    ui->textEdit->hide();
    ui->textEdit_2->hide();

    ch->addSeries(generateChart(ui->textEdit->toPlainText().split(' ')));
    ch->createDefaultAxes();
    ui->horizontalLayout_2->setStretch(3,100);

    chV->show();
    b->show();
}

void Widget::unchart()
{
    ui->label->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();
    ui->pushButton->show();\
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->groupBox->show();\
    ui->groupBox_2->show();
    ui->textEdit->show();
    ui->textEdit_2->show();

    ui->horizontalLayout_2->setStretch(3,0);
    chV->hide();
    b->hide();
}

