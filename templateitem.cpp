#include "templateitem.h"

TemplateItem::TemplateItem()
{
    inUrl = "www.google.com";
    url.setUrl(inUrl);
}

TemplateItem::TemplateItem(QString inUrl)
{
    url.setUrl(inUrl);
}

void TemplateItem::mouseDoubleClickEvent(QMouseEvent *)
{
    QDesktopServices::openUrl(url);
}
