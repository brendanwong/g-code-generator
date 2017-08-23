#include "wizard.h"
#include "pageone.h"
#include "pagetwo.h"
#include "constants.h"



Wizard::Wizard() : QDialog()
{
    cancel = new QPushButton(tr("Cancel"));
    next = new QPushButton(tr("Next"));
    previous = new QPushButton(tr("Previous"));
    pages = new QStackedWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QHBoxLayout *pageLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    //top right layout, pages
    pageLayout->addWidget(pages);

    //bottom right layout, navigation buttons
    next->setMinimumWidth(100);
    previous->setMinimumWidth(100);
    cancel->setMinimumWidth(100);

    buttonLayout->addWidget(previous, 0, Qt::AlignLeft);
    buttonLayout->addWidget(next, 0, Qt::AlignLeft);
    buttonLayout->addWidget(cancel, 0, Qt::AlignRight);

    buildSideBar(mainLayout);


    //right half layout, holds navigation and pages
    rightLayout->addLayout(pageLayout);
    rightLayout->addLayout(buttonLayout);
    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);
    //right widget to encapsulate the buttons and form to prevent the margin change to affect them
    //main layout, holds errthangggg
    mainLayout->addWidget(rightWidget);
    mainLayout->setContentsMargins(0,0,0,0);

    previous->setEnabled(false);

    connect(next, SIGNAL(clicked()), this, SLOT(doNext()));
    connect(previous, SIGNAL(clicked()), this, SLOT(doPrev()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    pages->addWidget(pageOne = new PageOne(pages));
    pages->addWidget(pageTwo = new PageTwo(pages));

    connect(next, SIGNAL(clicked(bool)), this, SLOT(saveFormInfo()));
    connect(this, SIGNAL(emitOutput(QString)), pageTwo, SLOT(updateOutput(QString)));
}




void Wizard::buildSideBar(QHBoxLayout *mainLayout)
{
    QFrame *sidebar = new QFrame;
    QVBoxLayout *sidebarLayout = new QVBoxLayout;

    QLabel *logo = new QLabel;
    logo->setText("SE3D Logo");
    QPixmap image("/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/se3d-logo-copy.png");
    logo->setPixmap(image);
    logo->setAlignment(Qt::AlignCenter);


    QLabel *welcome = new QLabel;
    welcome->setText("G-Code Generator");
    welcome->setAlignment(Qt::AlignCenter);
    welcome->setStyleSheet("color: #ffffff;"
                           "font: 20px;");

    QLabel *version = new QLabel;
    version->setText("Version " + VERSION);
    version->setAlignment(Qt::AlignCenter);
    version->setStyleSheet("color: #8F8D8D;"
                           "font: 11px;");

    sidebarLayout->addWidget(logo);
    sidebarLayout->addWidget(welcome);
    sidebarLayout->addWidget(version);

    //build component links
    addDivider(sidebarLayout);
    buildAbout(sidebarLayout);
    addDivider(sidebarLayout);
    buildVisit(sidebarLayout);
    addDivider(sidebarLayout);
    buildContact(sidebarLayout);
    addDivider(sidebarLayout);
    buildDemoRequest(sidebarLayout);

    sidebar->setLayout(sidebarLayout);
    sidebar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sidebar->setStyleSheet("background-color:#252525");
    sidebar->setMinimumWidth(220);
    sidebar->setMaximumWidth(220);
    mainLayout->addWidget(sidebar);
}





void Wizard::buildAbout(QVBoxLayout *sidebarLayout)
{
    Link *aboutWidget = new Link(ABOUT_LINK);
    QHBoxLayout *aboutHLayout = new QHBoxLayout;
    QLabel *icon = new QLabel;
    QPixmap aboutIcon("/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/rebel-mini-logo.png");
    icon->setPixmap(aboutIcon);
    aboutWidget->setMaximumHeight(30);

    QVBoxLayout *aboutVLayout = new QVBoxLayout;
    QLabel *aboutLabel = new QLabel;
    aboutLabel->setText("About the Rebel");
    aboutLabel->setStyleSheet("color:#ffffff");

    QLabel *aboutDescr = new QLabel;
    aboutDescr->setText("Learn about our printers");
    aboutDescr->setStyleSheet("color: #8F8D8D;"
                              "font: 11px");

    aboutVLayout->addWidget(aboutLabel);
    aboutVLayout->addWidget(aboutDescr);

    aboutHLayout->addWidget(icon);
    aboutHLayout->addLayout(aboutVLayout);
    aboutWidget->setLayout(aboutHLayout);

    aboutHLayout->setAlignment(Qt::AlignLeft);
    aboutVLayout->setContentsMargins(0, 0, 0, 0);
    aboutHLayout->setContentsMargins(0, 0, 0, 0);




    sidebarLayout->addWidget(aboutWidget);

}





void Wizard::buildVisit(QVBoxLayout *sidebarLayout)
{
    //visit se3d's website
    Link *visitWidget = new Link(VISIT_LINK);
    QHBoxLayout *visitHLayout = new QHBoxLayout;
    QLabel *visitIcon = new QLabel;
    QPixmap visitImage("/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/browser-mini-logo.png");
    visitIcon->setPixmap(visitImage);
    visitWidget->setMaximumHeight(30);


    QVBoxLayout *visitVLayout = new QVBoxLayout;
    QLabel *visitLabel = new QLabel;
    visitLabel->setText("Visit SE3D");
    visitLabel->setStyleSheet("color: #ffffff");

    QLabel *visitDescr = new QLabel;
    visitDescr->setText("Check out our website!!");
    visitDescr->setStyleSheet("color: #8F8D8D;"
                              "font: 11px");

    visitVLayout->addWidget(visitLabel);
    visitVLayout->addWidget(visitDescr);

    visitHLayout->addWidget(visitIcon);
    visitHLayout->addLayout(visitVLayout);
    visitWidget->setLayout(visitHLayout);

    visitVLayout->setContentsMargins(0, 0, 0, 0);
    visitHLayout->setContentsMargins(0, 0, 0, 0);
    visitHLayout->setAlignment(Qt::AlignLeft);


    sidebarLayout->addWidget(visitWidget);

}





void Wizard::buildContact(QVBoxLayout *sidebarLayout)
{
    Link *contactWidget = new Link(CONTACT_LINK);
    QHBoxLayout *contactHLayout = new QHBoxLayout;
    QLabel *icon = new QLabel;
    QPixmap contactIcon("/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/rebel-mini-logo.png");
    icon->setPixmap(contactIcon);
    contactWidget->setMaximumHeight(30);

    QVBoxLayout *contactVLayout = new QVBoxLayout;
    QLabel *contactLabel = new QLabel;
    contactLabel->setText("Contact Us");
    contactLabel->setStyleSheet("color:#ffffff");

    QLabel *contactDescr = new QLabel;
    contactDescr->setText("Questions? Let us know!");
    contactDescr->setStyleSheet("color: #8F8D8D;"
                              "font: 11px");

    contactVLayout->addWidget(contactLabel);
    contactVLayout->addWidget(contactDescr);

    contactHLayout->addWidget(icon);
    contactHLayout->addLayout(contactVLayout);
    contactWidget->setLayout(contactHLayout);

    contactHLayout->setAlignment(Qt::AlignLeft);
    contactVLayout->setContentsMargins(0, 0, 0, 0);
    contactHLayout->setContentsMargins(0, 0, 0, 0);

    sidebarLayout->addWidget(contactWidget);

}






void Wizard::buildDemoRequest(QVBoxLayout *sidebarLayout)
{
    //request a demo
    Link *demoWidget = new Link(DEMO_LINK);
    QHBoxLayout *demoHLayout = new QHBoxLayout;
    QLabel *demoIcon = new QLabel;
    QPixmap demoImage("/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/research-mini-logo.png");
    demoIcon->setPixmap(demoImage);
    demoWidget->setMaximumHeight(35);


    QVBoxLayout *demoVLayout = new QVBoxLayout;
    QLabel *demoLabel = new QLabel;
    demoLabel->setText("Request a Demo");
    demoLabel->setStyleSheet("color: #ffffff");

    QLabel *demoDescr = new QLabel;
    demoDescr->setText("Slide thru these DMs");
    demoDescr->setStyleSheet("color: #8F8D8D;"
                              "font: 11px");

    demoVLayout->addWidget(demoLabel);
    demoVLayout->addWidget(demoDescr);

    demoHLayout->addWidget(demoIcon);
    demoHLayout->addLayout(demoVLayout);
    demoWidget->setLayout(demoHLayout);

    demoVLayout->setContentsMargins(0, 0, 0, 0);
    demoHLayout->setContentsMargins(0, 0, 0, 0);
    demoHLayout->setAlignment(Qt::AlignLeft);
    sidebarLayout->addWidget(demoWidget);

}





void Wizard::addDivider(QVBoxLayout *sidebarLayout)
{
    QFrame *divLine = new QFrame;
    divLine->setFrameShape(QFrame::HLine);
    divLine->setStyleSheet("color:#696969;");
    sidebarLayout->addWidget(divLine);
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
    int Y_MOVE = DISH_DIAMETER - Y_BORDER;

    X_MOVE = X_MOVE / widthInput;
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

    output = "";

    //Commented confirmation of inputs
    if (nameInput != "")
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
    previous->setEnabled(true);
    next->setEnabled(false);
    pages->setCurrentIndex(pages->currentIndex() + 1);
}





void Wizard::doPrev()
{
    previous->setEnabled(false);
    next->setEnabled(true);
    pages->setCurrentIndex(pages->currentIndex() - 1);
}





//functions to enable frameless window dragging
void Wizard::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}





void Wizard::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate, event->globalY()-m_nMouseClick_Y_Coordinate);
}

