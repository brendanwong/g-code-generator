#ifndef TEMPLATEITEM_H
#define TEMPLATEITEM_H

#include <QWidget>
#include <QListWidgetItem>

class TemplateItem : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    TemplateItem();
    TemplateItem(int a);

    void mouseDoubleClickEvent(QMouseEvent *);

    int a;
};

#endif // TEMPLATEITEM_H


