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
        curl->start("curl https://v1.hitokoto.cn/?c=i");
    }
    else
    {
        curl->start("curl https://v1.hitokoto.cn/");
    }
    curl->waitForFinished();
    //ui->label->setText(curl->readAllStandardOutput().simplified());
    QString YiYan=curl->readAllStandardOutput().simplified();
    QStringList list = YiYan.split("\"");
    QString text=list[9];
    QString from;
    QString from_Who;
    if (list[21]=="creator" || list[21]=="网络")
    {
        if (list[17]=="网络" || list[17]=="热评" || list[17]=="原创")
        {
            from=list[17];
        }
        else
        {
            from="《"+list[17]+"》";
        }
        from_Who="";
    }
    else
    {
        from="《"+list[17]+"》";
        from_Who=list[21];
    }
    setAuther(from,from_Who);
    return text;
}
void Widget::refresh()
{
    ui->YiYanText->setText("Loading...");
    ui->InformationLabel->setText("Loading...");
    QtConcurrent::run([=](){
            ui->YiYanText->setText(getTextFromYiYan());
    });
    QFont font("思源黑体",16,75);
    QFont font2("思源黑体",10,63);
    QFont font3("思源黑体",12,50);
    ui->YiYanText->setFont(font);
    ui->refreshBtn->setFont(font2);
    ui->exitBtn->setFont(font2);
    ui->InformationLabel->setFont(font3);
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
void Widget::setAuther(QString from, QString fromWho)
{
    ui->InformationLabel->setText("——"+fromWho+from);
}
