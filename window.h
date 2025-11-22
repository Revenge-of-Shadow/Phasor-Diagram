#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QDoubleSpinBox;
QT_END_NAMESPACE
class RenderArea;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
private slots:
    void changed();
private:

    RenderArea *ra;
    QLabel *l_I1;
    QLabel *l_I2;
    QLabel *l_I3;
    QLabel *l_P1;
    QLabel *l_P2;
    QLabel *l_P3;
    QLabel *l_Q1;
    QLabel *l_Q2;
    QLabel *l_Q3;
    QLabel *l_a1;
    QLabel *l_a2;
    QLabel *l_a3;
    QLabel *l_p1;
    QLabel *l_p2;
    QLabel *l_p3;
    QDoubleSpinBox *sb_I1;
    QDoubleSpinBox *sb_I2;
    QDoubleSpinBox *sb_I3;
    QDoubleSpinBox *sb_P1;
    QDoubleSpinBox *sb_P2;
    QDoubleSpinBox *sb_P3;
    QDoubleSpinBox *sb_Q1;
    QDoubleSpinBox *sb_Q2;
    QDoubleSpinBox *sb_Q3;
};
#endif // WINDOW_H

