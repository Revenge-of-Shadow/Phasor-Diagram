#include "window.h"
#include "renderarea.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>

const int IdRole = Qt::UserRole;
Window::Window(){
    this->setStyleSheet("background-color: white; color: black;");

    ra = new RenderArea;
    l_I1 = new QLabel(tr("I1 [A]:"));
    l_I2 = new QLabel(tr("I2 [A]:"));
    l_I3 = new QLabel(tr("I3 [A]:"));
    l_P1 = new QLabel(tr("P1 [W]:"));
    l_P2 = new QLabel(tr("P2 [W]:"));
    l_P3 = new QLabel(tr("P3 [W]:"));
    l_Q1 = new QLabel(tr("Q1 [var]:"));
    l_Q2 = new QLabel(tr("Q2 [var]:"));
    l_Q3 = new QLabel(tr("Q3 [var]:"));
    l_a1 = new QLabel(tr("φ1 [rad]:"));
    l_a2 = new QLabel(tr("φ2 [rad]:"));
    l_a3 = new QLabel(tr("φ3 [rad]:"));
    l_p1 = new QLabel(tr(""));
    l_p2 = new QLabel(tr(""));
    l_p3 = new QLabel(tr(""));
    sb_I1 = new QDoubleSpinBox();
    sb_I2 = new QDoubleSpinBox();
    sb_I3 = new QDoubleSpinBox();
    sb_P1 = new QDoubleSpinBox();
    sb_P2 = new QDoubleSpinBox();
    sb_P3 = new QDoubleSpinBox();
    sb_Q1 = new QDoubleSpinBox();
    sb_Q2 = new QDoubleSpinBox();
    sb_Q3 = new QDoubleSpinBox();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(ra, 0,0,1,6);

    mainLayout->addWidget(l_I1, 2,0,Qt::AlignRight);
    mainLayout->addWidget(sb_I1, 2,1);
    mainLayout->addWidget(l_I2, 2,2,Qt::AlignRight);
    mainLayout->addWidget(sb_I2, 2,3);
    mainLayout->addWidget(l_I3, 2,4,Qt::AlignRight);
    mainLayout->addWidget(sb_I3, 2,5);
    mainLayout->addWidget(l_P1, 3,0,Qt::AlignRight);
    mainLayout->addWidget(sb_P1, 3,1);
    mainLayout->addWidget(l_P2, 3,2,Qt::AlignRight);
    mainLayout->addWidget(sb_P2, 3,3);
    mainLayout->addWidget(l_P3, 3,4,Qt::AlignRight);
    mainLayout->addWidget(sb_P3, 3,5);
    mainLayout->addWidget(l_Q1, 4,0,Qt::AlignRight);
    mainLayout->addWidget(sb_Q1, 4,1);
    mainLayout->addWidget(l_Q2, 4,2,Qt::AlignRight);
    mainLayout->addWidget(sb_Q2, 4,3);
    mainLayout->addWidget(l_Q3, 4,4,Qt::AlignRight);
    mainLayout->addWidget(sb_Q3, 4,5);
    mainLayout->addWidget(l_a1, 5,0,Qt::AlignRight);
    mainLayout->addWidget(l_p1, 5,1);
    mainLayout->addWidget(l_a2, 5,2,Qt::AlignRight);
    mainLayout->addWidget(l_p2, 5,3);
    mainLayout->addWidget(l_a3, 5,4,Qt::AlignRight);
    mainLayout->addWidget(l_p3, 5,5);

    sb_I1->setRange(-1000000, 1000000);
    sb_I2->setRange(-1000000, 1000000);
    sb_I3->setRange(-1000000, 1000000);
    sb_P1->setRange(-1000000, 1000000);
    sb_P2->setRange(-1000000, 1000000);
    sb_P3->setRange(-1000000, 1000000);
    sb_Q1->setRange(-1000000, 1000000);
    sb_Q2->setRange(-1000000, 1000000);
    sb_Q3->setRange(-1000000, 1000000);

    connect(sb_I1, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_I2, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_I3, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_P1, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_P2, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_P3, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_Q1, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_Q2, &QDoubleSpinBox::valueChanged, this, &Window::changed);
    connect(sb_Q3, &QDoubleSpinBox::valueChanged, this, &Window::changed);

    setLayout(mainLayout);

    setWindowTitle(tr("Phasor diagram"));
}

void Window::changed(){
    if(sb_P1->value() == 0 || sb_P2->value() == 0 || sb_P3->value() == 0) return;
    double a1 = std::atan(sb_Q1->value()/sb_P1->value());
    double a2 = std::atan(sb_Q2->value()/sb_P2->value());
    double a3 = std::atan(sb_Q3->value()/sb_P3->value());
    l_p1->setText(QString(std::to_string(a1).c_str()));
    l_p2->setText(QString(std::to_string(a2).c_str()));
    l_p3->setText(QString(std::to_string(a3).c_str()));
    ra->set(sb_I1->value(), sb_I2->value(), sb_I3->value(), a1, a2, a3);
    ra->update();
}
