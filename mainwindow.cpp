#include "mainwindow.h"
#include "ui_grid.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridsize->setValue(ui->widget->getGap());
    connect(ui->widget, SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    connect(ui->widget, SIGNAL(mousePressed(QPoint&)),this,SLOT(showMousePressed(QPoint&)));
    connect(ui->widget, SIGNAL(showTime(double&)), this, SLOT(showExTime(double&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_show_axes_clicked(){
    ui->widget->show_axes(ui->show_axes->isChecked());
}

void MainWindow::on_show_grid_clicked(){
    ui->widget->show_grid(ui->show_grid->isChecked());
}

void MainWindow::on_Draw_clicked(){
    if(!lastLine.isNull())
    {
        QString a  = ui->widget->getAlgo();
        if(a=="Midpoint_Circle"||a=="Polar_Circle"){
            pair<QPoint,int> p(lastClicked, ui->widget->getRadius());
            ui->widget->addCircle(p);
        }
        else
        {
            ui->widget->addLine(lastLine);
            ui->point1->setText(QString::number(lastLine.p1().x()) +", "+QString::number(lastLine.p1().y()));
            ui->point2->setText(QString::number(lastLine.p2().x()) +", "+QString::number(lastLine.p2().y()));
        }
    }

}

//void MainWindow::on_set_point1_clicked(){
//    lastLine.setP1(lastClicked);
//}

//void MainWindow::on_set_point2_clicked(){
//    lastLine.setP2(lastClicked);
//}

//void MainWindow::on_Draw_clicked(){
//    ui->Draw->setDisabled(true);
//}
void MainWindow::showExTime(double& time){
    ui->ex_time->setText(QString::number(time));
}

void MainWindow::showMousePosition(QPoint& pos){
    ui->mouse_movement->setText(QString::number(pos.x()) +", "+QString::number(pos.y()));
}

void MainWindow::showMousePressed(QPoint& pos){
    ui->mouse_pressed->setText(QString::number(pos.x()) +", "+QString::number(pos.y()));
    lastClicked=pos;
    lastLine.setP1(lastLine.p2());
    lastLine.setP2(lastClicked);
}

void MainWindow::on_gridsize_valueChanged(int gap)
{
    ui->widget->setGap(gap);
}


void MainWindow::on_pushButton_pressed()
{
    ui->widget->clear();
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->widget->setAlgo(arg1);
}


void MainWindow::on_radius_valueChanged(int arg1)
{
    ui->widget->setRadius(arg1);
}


void MainWindow::on_Fill_pressed()
{
    ui->widget->addFill(lastClicked);
}

