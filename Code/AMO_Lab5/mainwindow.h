#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <fieldtable.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FieldTable *t;
    FieldColumn *c;
    QSpacerItem *si;

protected slots:
    void changeTable(QString s);
    void solve();
};

#endif // MAINWINDOW_H
