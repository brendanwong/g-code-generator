#ifndef LINK_H
#define LINK_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>

class Link : public QWidget{
    Q_OBJECT
public:
    Link();
    Link(QString inUrl);
    QUrl url;
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // LINK_H
