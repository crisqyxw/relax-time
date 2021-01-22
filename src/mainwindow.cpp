#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUI();
    refresh();
}
MainWindow::~MainWindow()
{
    delete ui;

}
QString MainWindow::getTextFromYiYan()
{
    curl->start("curl https://v1.hitokoto.cn/?encode=text\"");
    curl->waitForFinished();
    //ui->label->setText(curl->readAllStandardOutput().simplified());
    QString YiYan=curl->readAllStandardOutput().simplified();
    return YiYan;
}
void MainWindow::refresh()
{
    ui->label->setText(getTextFromYiYan());
    QFont font("思源黑体",16,75);
    QFont font2("思源黑体",10,63);
    ui->label->setFont(font);
    ui->pushButton->setFont(font2);
    ui->pushButton_2->setFont(font2);
    //getTextFromYiYan();
}

void MainWindow::on_pushButton_2_clicked(bool checked)
{
    refresh();
}
void MainWindow::InitUI()
{
    this->setWindowOpacity(0.825);
}
