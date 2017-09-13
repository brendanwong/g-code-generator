#include "positionedit.h"
#include <QDebug>
#include <QMouseEvent>

PositionEdit::PositionEdit()
{

}


void PositionEdit::mouseMoveEvent(QMouseEvent *)
{
    emit positionHoverSignal();

}

void PositionEdit::leaveEvent(QEvent *)
{
   emit leftPositionSignal();
}

