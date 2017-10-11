#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <functional>

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

protected slots:
    void draw();
    void sine();
    void func();
};

#endif // WIDGET_H
