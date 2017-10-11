#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    float* toArray(QString s);

private:
    Ui::Widget *ui;

protected slots:
    void rb1();
    void rb2();
    void rb3();

    void calc();
};

#endif // WIDGET_H
