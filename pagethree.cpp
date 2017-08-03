#include "wizard.h"
#include "pagethree.h"


PageThree::PageThree(QWidget *parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("All is ready. Press finish to get it done!")), 0, 0);
}
