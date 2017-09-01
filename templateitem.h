#ifndef TEMPLATEITEM_H
#define TEMPLATEITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QUrl>

class TemplateItem : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    TemplateItem();
    TemplateItem(QString inUrl);

    void mouseDoubleClickEvent(QMouseEvent *);

private:
    int a;
    QUrl url;
    QString inUrl;
};

#endif // TEMPLATEITEM_H


