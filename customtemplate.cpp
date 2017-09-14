#include "customtemplate.h"

CustomTemplate::CustomTemplate(QWidget *parent) : QWidget(parent)
{

}

void CustomTemplate::mouseReleaseEvent(QMouseEvent *)
{
    //signal to switch to custom tab
    emit switchTabs(0);
}

