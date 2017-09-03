#ifndef TEMPLATEITEM_H
#define TEMPLATEITEM_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>

class TemplateItem : public QWidget
{
    Q_OBJECT
public:
    TemplateItem();

    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void switchTabs(int);

};

#endif // TEMPLATEITEM_H


