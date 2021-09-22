#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QtGui>
#include <list>

using namespace std;

class grid : public QWidget
{
    Q_OBJECT
private:
    int m_gap = 10;
    list<QPoint> pointsList;
    list<QLine> lineList;
    bool showGrid = false;
    bool showAxes = false;
    QString algo = "DDA";
    QPoint convertCoordinate(QPoint q) const;
    double ex_time=0;

public:
    explicit grid(QWidget *parent = nullptr);
    ~grid();
    void drawPoint(int x, int y);
    void clear();
    int getGap() const;
    void setGap(int);
    void show_axes(bool);
    void show_grid(bool);
    void addLine(QLine l);
    void setAlgo(const QString &arg1);
    void setTime(double t);
protected:
    void paintEvent(QPaintEvent *) override;
    void setPixel(int x, int y, QPainter& painter);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void bresenham(int x1, int y1, int x2, int y2, QPainter& painter);
    void dda(QLine const& l, QPainter& painter);
signals:
    void sendMousePosition(QPoint&);
    void mousePressed(QPoint&);
    void showTime(double&);
};

#endif // GRID_H