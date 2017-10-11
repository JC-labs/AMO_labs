#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;

namespace QtCharts {
    class QChart;
    class QChartView;
}

namespace Ui {
class Widget;
}

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
    QPushButton* b;

protected slots:
    void generateRandom();
    void sort();
    void chart();
    void unchart();
};

#endif // WIDGET_H
