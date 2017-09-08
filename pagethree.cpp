#include "pagethree.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>

PageThree::PageThree(QWidget *parent) : QWidget(parent)
{
    QWidget *widget = new QWidget(this);
    buildTemplateEdit(widget);

}

void PageThree::buildTemplateEdit(QWidget *widget)
{
    QLineEdit *nameEdit = new QLineEdit;
    QDateEdit *dateEdit = new QDateEdit;
    QSpinBox *heightEdit = new QSpinBox;
    QSpinBox *widthEdit = new QSpinBox;
    QSpinBox *positionEdit = new QSpinBox;


}
