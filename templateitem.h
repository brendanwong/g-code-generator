#ifndef TEMPLATEITEM_H
#define TEMPLATEITEM_H

#include "pageone.h"
#include "wizard.h"

#include <QWidget>


class TemplateItem : public QWidget
{
    Q_OBJECT
public:
    TemplateItem();
    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void switchPage(int);
    void activateTemplate();

};

#endif // TEMPLATEITEM_H


