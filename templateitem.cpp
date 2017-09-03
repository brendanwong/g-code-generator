#include "templateitem.h"

TemplateItem::TemplateItem()
{
}

void TemplateItem::mouseDoubleClickEvent(QMouseEvent *)
{
    emit switchTabs(0);
}
