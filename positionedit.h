#ifndef POSITIONEDIT_H
#define POSITIONEDIT_H

#include <QSpinBox>
#include <QMouseEvent>

class PositionEdit : public QSpinBox
{
    Q_OBJECT
public:
    PositionEdit();
    void mouseMoveEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void positionHoverSignal();
    void leftPositionSignal();

};

#endif // POSITIONEDIT_H
