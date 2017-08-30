#include "link.h"

Link::Link()
{
    url = "www.se3d.com";
}

Link::Link(QString inUrl)
{
    url.setUrl(inUrl);
}

void Link::mouseReleaseEvent(QMouseEvent *)
{
    QDesktopServices::openUrl(url);
}
