#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include "cfd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static std::vector<unsigned char> mapCfdDataRGB(const std::vector<CFD::ElemState>& data);

private slots:
    void on_startBtn_clicked();

    void on_stopBtn_clicked();
    void timer_timeout();

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;
    CFD cfd;
    QTimer timer;
};
#endif // MAINWINDOW_H
