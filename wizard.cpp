#include "wizard.h"
#include "pageone.h"
#include "pagetwo.h"
#include "pagethree.h"
#include "constants.h"

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

    connect(pageOne->acceptDeal, SIGNAL(toggled(bool)), next, SLOT(setEnabled(bool)));

    connect(next, SIGNAL(clicked(bool)), this, SLOT(saveFormInfo()));
    connect(this, SIGNAL(emitOutput(QString)), this, SLOT(makeMessageBox(QString)));

}

void Wizard::makeMessageBox(QString output)
{
    QMessageBox a;
    a.setText(output);
    a.exec();
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

    //String conversion for later use
    yearString = QString::number(yearInput);
    monthString = QString::number(monthInput);
    dayString = QString::number(dayInput);

    generateCode();

}

void Wizard::generateCode()
{
    int calc;

    int X_MOVE = DISH_DIAMETER - X_BORDER;
    X_MOVE = X_MOVE / widthInput;

    int Y_MOVE = DISH_DIAMETER - Y_BORDER;
    Y_MOVE = Y_MOVE / heightInput;

    QString materialString;
    switch(materialInput)
    {
    case 0:
        materialString =  "CaCl2";
        break;
    case 1:
        materialString = "HPR";
        break;
    case 2:
        materialString =  "ABTS";
        break;
    }

    output += "(Name: " + nameInput + ")\n";
    output += "(Material: " + materialString + ")\n";
    output += "(Position: " + QString::number(positionInput) + ")\n";
    output += "(Size: " + QString::number(widthInput) + "x" + QString::number(heightInput) + ")\n";
    output += "(Date: " + monthString + "/" + dayString + "/" + yearString + ")\n\n";

    //Begin building gcode

    output += "G90\n";
    output += "G1 Z" + DISH_HEIGHT + " F1000\n";

    switch(positionInput)
    {
    case 1:
        output += "G1 X" + COORD_1 + " Y" + COORD_1 + " F" + FR_MOVE_XY + "\n";
        break;
    case 2:
        output += "G1 X" + COORD_2 + " Y" + COORD_1 + " F" + FR_MOVE_XY + "\n";
        break;
    case 3:
        output += "G1 X" + COORD_1 + " Y" + COORD_2 + " F" + FR_MOVE_XY + "\n";
        break;
    case 4:
        output += "G1 X" + COORD_2 + " Y" + COORD_2 + " F" + FR_MOVE_XY + "\n";
    }

    switch(materialInput)
    {
    case 0:
        //Calcium Carbonate
        output += "G1 Z" + Z_START_CACL2 + " F1000\n";
        break;
    case 1:
        //HPR
        output += "G1 Z" + Z_START_ALGINATE + " F1000\n";
        break;
    case 2:
        //ABTS
        output += "G1 Z" + Z_START_ABTS + " F1000\n";
        break;
    }

    //Relative positioning start

    output += "\nG91\n\n";

    switch(materialInput)
    {
    //CaCl2 print
    case 0:
        for (int row = 0; row < heightInput; row++)
        {
            for (int col = 0; col < (widthInput - 1); col++)
            {
                output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + DWELL + "\n";
                output += "G1 Z" + Z_MOVE + " F" + Z_FEEDRATE + "\n";

                calc = row % 2 ? -1 : 1;
                calc *= X_MOVE;
                QString temp  = QString::number(calc);

                output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n";
                output += "G1 Z-" + Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
            }
            output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
            output += "G4 P" + DWELL + "\n";
            output += "G1 Z" + Z_MOVE + " F" + Z_FEEDRATE + "\n";

            if (row < heightInput - 1)
            {
                output += "G1 Y" + QString::number(Y_MOVE) + " F" + FR_MOVE_XY + "\n";
                output += "G1 Z-" + Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
            }
            else
                output += "\n\n";
        }
        output += "G90\n";
        output += "G1 Z" + DISH_HEIGHT + " F1000\n";
        output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
        output += "G1 X100 Y10 F6000\n";
        output += "M84\n";
        break;

        // 1% HPR Alginate Mixture
    case 1:
        for (int row = 0; row < heightInput; row++)
        {
            for (int col = 0; col < (widthInput - 1); col++)
            {
                output += "G1 E" + ALG_EXT + " F" + FR_EXTRUDE + "\n";
                output += "G1 E-" + ALG_EXT_REV + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + ALG_DWELL + "\n";

                calc = row % 2 ? -1 : 1;
                calc *= X_MOVE;
                QString temp = QString::number(calc);

                output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n\n";
            }
            output += "G1 E" + ALG_EXT + " F" + FR_EXTRUDE + "\n";
            output +=  "G1 E-" + ALG_EXT_REV + " F" + FR_EXTRUDE + "\n";
            output += "G4 P" + ALG_DWELL + "\n";

            if (row < heightInput - 1)
                output += "G1 Y" + QString(Y_MOVE) + " F" + FR_MOVE_XY + "\n\n";
            else
                output += "\n\n";
        }
        output += "G90\n";
        output += "G1 Z" + DISH_HEIGHT + " F1000\n";
        output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
        output += "G1 X100 Y10 F6000\n";
        output += "M84\n";
        break;

        //ABTS Substrate -- assay print
    case 2:
        for (int row = 0; row < heightInput; row++)
        {
            for (int col = 0; col < (widthInput - 1); col++)
            {
                output += "G1 E" + ABTS_EXT + " F" + FR_EXTRUDE + "\n";
                output += "G1 E-" + ABTS_EXT_REV + " F" + FR_ABTS_EXT + "\n";
                output += "G4 P" + DWELL + "\n";

                calc = row % 2 ? -1 : 1;
                calc *= X_MOVE;
                QString temp = QString::number(calc);

                output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n\n";
            }
            output += "G1 E " + ABTS_EXT + " F " + FR_EXTRUDE + "\n";
            output += "G1 E-" + ABTS_EXT_REV + " F" + FR_ABTS_EXT + "\n";
            output += "G4 P" + DWELL + "\n";

            if (row < heightInput - 1)
                output += "G1 Y" + QString(Y_MOVE) + " F" + FR_MOVE_XY + "\n\n";
            else
                output += "\n\n";
        }
        break;
    }

    emit emitOutput(output);
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

