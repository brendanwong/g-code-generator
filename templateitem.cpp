#include "templateitem.h"


TemplateItem::TemplateItem()
{
}

void TemplateItem::mouseReleaseEvent(QMouseEvent *)
{
    emit switchPage(1);
    emit activateTemplate();
}


