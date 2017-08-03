#ifndef PAGETWO_H
#define PAGETWO_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>


class PageTwo : public QWidget
{
    Q_OBJECT
public:
    PageTwo(QWidget *parent = 0);
    void displayOutput(QFormLayout *layout);
};



#endif // PAGETWO_H
