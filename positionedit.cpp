#include "positionedit.h"
#include <QMessageBox>
#include <QDebug>

PositionEdit::PositionEdit()
{

}




void PositionEdit::mouseMoveEvent(QMouseEvent *)
{
    emit positionHoverSignal();
    qDebug() << Q_FUNC_INFO << QString("Position Edit is being hovered");
}


