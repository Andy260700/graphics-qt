#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint lastClicked;
    QLine lastLine;
    bool isDrawingPolygon = false;
    list<QPoint> poly;
public slots:
    void showMousePosition(QPoint& pos);
    void showMousePressed(QPoint& pos);
    void showExTime(double& time);
private slots:
    void on_show_axes_clicked();

    void on_show_grid_clicked();

    void on_Draw_clicked();

//    void on_set_point1_clicked();

//    void on_set_point2_clicked();

    void on_gridsize_valueChanged(int arg1);

    void on_pushButton_pressed();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_radius_valueChanged(int arg1);
    void on_Fill_pressed();
    void on_semi_major_valueChanged(int arg1);
    void on_semi_minor_valueChanged(int arg1);
    void on_colors_currentTextChanged(const QString &arg1);
    void on_boundary_fill_pressed();
    void on_polygon_clicked();

    void on_rotate_input_valueChanged(int arg1);
    void on_translate_input_valueChanged(int arg1);
    void on_shear_input_valueChanged(int arg1);
    void on_scale_input_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
