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
//        if(a=="Midpoint_Circle"||a=="Polar_Circle"){
//            pair<QPoint,int> p(lastClicked, ui->widget->getRadius());
//            ui->widget->addCircle(p);
//        }
//        else if(a=="Polar_Ellipse"){
//            pair<QPoint, pair<int,int>> p(lastClicked, pair<int,int>(ui->widget->getSmajor(), ui->widget->getSminor()));
//            ui->widget->addEllipse(p);
//        }
//        else
//        {
//            ui->widget->addLine(lastLine);
//            ui->point1->setText(QString::number(lastLine.p1().x()) +", "+QString::number(lastLine.p1().y()));
//            ui->point2->setText(QString::number(lastLine.p2().x()) +", "+QString::number(lastLine.p2().y()));
//        }
        if(a=="Midpoint_Circle"){
            ui->widget->midpoint_circle(lastClicked, ui->widget->getRadius());
        }
        else if(a=="Polar_Circle"){
            ui->widget->polar_circle(lastClicked, ui->widget->getRadius());
        }
        else if(a=="Polar_Ellipse"){
            ui->widget->polar_ellipse(lastClicked, ui->widget->getSmajor(), ui->widget->getSminor());
        }
        else if(a=="Midpoint_Ellipse"){
            ui->widget-> midpoint_ellipse(lastClicked, ui->widget->getSmajor(), ui->widget->getSminor());
        }
        else if(a=="DDA_Line"){
            ui->widget->dda(lastLine);
        }
        else{
            ui->widget->bresenham(lastLine.p1().x(), lastLine.p1().y(), lastLine.p2().x(), lastLine.p2().y());
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
    if(isDrawingPolygon)
        {
            if(!poly.empty())
            {
                ui->widget->dda(QLine(pos, poly.front()));
            }
            poly.push_front(pos);
        }
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
    QString col = ui->widget->getFill();
    QColor color = QColor(col);
    ui->widget->floodfill(lastClicked.x(), lastClicked.y(), color);
}


void MainWindow::on_semi_major_valueChanged(int arg1)
{
    ui->widget->setSmajor(arg1);
}


void MainWindow::on_semi_minor_valueChanged(int arg1)
{
    ui->widget->setSminor(arg1);
}


void MainWindow::on_colors_currentTextChanged(const QString &arg1)
{
    ui->widget->setFill(arg1);
}


void MainWindow::on_boundary_fill_pressed()
{
    QString col = ui->widget->getFill();
    QColor color = QColor(col);
    ui->widget->boundary_fill(lastClicked.x(), lastClicked.y(), color);
}


void MainWindow::on_polygon_clicked()
{
    if(!isDrawingPolygon) {
            ui->polygon->setText("End Polygon");
            isDrawingPolygon = true;
        } else {
//        cout<<poly.size()<<" "<<poly.front().x()<<" "<<poly.back().y()<<'\n';
            ui->widget->dda(QLine(poly.back(), poly.front()));
            ui->widget->addPolygon(poly);
            isDrawingPolygon = false;
            ui->polygon->setText("Start Polygon");
            poly.clear();
            ui->widget->scanline(ui->widget->getFill());
        }
}





void MainWindow::on_rotate_input_valueChanged(int arg1)
{
    ui->widget->rotate_transform(arg1);
}


void MainWindow::on_translate_input_valueChanged(int arg1)
{
   ui->widget->translate_transform(arg1,arg1);
}


void MainWindow::on_shear_input_valueChanged(int arg1)
{
    ui->widget->shear_transform(arg1,arg1);
}


void MainWindow::on_scale_input_valueChanged(int arg1)
{
    ui->widget->scale_transform(arg1,arg1);
}

