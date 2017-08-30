#include "wizard.h"

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
    QWidget *rightWidget = new QWidget;

    //container for the array/template code generation
    pageLayout->addWidget(pages);

    //bottom right layout, navigation buttons
    next->setMinimumWidth(100);
    previous->setMinimumWidth(100);
    cancel->setMinimumWidth(100);

    buttonLayout->addWidget(previous, 0, Qt::AlignLeft);
    buttonLayout->addWidget(next, 0, Qt::AlignLeft);
    buttonLayout->addWidget(cancel, 0, Qt::AlignRight);

    buildSideBar(mainLayout);

    //right layout, contains user input and naviation
    rightLayout->addLayout(pageLayout);
    rightLayout->addLayout(buttonLayout);

    //right widget to encapsulate input and buttons
    rightWidget->setLayout(rightLayout);

    //main layout to hold everything
    mainLayout->addWidget(rightWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    //create forms
    pages->addWidget(pageOne = new PageOne(pages));
    pages->addWidget(pageTwo = new PageTwo(pages));

    //button functionality
    previous->setEnabled(false);

    connect(next, SIGNAL(clicked()), this, SLOT(doNext()));
    connect(previous, SIGNAL(clicked()), this, SLOT(doPrev()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    connect(next, SIGNAL(clicked(bool)), this, SLOT(saveFormInfo()));
    connect(this, SIGNAL(emitOutput(QString)), pageTwo, SLOT(updateOutput(QString)));
    connect(this, SIGNAL(emitTitle(QString)), pageTwo, SLOT(updateTitle(QString)));
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
    welcome->setText("Welcome to Rebel X");
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

    //build component links, replace icon file paths if forked
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, ABOUT_LINK, "/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/rebel-mini-logo.png",
                        "About the Rebel", "Learn about our flagship");
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, VISIT_LINK, "/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/browser-mini-logo.png",
                        "Visit SE3D", "Check out our website ");
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, CONTACT_LINK, "/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/rebel-mini-logo.png",
                        "Contact Us", "Questions? Let us know");
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, DEMO_LINK, "/Users/brendanwong/Documents/Qt projects/gcg-gui/resources/research-mini-logo.png",
                        "Request a Demo", "or preview our curriculum");

    sidebar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sidebar->setStyleSheet("background-color:#252525");
    sidebar->setMinimumWidth(220);
    sidebar->setMaximumWidth(220);

    sidebar->setLayout(sidebarLayout);
    mainLayout->addWidget(sidebar);
}





void Wizard::buildSidebarLink(QVBoxLayout *sidebarLayout, QString inLink, QString location, QString inLabel, QString inDescr)
{
    //Custom link widget to encapsulate everything and provide clickability
    Link *linkWidget = new Link(inLink);
    linkWidget->setMaximumHeight(30);

    //Horizontal layout to hold icon and vertical layout
    QHBoxLayout *HLayout = new QHBoxLayout;
    QLabel *iconLabel = new QLabel;
    QPixmap icon(location);
    iconLabel->setPixmap(icon);

    //Vertical layout to hold title and description
    QVBoxLayout *VLayout = new QVBoxLayout;
    QLabel *label = new QLabel;
    label->setText(inLabel);
    label->setStyleSheet("color: #ffffff");

    QLabel *description = new QLabel;
    description->setText(inDescr);
    description->setStyleSheet("color: #8F8D8D;"
                                "font: 11px");

    VLayout->addWidget(label);
    VLayout->addWidget(description);

    HLayout->addWidget(iconLabel);
    HLayout->addLayout(VLayout);
    linkWidget->setLayout(HLayout);

    HLayout->setAlignment(Qt::AlignLeft);
    VLayout->setContentsMargins(0, 0, 0, 0);
    HLayout->setContentsMargins(0, 0, 0, 0);

    sidebarLayout->addWidget(linkWidget);
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
    //Save information from text fields, invoked when next button is clicked
    nameInput = pageOne->nameEdit->text();
    yearInput = pageOne->dateEdit->date().year();
    monthInput = pageOne->dateEdit->date().month();
    dayInput = pageOne->dateEdit->date().day();
    heightInput = pageOne->heightEdit->value();
    widthInput = pageOne->widthEdit->value();
    positionInput = pageOne->positionEdit->value();
    materialInput = pageOne->materialEdit->currentIndex();

    yearString = QString::number(yearInput);
    monthString = QString::number(monthInput);
    dayString = QString::number(dayInput);

    buildTitle();
    generateCode();
}




void Wizard::buildTitle()
{
    QString title = "";
    switch(materialInput)
    {
    case 0:
        title +=  "CaCl2 - ";
        break;
    case 1:
        title += "HPR - ";
        break;
    case 2:
        title +=  "ABTS - ";
        break;
    }
    title += QString::number(widthInput);
    title += "x";
    title += QString::number(heightInput);

    emit emitTitle(title);
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

    //G-Code commented confirmation of inputs
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




//window navigation
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

