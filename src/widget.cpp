#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

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
void Widget::paintEvent(QPaintEvent *event)
{
Q_UNUSED(event);

QPainter p(this);
p.drawPixmap(rect(),QPixmap(":/backgrounds/backgrounds/4.jpg"),QRect());
}
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
    ui->YiYanText->setText(getTextFromYiYan());
    QFont font("思源黑体",16,75);
    QFont font2("思源黑体",10,63);
    ui->YiYanText->setFont(font);
    ui->refreshBtn->setFont(font2);
    ui->exitBtn->setFont(font2);
    //getTextFromYiYan();
}

void Widget::on_refreshBtn_clicked(bool checked)
{
    refresh();
}
