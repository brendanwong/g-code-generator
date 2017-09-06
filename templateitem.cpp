#include "templateitem.h"

TemplateItem::TemplateItem()
{
}

void TemplateItem::mouseDoubleClickEvent(QMouseEvent *)
{
    //insert code to update values

    emit switchTabs(0);
    emit rowPrint();


}
