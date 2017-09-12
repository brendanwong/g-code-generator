#ifndef POSITIONEDIT_H
#define POSITIONEDIT_H

#include <QSpinBox>

class PositionEdit : public QSpinBox
{
    Q_OBJECT
public:
    PositionEdit();
    void mouseMoveEvent(QMouseEvent *);

signals:
    void positionHoverSignal();

};

#endif // POSITIONEDIT_H
