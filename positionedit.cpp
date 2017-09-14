#include "positionedit.h"

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

void PositionEdit::mouseReleaseEvent(QMouseEvent *)
{
    emit positionHoverSignal();
}

