#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QtGui>
#include <list>
#include<unordered_map>
#include "qpointhasher.h"

using namespace std;

class grid : public QWidget
{
    Q_OBJECT
private:
    int m_gap = 10;
//    list<QPoint> pointsList;
    unordered_map<QPoint, QColor, QPointHasher> pointsList;
    list<QLine> lineList;
    list<QPoint> flood_fill;
    list<pair<QPoint,int>> circleList;
    list<pair<QPoint, pair<int,int>>> ellipseList;
    bool showGrid = false;
    bool showAxes = false;
    int radius = 0;
    int s_major=0;
    int s_minor=0;
    QString algo;
    QString fill_color;
    QColor old_color = QColor(Qt::black);
    QPoint convertCoordinate(QPoint q) const;
    double ex_time=0;

public:
    explicit grid(QWidget *parent = nullptr);
    ~grid();
    void drawPoint(int x, int y, QColor color = QColor(Qt::yellow));
    void clear();
    int getGap() const;
    int getRadius() const;
    int getSminor() const;
    int getSmajor() const;
    void setGap(int);
    void show_axes(bool);
    void show_grid(bool);
    void addLine(QLine l);
    void addCircle(pair<QPoint,int>);
    void addEllipse(pair<QPoint, pair<int,int>>);
    void setAlgo(const QString &arg1);
    void setFill(const QString &arg1);
    void setTime(double t);
    void setRadius(int);
    void setSmajor(int);
    void setSminor(int);
    QString getAlgo();
    QString getFill();
    void addFill(QPoint p);
    void bresenham(int x1, int y1, int x2, int y2 );
    void dda(QLine const& l );
    void midpoint_circle(QPoint const& centre, int rad );
    void polar_circle(QPoint const& centre, int rad );
    void polar_ellipse(QPoint const& centre, int a, int b );
    void midpoint_ellipse(QPoint const& centre, int a, int b);
    void floodfill(int x,int y,  QColor color);
    void boundary_fill(int x,int y,  QColor color, QColor stop=QColor(Qt::yellow));
protected:
    void paintEvent(QPaintEvent *) override;
    void setPixel(int x, int y, QPainter& painter ,QBrush brush=QBrush(Qt::yellow));
    QColor getPixel(int x, int y);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void midpoint_time(int rad);
    void polar_time(int rad);
    void polar_ellipse_time(int a, int b);
    void draw_8_points(int xc, int yc, int x,int y );
    void draw_4_points(int xc, int yc, int x,int y );
signals:
    void sendMousePosition(QPoint&);
    void mousePressed(QPoint&);
    void showTime(double&);
};

#endif // GRID_H
