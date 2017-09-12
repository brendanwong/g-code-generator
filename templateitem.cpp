#include "templateitem.h"
#include <QDebug>

TemplateItem::TemplateItem()
{
}

void TemplateItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit switchPage(1);
    emit activateTemplate();
}

