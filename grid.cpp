#include "grid.h"
#include <iostream>
#include<time.h>
#include<queue>

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
      QBrush brush = QBrush(p.second);
      setPixel(p.first.x(), p.first.y(), painter, brush);
    }

//    for(auto const& l : lineList){
//        if(algo=="DDA_Line")
//            dda(l, painter);
//        else
//            bresenham(l.p1().x(), l.p1().y(), l.p2().x(), l.p2().y(),painter);
//    }

//    for(auto const& c : circleList){
//        if(algo=="Polar_Circle")
//            polar_circle(c.first,c.second,painter);
//        else
//            midpoint_circle(c.first,c.second,painter);
//    }
//    for(auto const& e : ellipseList){
//        polar_ellipse(e.first, e.second.first, e.second.second, painter);
//    }
//    for(auto const& p:flood_fill){
//        floodfill(p.x(),p.y(),painter);
//    }
}

grid::~grid() {}

int grid::getGap() const
{
    return m_gap;
}
QString grid::getAlgo()
{
    return algo;
}
QString grid::getFill()
{
    return fill_color;
}
void grid::setFill(const QString &arg1)
{
    fill_color=arg1;
}
int grid::getRadius() const
{
    return radius;
}
int grid::getSmajor() const
{
    return s_major;
}
int grid::getSminor() const
{
    return s_minor;
}
void grid::setGap(int gap)
{
    m_gap = gap;
    update();
}
void grid::setRadius(int rad)
{
    radius = rad;
}
void grid::setSmajor(int major)
{
    s_major = major;
}
void grid::setSminor(int minor)
{
    s_minor = minor;
}
void grid::setAlgo(const QString &arg1){
    algo = arg1;
}
void delay(int msecs)
{
    QTime dieTime = QTime::currentTime().addMSecs(msecs);
    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void grid::setPixel(int x, int y, QPainter& painter, QBrush brush)
{
    int x1 = (int(width()/(m_gap*2))*m_gap  + x * m_gap);
    int y1 = (-y * m_gap + int(height()/(m_gap*2))*m_gap);
    painter.fillRect(x1, y1, m_gap, m_gap, brush);
}

QColor grid::getPixel(int x, int y)
{
    int x1 = (int(width()/(m_gap*2))*m_gap  + x * m_gap);
    int y1 = (-y * m_gap + int(height()/(m_gap*2))*m_gap);
    QPixmap pix = grab(QRect(x1, y1, m_gap, m_gap));
    QImage img(pix.toImage());
    QColor color(img.pixel(x1,y1));
    return color;
}

void grid::drawPoint(int x, int y, QColor color)
{
    pointsList[QPoint(x, y)] = color;
    update();
}
void grid::clear()
{
    pointsList.clear();
    lineList.clear();
    circleList.clear();
    ellipseList.clear();
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
void grid:: addCircle(pair<QPoint,int> circle){
    circleList.push_back(circle);
    update();
}
void grid:: addFill(QPoint point){
    flood_fill.push_back(point);
    update();
}
void grid:: addEllipse(pair<QPoint, pair<int,int>> ellipse){
    ellipseList.push_back(ellipse);
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
void grid:: draw_4_points(int xc, int yc, int x,int y ){
//        setPixel(xc+x, yc+y, painter, QBrush(Qt::red));
//        setPixel(xc-x, yc+y, painter, QBrush(Qt::yellow));
//        setPixel(xc+x, yc-y, painter, QBrush(Qt::blue));
//        setPixel(xc-x, yc-y, painter, QBrush(Qt::magenta));
    pointsList[QPoint(xc+x, yc+y)] = QColor(Qt::red);
    pointsList[QPoint(xc-x, yc+y)] = QColor(Qt::yellow);
    pointsList[QPoint(xc+x, yc-y)] = QColor(Qt::blue);
    pointsList[QPoint(xc-x, yc-y)] = QColor(Qt::magenta);
//        if(x != y)
//        {

//            setPixel(xc+y, yc+x, painter, QBrush(Qt::cyan));

//            setPixel(xc-y, yc+x, painter, QBrush(Qt::lightGray));

//            setPixel(xc+y, yc-x, painter, QBrush(Qt::green));

//            setPixel(xc-y, yc-x, painter, QBrush(Qt::darkBlue));
//        }
}

void grid:: draw_8_points(int xc, int yc, int x,int y ){
//        setPixel(xc+x, yc+y, painter, QBrush(Qt::red));
//        setPixel(xc-x, yc+y, painter, QBrush(Qt::yellow));
//        setPixel(xc+x, yc-y, painter, QBrush(Qt::blue));
//        setPixel(xc-x, yc-y, painter, QBrush(Qt::magenta));
    pointsList[QPoint(xc+x, yc+y)] = QColor(Qt::red);
    pointsList[QPoint(xc-x, yc+y)] = QColor(Qt::yellow);
    pointsList[QPoint(xc+x, yc-y)] = QColor(Qt::blue);
    pointsList[QPoint(xc-x, yc-y)] = QColor(Qt::magenta);
        if(x != y)
        {

//            setPixel(xc+y, yc+x, painter, QBrush(Qt::cyan));
//            setPixel(xc-y, yc+x, painter, QBrush(Qt::lightGray));
//            setPixel(xc+y, yc-x, painter, QBrush(Qt::green));
//            setPixel(xc-y, yc-x, painter, QBrush(Qt::darkBlue));
            pointsList[QPoint(xc+y, yc+x)] = QColor(Qt::cyan);
            pointsList[QPoint(xc-y, yc+x)] = QColor(Qt::lightGray);
            pointsList[QPoint(xc+y, yc-x)] = QColor(Qt::green);
            pointsList[QPoint(xc-y, yc-x)] = QColor(Qt::darkBlue);
        }
}
void grid:: midpoint_time(int radius){
    QElapsedTimer clock = QElapsedTimer();
    clock.start();
    qint64 start = clock.nsecsElapsed();
    int x = radius, y = 0;
    int P = 1 - radius;
    while (x > y)
    {
        y++;

        if (P <= 0)
            P = P + 2*y + 1;

        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }

        if (x < y)
            break;
    }

    setTime(double(clock.nsecsElapsed()-start));
    clock.invalidate();
}
void grid:: midpoint_circle(QPoint const& c, int radius ){
    midpoint_time(radius);
                int x_center = c.x();
                int y_center = c.y();

                int x = radius, y = 0;


                if (radius > 0)
                {
                   draw_8_points(x_center, y_center, x,y);
                }

                int P = 1 - radius;
                while (x > y)
                {

                    y++;

                    if (P <= 0)
                        P = P + 2*y + 1;

                    else
                    {
                        x--;
                        P = P + 2*y - 2*x + 1;
                    }

                    if (x < y)
                        break;

                    draw_8_points(x_center, y_center, x, y);
                    update();
                    delay(100);
                }
                update();
}
void grid:: polar_time(int radius){
    QElapsedTimer clock = QElapsedTimer();
    clock.start();
    qint64 start = clock.nsecsElapsed();

    int x = 0;
    int y = 0;
    double angle = 0;
    if(radius == 0) {
        return;
    }
    const double angular_increment = 1.0 / radius;
    while(x >= y) {
        int x_new = round(radius * cos(angle));
        int y_new = round(radius * sin(angle));
//        if(x != x_new || y!= y_new)
//        {
//        }
        x = x_new;
        y = y_new;
        angle += angular_increment;

    }
    setTime(double(clock.nsecsElapsed()-start));
    clock.invalidate();
}
void grid:: polar_circle(QPoint const& c, int radius ){
    polar_time(radius);
        int x = 0;
        int y = 0;
        double angle = 0;
        if(radius == 0) {
            return;
        }
        const double angular_increment = 1.0 / radius;
        while(x >= y) {
            int x_new = round(radius * cos(angle));
            int y_new = round(radius * sin(angle));
            if(x != x_new || y!= y_new)
            {
                draw_8_points(c.x(), c.y(), x, y);
                update();
                delay(100);
            }

            x = x_new;
            y = y_new;
            angle += angular_increment;

        }
        update();
}
void grid:: bresenham(int x1, int y1, int x2, int y2 )
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
//                    setPixel(x, y, painter);
                    pointsList[QPoint(x,y)]=QColor(Qt::yellow);
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
//                    setPixel(x, y, painter);
                    pointsList[QPoint(x,y)]=QColor(Qt::yellow);
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
      update();
}
void grid::setTime(double t){
    ex_time = t;
    emit showTime(t);
}
void grid::dda(QLine const& l )
{
    QElapsedTimer clock = QElapsedTimer();
    clock.start();
    qint64 start = clock.nsecsElapsed();
    int dx = l.p2().x() - l.p1().x();
    int dy = l.p2().y() - l.p1().y();

    int steps = max(abs(dx), abs(dy));

    double xinc = dx / (double) steps;
    double yinc = dy / (double) steps;


    double x = l.p1().x();
    double y = l.p1().y();
    for (int i = 0; i <= steps; i++)
    {
//        setPixel(round(x),round(y), painter);
        pointsList[QPoint(round(x),round(y))]=QColor(Qt::yellow);
        x += xinc;
        y += yinc;
    }
//   time(&end);
     setTime(double((clock.nsecsElapsed()-start)*1.1));
     clock.invalidate();
     update();
}

void grid::polar_ellipse(QPoint const& c, int a, int b ){
 polar_time(a);
    int x = 0;
    int y = 0;
    double angle = 0;
    if(a == 0 || b==0) {
        return;
    }
    const double angular_increment = 1.0 / max(a,b);
    while(x>=0) {
        int x_new = round(a * cos(angle));
        int y_new = round(b * sin(angle));
        if(x != x_new || y!= y_new)
        {
            draw_4_points(c.x(), c.y(), x, y);
            update();
            delay(100);
        }

        x = x_new;
        y = y_new;
        angle += angular_increment;
    }
    update();
}
void grid:: midpoint_ellipse(QPoint const& c, int a, int b){
    double dx, dy, d1, d2, x, y;
        x = 0;
        y = b;

        // Initial decision parameter of region 1
        d1 = (b * b) - (a * a * b) +
                (0.25 * a * a);
        dx = 2 * b * b * x;
        dy = 2 * a * a * y;

        // For region 1
        while (x < y)
        {

            // Print points based on 4-way symmetry
           draw_4_points(c.x(), c.y(), x, y);
           update();
           delay(100);

            // Checking and updating value of
            // decision parameter based on algorithm
            if (d1 < 0)
            {
                x++;
                dx = dx + (2 * b * b);
                d1 = d1 + dx + (b * b);
            }
            else
            {
                x++;
                y--;
                dx = dx + (2 * b * b);
                dy = dy - (2 * a * a);
                d1 = d1 + dx - dy + (b * b);
            }
        }

        // Decision parameter of region 2
        d2 = ((b * b) * ((x + 0.5) * (x + 0.5))) +
                ((a * a) * ((y - 1) * (y - 1))) -
                (a * a * b * b);


        while (y >= 0)
        {

            draw_4_points(c.x(), c.y(), x, y);
            update();
            delay(100);
            // Checking and updating parameter
            // value based on algorithm
            if (d2 > 0)
            {
                y--;
                dy = dy - (2 * a * a);
                d2 = d2 + (a * a) - dy;
            }
            else
            {
                y--;
                x++;
                dx = dx + (2 * b * b);
                dy = dy - (2 * a * a);
                d2 = d2 + dx - dy + (a * a);
            }
        }
        update();
}
void grid::floodfill(int x,int y, QColor color){
    if(color==old_color)
        return;
    queue<pair<int,int>> q;
    q.push(pair<int,int>(x,y));
//    setPixel(x,y, QBrush(Qt::white));
    pointsList[QPoint(x,y)] = color;
    int _x[4]={0,0,1,-1};
    int _y[4]={1,-1,0,0};
    int w = int(width()/m_gap)/2;
    int h = int(height()/m_gap)/2;
    while(!q.empty()){
        pair<int,int> p = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int a = p.first+_x[i];
            int b = p.second+_y[i];
            if(a>=-w && b>=-h && a<=w && b<=h && (pointsList.find(QPoint(a,b))==pointsList.end() || pointsList[QPoint(a,b)]==old_color)){
                q.push(pair<int,int>(a,b));
//                setPixel(a,b,QBrush(Qt::white));
                pointsList[QPoint(a,b)] = color;
                update();
                delay(10);
            }
        }
    }
    update();
}
void grid:: boundary_fill(int x,int y,  QColor color,  QColor stop){
    if(color==old_color)
        return;
    queue<pair<int,int>> q;
    q.push(pair<int,int>(x,y));
//    setPixel(x,y, QBrush(Qt::white));
    pointsList[QPoint(x,y)] = color;
    int _x[4]={0,0,1,-1};
    int _y[4]={1,-1,0,0};
    int w = int(width()/m_gap)/2;
    int h = int(height()/m_gap)/2;
    while(!q.empty()){
        pair<int,int> p = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int a = p.first+_x[i];
            int b = p.second+_y[i];
            if(a>=-w && b>=-h && a<=w && b<=h && (pointsList.find(QPoint(a,b))==pointsList.end() || (pointsList[QPoint(a,b)]!=color && pointsList[QPoint(a,b)]!=stop))){
                q.push(pair<int,int>(a,b));
//                setPixel(a,b,QBrush(Qt::white));
                pointsList[QPoint(a,b)] = color;
                update();
                delay(10);
            }
        }
    }
    update();
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
            if(pointsList.find(QPoint(mp.x(),mp.y()))!=pointsList.end())
                old_color=pointsList[QPoint(mp.x(),mp.y())];
            drawPoint(mp.x(),mp.y());
            emit mousePressed(mp);
        }
    }
}
