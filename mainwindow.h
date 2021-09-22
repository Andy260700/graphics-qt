#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};
#endif // MAINWINDOW_H
