#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "equation.hpp"

class Polynom;

namespace Ui {
class Widget;
}

namespace QtCharts {
    class QChart;
    class QChartView;
}

class BadBoundsException {};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QtCharts::QChart* ch;
    QtCharts::QChartView* chV;

    QVector<float> roots;

protected slots:
    void solve();
    void findRoot(Polynom e, float left, float right);
    void draw(Polynom e);
};

#endif // WIDGET_H
