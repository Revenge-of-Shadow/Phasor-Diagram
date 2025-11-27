#include "renderarea.h"

#include <QPainter>
#include <QPainterPath>
#include <QPainterStateGuard>

const double pi = std::acos(-1);

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(false);
    set(0.f,0.f,0.f,0.f,0.f,0.f);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(800, 600);
}

void RenderArea::set(double I1, double I2, double I3, double a1, double a2, double a3)
{
    I[0] = I1; I[1] = I2; I[2] = I3;
    a[0] = a1; a[1] = a2; a[2] = a3;
}

void makeArrow(double angle, double r, QPainter& painter){
    double offset = angle > 0? 0.125 : -0.125;
    painter.drawLine(QPoint(0,0),
                     -QPoint(std::cos(angle-offset)*r, std::sin(angle-offset)*r));
    painter.drawLine(QPoint(0,0),
                     -QPoint(std::cos(angle+offset)*r, std::sin(angle+offset)*r));

}
void RenderArea::paintEvent(QPaintEvent *event)
{
    Qt::GlobalColor colors[6] = {Qt::GlobalColor::red, Qt::GlobalColor::green, Qt::GlobalColor::blue, Qt::GlobalColor::magenta, Qt::GlobalColor::white, Qt::GlobalColor::black};

    QBrush brush(colors[4], Qt::BrushStyle::SolidPattern);
    QRect canvas(10, 20, width()-10, height()-40);

    QPainter painter(this);
    QFont font = painter.font();
    font.setPointSize(font.pointSize()*2);
    QPoint textOffset(font.pointSize()/1.5, -font.pointSize()/2.f);
    painter.setFont(font);
    painter.setPen(palette().dark().color());
    painter.setBrush(brush);
    painter.drawRect(QRect(0,0, width()-1, height()-1));

    brush.setColor(colors[5]);
    painter.setPen(QPen(brush, 2));

    for(int i = 0; i<3; ++i)
        if(I[i] == 0) return;
    //  Loop start


    double r = std::min(width(), height())/4.f;
    double angle_step = pi*2.f/3.f;
    double angle = pi/2.f;

    QPoint points[3];
    for(int i = 0; i<3; ++i){
        points[i] = -QPoint(std::cos(angle)*r, std::sin(angle)*r);
        angle += angle_step;
    }

    //	Drawing.
    QLine phasor(QPoint(0,0),QPoint(0,0));
    painter.translate(canvas.center());

    //	Triangle part.
    for(int i = 0; i < 3; ++i)
        painter.drawLine(points[i], points[(i+1)%3]);

    //	Phase vector.
    for(int i = 0; i < 3; ++i){
        QPainterStateGuard guard(&painter);

        brush.setColor(colors[i]);
        painter.setPen(QPen(brush, 2));
        phasor.setP2(points[i]);
        painter.drawLine(phasor);
        // Arrowhead
        painter.translate(phasor.p2());
        makeArrow(-pi/2.f+angle_step*i, r/8.f, painter);

        QString str("U");
        str.append(char('1'+i));
        str.append(char('N'));
        QPoint currentOffset(textOffset.x()*float(str.length()/2+1), textOffset.y());
        painter.drawText(phasor.p2()/8.f-currentOffset, str);
    }

    //	Between-phase vector.
    for(int i = 0; i < 3; ++i){
        QPainterStateGuard guard(&painter);

        brush.setColor(colors[i]);
        painter.setPen(QPen(brush, 2));
        phasor.setP2(points[(i+1)%3]-points[(i+2)%3]);
        painter.drawLine(phasor);
        // Arrowhead
        painter.translate(phasor.p2());
        makeArrow(angle_step*i, r/8.f, painter);

        QString str("U");
        str.append(char('1'+(i+1)%3));
        str.append(char('1'+(i+2)%3));
        QPoint currentOffset(textOffset.x()*2, textOffset.y());
        painter.drawText(phasor.p2()/8.f-currentOffset, str);

    }
    double Imax = I[0];
    for(int i = 1; i < 3; ++i)
        Imax = Imax < I[i] ? I[i] : Imax;
    QLine In(QPoint(0,0), QPoint(0,0));

    brush.setColor(colors[3]);
    painter.setPen(QPen(brush, 3));
    for(int i = 0; i < 3; ++i){
        QPainterStateGuard guard(&painter);

        double angle_offset = a[i];
        angle = pi/2.f+angle_step*i - angle_offset;
        phasor.setP2(QPoint(std::cos(angle)*(I[i]/Imax*r), std::sin(angle)*(I[i]/Imax*r)));
        painter.drawLine(phasor);
        // Arrowhead
        painter.translate(phasor.p2());
        makeArrow(angle, r/8.f, painter);

        QString str("I");
        str.append(char('1'+i));
        QPoint currentOffset(textOffset.x(), textOffset.y());
        painter.drawText(phasor.p2()/8.f-currentOffset, str);

        In.setP2(In.p2()+phasor.p2());
    }

    phasor.setP2(In.p2());
    //	Nil phasors cause severe glitch: a vector that starts code-knows-where.
    if(phasor.toLineF().length() != 0){
        painter.drawLine(phasor);
        // Arrowhead
        painter.translate(phasor.p2());
        angle = std::atan(phasor.p2().y()/double(phasor.p2().x()));
        makeArrow(phasor.p2().x() < 0? angle+pi : angle, r/8.f, painter);
    }
    QString str("IN");
    QPoint currentOffset(textOffset.x()*2, textOffset.y());
    painter.drawText(phasor.p2()/8.f-currentOffset, str);

}
