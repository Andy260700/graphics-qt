#include "grid.h"
#include <iostream>
#include<time.h>

grid::grid(QWidget *parent) : QWidget(parent)
{
//    resize(490, 490);
//    pointsList.push_back(QPoint(5,5));
//    std::cout << width() << std::endl;
    setMouseTracking(true);
}

void grid::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    if(showAxes)
    {
        QPen axesPen(Qt::white , m_gap);
        painter.setPen(axesPen);
        painter.drawLine(0, int(height()/(m_gap*2))*m_gap + m_gap/2, width(), int(height()/(m_gap*2))*m_gap+m_gap/2);
        painter.drawLine(int(width()/(m_gap*2))*m_gap + m_gap/2, 0 , int(width()/(m_gap*2))*m_gap + m_gap/2, height());
    }
    if(showGrid)
    {
        QPen gridpen(Qt::darkGray);
        painter.setPen(gridpen);
        for(int i = 0; i < height(); i += m_gap)
        {
            painter.drawLine(0, i, width(), i);
        }

        for(int i = 0; i < width(); i += m_gap) {
            painter.drawLine(i,0,i, height());
        }
    }

    for(auto const& p: pointsList)
    {
      setPixel(p.x(), p.y(), painter);
    }

    for(auto const& l : lineList){
        if(algo=="DDA")
            dda(l, painter);
        else
            bresenham(l.p1().x(), l.p1().y(), l.p2().x(), l.p2().y(),painter);
    }

}

grid::~grid() {}

int grid::getGap() const
{
    return m_gap;
}
void grid::setGap(int gap)
{
    m_gap = gap;
    update();
}
void grid::setAlgo(const QString &arg1){
    algo = arg1;
}
void grid::setPixel(int x, int y, QPainter& painter)
{
    QBrush brush(Qt::yellow);
    int x1 = (int(width()/(m_gap*2))*m_gap  + x * m_gap);
    int y1 = (-y * m_gap + int(height()/(m_gap*2))*m_gap);
    painter.fillRect(x1, y1, m_gap, m_gap, brush);
}

void grid::drawPoint(int x, int y)
{
    pointsList.push_back(QPoint(x, y));
    update();
}
void grid::clear()
{
    pointsList.clear();
    lineList.clear();
    update();
}

void grid::show_axes(bool cond)
{
    showAxes = cond;
    update();
}
void grid::show_grid(bool cond)
{
    showGrid = cond;
    update();
}
QPoint grid::convertCoordinate(QPoint q) const{
    int x = int(q.x())/m_gap - (width()/m_gap)/2;
    int y = -int(q.y())/m_gap + (height()/m_gap)/2;
    return QPoint(x,y);
}
void grid:: addLine(QLine line){
    lineList.push_back(line);
    update();
}
void grid::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint mouse_pos=ev->pos();
    if(mouse_pos.x()<=this->size().width() && mouse_pos.y()<=this->size().height()){
        if(mouse_pos.x()>0 && mouse_pos.y()>0){
            QPoint mp = convertCoordinate(mouse_pos);
            emit sendMousePosition(mp);
        }
    }
}

void grid:: bresenham(int x1, int y1, int x2, int y2, QPainter& painter)
{
//    time_t start,end;
//    time(&start);
    QElapsedTimer clock = QElapsedTimer();
    clock.start();
    qint64 start = clock.nsecsElapsed();
            int dx=x2-x1;
            int dy=y2-y1;

            int xinc=(dx>0)?1:-1;
            int yinc=(dy>0)?1:-1;

            dx=abs(dx);
            dy=abs(dy);

            if(dx>dy)
            {
                int p=2*(dy)-dx;
                int y=y1;

                for(int x=x1; x!=x2; x+=xinc)
                {
                    setPixel(x, y, painter);
                    if(p>=0)
                    {
                        y+=yinc;
                        p-=2*dx;
                    }
                    p+=2*dy;
                }
            }
            else
            {
                int p=2*(dx)-dy;
                int x=x1;

                for(int y=y1; y!=y2; y+=yinc)
                {
                    setPixel(x, y, painter);
                    if(p>=0)
                    {
                        x+=xinc;
                        p-=2*(dy);
                    }
                    p+=2*(dx);
                }
            }
//      time(&end);
      setTime(double(clock.nsecsElapsed()-start));
      clock.invalidate();
}
void grid::setTime(double t){
    ex_time = t;
    emit showTime(t);
}
void grid::dda(QLine const& l, QPainter& painter)
{
    QElapsedTimer clock = QElapsedTimer();
    clock.start();
    qint64 start = clock.nsecsElapsed();
    double t = 0;
    int dx = l.p2().x() - l.p1().x();
    int dy = l.p2().y() - l.p1().y();

    int steps = max(abs(dx), abs(dy));

    double xinc = dx / (double) steps;
    double yinc = dy / (double) steps;


    double x = l.p1().x();
    double y = l.p1().y();
    for (int i = 0; i <= steps; i++)
    {
        setPixel(round(x),round(y), painter);
        x += xinc;
        y += yinc;
        t+=5;
    }
//   time(&end);
     setTime(double((clock.nsecsElapsed()-start)*1.4));
     clock.invalidate();
}

void grid::mousePressEvent(QMouseEvent *ev)
{
//    if(ev->button()==Qt::LeftButton){
//        this->x=ev->position().x();
//        this->y=ev->position().y();
//        emit sendMousePosition(mouse_pos);
//    }
    QPoint mouse_pos=ev->pos();
    if(mouse_pos.x()<=this->size().width() && mouse_pos.y()<=this->size().height()){
        if(mouse_pos.x()>0 && mouse_pos.y()>0){
            QPoint mp = convertCoordinate(mouse_pos);
            drawPoint(mp.x(),mp.y());
            emit mousePressed(mp);
        }
    }
}
