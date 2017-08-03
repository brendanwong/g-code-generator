#include "wizard.h"
#include "pageone.h"
#include "pagetwo.h"
#include "pagethree.h"

#include "globals.h"


Wizard::Wizard() : QDialog()
{
    QGridLayout *layout = new QGridLayout(this);

    QPushButton *cancel = new QPushButton(tr("Cancel"));
    next = new QPushButton(tr("Next"));
    previous = new QPushButton(tr("Previous"));

    pages = new QStackedWidget();

    layout->addWidget(pages, 0, 0, 1, 5);
    layout->setColumnMinimumWidth(0, 50);
    layout->addWidget(previous, 1, 1);
    layout->addWidget(next, 1, 2);
    layout->setColumnMinimumWidth(3, 5);
    layout->addWidget(cancel, 1, 4);

    previous->setEnabled(false);
    next->setEnabled(false);

    connect(next, SIGNAL(clicked()), this, SLOT(doNext()));
    connect(previous, SIGNAL(clicked()), this, SLOT(doPrev()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    pages->addWidget(pageOne = new PageOne(pages));
    pages->addWidget(pageTwo = new PageTwo(pages));
    pages->addWidget(pageThree = new PageThree(pages));

    connect(pageOne->acceptDeal, SIGNAL(toggled(bool)), next,       SLOT(setEnabled(bool)));

    connect(next, SIGNAL(clicked(bool)), this, SLOT(saveFormInfo()));
}

void Wizard::saveFormInfo()
{
    nameInput = pageOne->nameEdit->text();
    yearInput = pageOne->dateEdit->date().year();
    monthInput = pageOne->dateEdit->date().month();
    dayInput = pageOne->dateEdit->date().day();
    heightInput = pageOne->heightEdit->value();
    widthInput = pageOne->widthEdit->value();
    positionInput = pageOne->positionEdit->value();
    materialInput = pageOne->materialEdit->currentIndex();
        //0 = calcium carbonate
        //1 = HPR
        //2 = ABTS

    //String conversion for later use
    yearString = QString::number(yearInput);
    monthString = QString::number(monthInput);
    dayString = QString::number(dayInput);

    global = nameInput;

}

void Wizard::doNext()
{
    switch(pages->currentIndex())
    {
      case 0:
        previous->setEnabled(true);
        disconnect(pageOne->acceptDeal, SIGNAL(toggled(bool)), next, SLOT(setEnabled(bool)));
        break;
    case 1:
        next->setText(tr("Finish"));
        break;
    case 2:
        QMessageBox::information(this, tr("Finishing"), tr("Here is where the action takes place."));
        accept();
        return;
    }

    pages->setCurrentIndex(pages->currentIndex() + 1);
}

void Wizard::doPrev()
{
    switch(pages->currentIndex())
    {
      case 1:
        previous->setEnabled(false);
        next->setEnabled(pageOne->acceptDeal->isChecked());

        connect(pageOne->acceptDeal, SIGNAL(toggled(bool)), next, SLOT(setEnabled(bool)));

        break;
      case 2:
        next->setText(tr("Next"));

        break;
    }

    pages->setCurrentIndex(pages->currentIndex() - 1);
}

