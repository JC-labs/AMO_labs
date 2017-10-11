#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSpacerItem>
#include <jacobi.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    t = new FieldTable(0);
    c = new FieldColumn(0);
    si = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->setupUi(this);
    ui->verticalLayout->setStretch(0,1);
    ui->verticalLayout->setStretch(1,1);
    ui->verticalLayout->setStretch(2,1);
    ui->verticalLayout->setStretch(3,1);
    ui->verticalLayout->setStretch(4,1);

    changeTable("3");
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::changeTable);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::solve);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete c;
    delete t;
}

void MainWindow::changeTable(QString s)
{
    ui->horizontalLayout_3->removeItem(t);
    ui->horizontalLayout_3->removeItem(c);
    ui->horizontalLayout_3->removeItem(si);
    delete t;
    delete c;
    t = new FieldTable(s.toInt());
    c = new FieldColumn(s.toInt());
    ui->horizontalLayout_3->addLayout(t);
    ui->horizontalLayout_3->addSpacerItem(si);
    ui->horizontalLayout_3->addLayout(c);
}

void MainWindow::solve()
{
    QString res;
    auto x = Jacobi(t->get(), c->get(), ui->lineEdit_3->text().toFloat());
    for (int i = 0; i < t->get().size1(); i++)
        res += QString::number(x[i]) + ' ';
    ui->lineEdit_2->setText(res);
}
