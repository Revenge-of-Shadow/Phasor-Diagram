#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>


class RenderArea : public QWidget
{
    Q_OBJECT

    double I[3] = {0,0,0};
    double a[3] = {0,0,0};

public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
public slots:
    void set(double I1, double I2, double I3, double a1, double a2, double a3);
protected:
    void paintEvent(QPaintEvent *event) override;

private:

signals:
};

#endif // RENDERAREA_H
