#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QtConcurrent>
#include <QRandomGenerator>
#include <QScreen>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    Pic=QRandomGenerator().global()->bounded(1,18);
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
    if (ui->radioButton->isChecked())
    {
        curl->start("curl https://v1.hitokoto.cn/?encode=text&c=i\"");
    }
    else
    {
        curl->start("curl https://v1.hitokoto.cn/?encode=text\"");
    }
    curl->waitForFinished();
    //ui->label->setText(curl->readAllStandardOutput().simplified());
    QString YiYan=curl->readAllStandardOutput().simplified();
    return YiYan;
}
void Widget::refresh()
{
    ui->YiYanText->setText("Loading...");
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
    if (Pic<18)
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
    currentWallpaper.load("./backgrounds/"+num+".jpg");
    BgLabel->setScaledContents(true);
    BgLabel->setPixmap(QPixmap().fromImage(currentWallpaper));
    BgLabel->resize(screenRect.width(),screenRect.height());
    //BgLabel->show();
}
void Widget::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R){
        refresh();
    }
    if(event->key() == Qt::Key_Escape){
        this->close();
    }
    if(event->key() == Qt::Key_S){
        ui->refreshBtn->show();
        ui->exitBtn->show();
        ui->radioButton->show();
    }
    if(event->key() == Qt::Key_H){
        ui->refreshBtn->hide();
        ui->exitBtn->hide();
        ui->radioButton->hide();
    }
}
