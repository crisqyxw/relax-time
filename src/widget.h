#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QProcess>
#include <QLabel>
#include <QImage>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void paintEvent(QPaintEvent *event);
    QString getTextFromYiYan();
    void DrawBackground();
    QProcess *curl=new QProcess;
    void refresh();
    void keyPressEvent(QKeyEvent *event);
    int Pic=1;
    QLabel *BgLabel=new QLabel(this);
    QImage currentWallpaper;
    QString getRandNum();
    QString num;
    //QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect = QApplication::desktop()->screenGeometry();

private slots:
    void on_refreshBtn_clicked(bool checked);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
