#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QtConcurrent>
#include <QRandomGenerator>
#include <QScreen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    refresh();
}

Widget::~Widget()
{
    delete ui;
}
/*void Widget::paintEvent(QPaintEvent *event)
{
Q_UNUSED(event);

QPainter p(this);
p.drawPixmap(rect(),QPixmap(":/backgrounds/backgrounds/"+num+".jpg"),QRect());
}
*/
QString Widget::getTextFromYiYan()
{
    curl->start("curl https://v1.hitokoto.cn/?encode=text\"");
    curl->waitForFinished();
    //ui->label->setText(curl->readAllStandardOutput().simplified());
    QString YiYan=curl->readAllStandardOutput().simplified();
    return YiYan;
}
void Widget::refresh()
{
    ui->YiYanText->setText("");
    QtConcurrent::run([=](){
            ui->YiYanText->setText(getTextFromYiYan());
    });
    QFont font("思源黑体",16,75);
    QFont font2("思源黑体",10,63);
    ui->YiYanText->setFont(font);
    ui->refreshBtn->setFont(font2);
    ui->exitBtn->setFont(font2);
    DrawBackground();
    //num=1;
    //getTextFromYiYan();
    //num=getRandNum();
    //QWidget::repaint();
}

void Widget::on_refreshBtn_clicked(bool checked)
{
    refresh();
}
QString Widget::getRandNum()
{
    /*int num=QRandomGenerator::global()->bounded(1,4);
    QString numToString=QString::number(num);
    return numToString;*/
    if (Pic<7)
    {
        Pic++;
    }
    else
    {
        Pic=1;
    }
    return QString::number(Pic);
}
void Widget::DrawBackground()
{
    num=getRandNum();
    currentWallpaper.load(":/backgrounds/backgrounds/"+num+".jpg");
    BgLabel->setScaledContents(true);
    BgLabel->setPixmap(QPixmap().fromImage(currentWallpaper));
    BgLabel->resize(screenRect.width(),screenRect.height());
    //BgLabel->show();
}
