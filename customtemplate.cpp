#include "customtemplate.h"

CustomTemplate::CustomTemplate(QWidget *parent) : QWidget(parent)
{

}

void CustomTemplate::mouseDoubleClickEvent(QMouseEvent *)
{
    emit switchTabs(0);
}

