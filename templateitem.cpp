#include "templateitem.h"

TemplateItem::TemplateItem()
{
}

void TemplateItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit switchPage(1);
    emit activateTemplate();
}
