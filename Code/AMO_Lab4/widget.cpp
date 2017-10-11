#include "Widget.h"
#include "ui_Widget.h"
#include <QtCharts>
#include <QVector>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    ch = new QtCharts::QChart();
    ch->legend()->hide();

    chV = new QtCharts::QChartView(ch);
    chV->setRenderHint(QPainter::Antialiasing);

    ui->horizontalLayout->addWidget(chV);
    ui->verticalLayout->setStretch(0,1);
    ui->verticalLayout->setStretch(1,100);
    ui->verticalLayout->setStretch(2,1);

    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::solve);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::solve()
{
    Polynom e(ui->lineEdit_3->text());
    roots.clear();

    float left = -25.f;
    float right = -left;
    float step = (right - left) / 10000.f;

    float y_limit = 0.15f;
    QVector<float> limits;
    bool flag = fabs(e(left)) <= y_limit;
    for (float f = left; f <= right; f += step)
        if (flag != (fabs(e(f)) <= y_limit)) {
            flag = !flag;
            limits.push_back(f);
        }

    for (int i = 0; i < limits.size(); i+=2)
        findRoot(e, limits[i], limits[i+1]);

    draw(e);

    QString res = "";
    for (auto it : roots)
        res += QString::number(it) + ' ';
    ui->lineEdit_4->setText(res);
}

void Widget::findRoot(Polynom e, float left, float right) {
    float dx = left, x;
    float rb = e(right);
    float acc = ui->lineEdit_2->text().toFloat();
    do {
        x = dx;
        dx = x - e(x) * (right - x) / (rb - e(x));
    } while (fabs(x-dx) > acc);
    roots.push_back(dx);
}

void Widget::draw(Polynom e)
{
    QtCharts::QLineSeries* equation = new QtCharts::QLineSeries;
    QtCharts::QLineSeries* axis = new QtCharts::QLineSeries;
    QtCharts::QLineSeries** rt = new QtCharts::QLineSeries*[roots.size()];

    float left = -1000.f;
    float right = -left;

    float amp = ui->lineEdit->text().toFloat();
    for (float f = left; f <= right; f += 0.005f) {
        float r = e(f);
        if (fabs(r) <= amp) {
            equation->append(f, e(f));
            axis->append(f, 0);
        }
    }
    for (int i = 0; i < roots.size(); i++) {
        rt[i] = new QtCharts::QLineSeries;
        rt[i]->append(roots[i],-amp);
        rt[i]->append(roots[i],+amp);
    }

    ch->removeAllSeries();
    ch->addSeries(equation);
    ch->addSeries(axis);
    for (int i = 0; i < roots.size(); i++) {
        ch->addSeries(rt[i]);
    }
    ch->createDefaultAxes();
}
