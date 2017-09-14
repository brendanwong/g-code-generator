#ifndef CUSTOMTEMPLATE_H
#define CUSTOMTEMPLATE_H

#include <QWidget>

class CustomTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTemplate(QWidget *parent = nullptr);

    void mouseReleaseEvent(QMouseEvent *);

signals:
    void switchTabs(int);

public slots:
};

#endif // CUSTOMTEMPLATE_H
