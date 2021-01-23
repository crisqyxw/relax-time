#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    QString getTextFromYiYan();
    QProcess *curl=new QProcess;
    void refresh();
    QPixmap currentWallpaper;

private slots:
    void on_refreshBtn_clicked(bool checked);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
