#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startBtn_clicked()
{
    timer.setInterval(10);
    timer.start();
}

void MainWindow::on_stopBtn_clicked()
{
    timer.stop();
}

void MainWindow::timer_timeout() {
    cfd.iterate();
    auto data = cfd.getXYPlaneData();
    auto rgbData = mapCfdDataRGB(data);
    QImage img(cfd.width, cfd.height, QImage::Format_RGB888);
    memcpy(img.bits(), rgbData.data(), std::min((std::size_t)img.sizeInBytes(), (std::size_t)rgbData.size()));
    scene.clear();
    scene.addPixmap(QPixmap::fromImage(img));
}

std::vector<unsigned char> MainWindow::mapCfdDataRGB(const std::vector<CFD::ElemState>& data) {
    std::vector<unsigned char> result;
    result.resize(data.size() * 3);
    /*auto minMax = std::minmax(data.cbegin(), data.cend(), [=](const CFD::ElemState& e1, const CFD::ElemState& e2) {
        return e1.velocity.lengthSqr() < e2.velocity.lengthSqr();
    });*/
    std::pair<CFD::ElemState, CFD::ElemState> minMax;
    for(const auto& elem : data) {
        auto lenSqr = elem.velocity.lengthSqr();
        if(lenSqr < minMax.first.velocity.lengthSqr()) minMax.first = elem;
        if(lenSqr > minMax.second.velocity.lengthSqr()) minMax.second = elem;
    }

    double vMin = minMax.first.velocity.length();
    double vMax = minMax.second.velocity.length();

    for(int i=0;i< data.size(); ++i) {
        double val = data[i].velocity.length();
        val = val / vMax * 255.0;
        if(val < 0.0) val = 0.0;
        unsigned char byteVal = static_cast<unsigned char>(val);
        result[i*3] = byteVal;
        result[i*3+1] = byteVal;
        result[i*3+2] = byteVal;
    }
    return result;
}
