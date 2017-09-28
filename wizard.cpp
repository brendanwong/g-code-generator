#include "wizard.h"

Wizard::Wizard() : QDialog()
{
    //create navigation buttons
    cancel = new QPushButton(tr("Quit"));
    next = new QPushButton(tr("Next"));
    previous = new QPushButton(tr("Previous"));
    pages = new QStackedWidget();

    //mainLayout to encapsulate everything
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    //rightLayout to hold tab widget and buttons
    QVBoxLayout *rightLayout = new QVBoxLayout;

    //pageLayout to hold tab widget
    QHBoxLayout *pageLayout = new QHBoxLayout;

    //buttonLayout to hold buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    //encapsulating right widget to hold tab widget and buttons
    //in addition to rightLayout for uniform and aesthetically pleasing border
    QWidget *rightWidget = new QWidget;

    //container for the array/template code generation
    pageLayout->addWidget(pages);

    //bottom right layout, navigation buttons
    next->setMinimumWidth(BUTTON_WIDTH);
    previous->setMinimumWidth(BUTTON_WIDTH);
    cancel->setMinimumWidth(BUTTON_WIDTH);
    cancel->setFocusPolicy(Qt::NoFocus);
    previous->setDisabled(true);

    //adding buttons to layout
    buttonLayout->addWidget(cancel, 0, Qt::AlignLeft);
    buttonLayout->addWidget(previous, 0, Qt::AlignRight);
    buttonLayout->addWidget(next, 0, Qt::AlignRight);

    buildSideBar(mainLayout);

    //adding widgets to right side
    rightLayout->addLayout(pageLayout);
    rightLayout->addLayout(buttonLayout);

    //right widget to encapsulate input and buttons
    rightWidget->setLayout(rightLayout);

    //adding widgets to main layout
    mainLayout->addWidget(rightWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    //create forms/output pages
    pages->addWidget(pageOne = new PageOne(pages));
    pages->addWidget(templateEdit = new TemplateEdit(pages));
    pages->addWidget(pageTwo = new PageTwo(pages));

    //adding button functionality

    connect(next, SIGNAL(clicked(bool)), this, SLOT(saveFormInfo()));
    connect(this, SIGNAL(emitOutput(QString)), pageTwo, SLOT(updateOutput(QString)));
    connect(this, SIGNAL(emitTitle(QString)), pageTwo, SLOT(updateTitle(QString)));

    connect(next, SIGNAL(clicked()), this, SLOT(doNext()));
    connect(previous, SIGNAL(clicked()), this, SLOT(doPrev()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    connect(pageOne, SIGNAL(rowTemplateSignal()), templateEdit, SLOT(rowTemplate()));
    connect(pageOne, SIGNAL(gridPetriSignal()), templateEdit, SLOT(gridPetriSlot()));
    connect(pageOne, SIGNAL(wellPlateColumnSignal()), templateEdit, SLOT(wellPlateColumnSlot()));
    connect(pageOne, SIGNAL(gridPlateSignal()), templateEdit, SLOT(gridPlateSlot()));
    connect(pageOne, SIGNAL(fillWellSignal()), templateEdit, SLOT(fillWellSlot()));
    connect(pageOne, SIGNAL(nextPage()), this, SLOT(doNext()));
}





void Wizard::buildSideBar(QHBoxLayout *mainLayout)
{
    //encapsulating frame for border and background
    QFrame *sidebar = new QFrame;
    QVBoxLayout *sidebarLayout = new QVBoxLayout;

    //main logo instantiation + properties
    QLabel *logo = new QLabel;
    logo->setText("SE3D Logo");
    QPixmap image("://Resources/se3d-circle-logo.svg");
    image.setDevicePixelRatio(devicePixelRatio());
    logo->setPixmap(image.scaled(SIDEBAR_LOGO_DIMS, SIDEBAR_LOGO_DIMS,
                                 Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignCenter);

    //title logo instantiation + properties
    QLabel *title = new QLabel;
    title->setText("G-Code Generator");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #ffffff;"
                           "font: 20px;");

    //version instantiation + properties. it looks more official :)
    QLabel *version = new QLabel;
    version->setText("Version " + VERSION);
    version->setAlignment(Qt::AlignCenter);
    version->setStyleSheet("color: #8F8D8D;"
                           "font: 11px;");

    //add logo, title, and version to sidebar
    sidebarLayout->addWidget(logo);
    sidebarLayout->addWidget(title);
    sidebarLayout->addWidget(version);

    //build divider and each component link
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, VISIT_LINK, "://resources/browser-logo.svg",
                        "Visit SE3D", "Check out our website ");
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, PORTAL_LINK, "://resources/rebel-logo-normal.svg",
                        "SE3D Portal", "Find tutorials and curriculum");
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, CONTACT_LINK, "://resources/eye.svg",
                        "Troubleshooting", "Questions? Let us know");
    addDivider(sidebarLayout);
    buildSidebarLink(sidebarLayout, SUPPLY_LINK, "://resources/science-logo.svg",
                        "Resupply", "Order more supplies here");

    //sidebar settings
    sidebar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sidebar->setStyleSheet("background-color: #252525");
    sidebar->setMinimumWidth(SIDEBAR_WIDTH);
    sidebar->setMaximumWidth(SIDEBAR_WIDTH);

    sidebar->setLayout(sidebarLayout);
    mainLayout->addWidget(sidebar);
}





void Wizard::buildSidebarLink(QVBoxLayout *sidebarLayout, QString inLink, QString location, QString inLabel, QString inDescr)
{
    //Custom link widget to encapsulate everything and provide clickability
    Link *linkWidget = new Link(inLink);
    linkWidget->setMaximumHeight(LINK_HEIGHT);

    //Horizontal layout to hold icon and vertical layout
    QHBoxLayout *HLayout = new QHBoxLayout;
    QLabel *iconLabel = new QLabel;
    QPixmap icon(location);
    icon.setDevicePixelRatio(devicePixelRatio());
    iconLabel->setPixmap(icon.scaled(LINK_ICON_DIMS, LINK_ICON_DIMS, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //Vertical layout to hold title and description
    QVBoxLayout *VLayout = new QVBoxLayout;
    QLabel *label = new QLabel;
    label->setText(inLabel);
    label->setStyleSheet("color: #ffffff");

    //Constraints to prevent text cutoff
    VLayout->setSizeConstraint(QLayout::SetMinimumSize);
    HLayout->setSizeConstraint(QLayout::SetMinimumSize);

    //build description
    QLabel *description = new QLabel;
    description->setText(inDescr);
    description->setStyleSheet("color: #8F8D8D;"
                                "font: 11px");

    //add widgets
    VLayout->addWidget(label);
    VLayout->addWidget(description);

    HLayout->addWidget(iconLabel);
    HLayout->addLayout(VLayout);
    linkWidget->setLayout(HLayout);

    //set properties
    HLayout->setAlignment(Qt::AlignLeft);
    VLayout->setContentsMargins(0, 0, 0, 0);
    HLayout->setContentsMargins(0, 0, 0, 0);

    sidebarLayout->addWidget(linkWidget);
}





void Wizard::addDivider(QVBoxLayout *sidebarLayout)
{
    //dividers to make it look pretty
    QFrame *divLine = new QFrame;
    divLine->setFrameShape(QFrame::HLine);
    divLine->setStyleSheet("color:#696969;");
    sidebarLayout->addWidget(divLine);
}





void Wizard::saveFormInfo()
{
    //write in code to only go through this when you are on the first or third page
    if (pages->currentIndex() == 0)
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
        extrusionAmount = pageOne->amountEdit->value();

        yearString = QString::number(yearInput);
        monthString = QString::number(monthInput);
        dayString = QString::number(dayInput);

        //build title based off of selections
        buildTitle();

        if (pageOne->petriRadio->isChecked())
        {
            printType = 0;
            generatePetriArray();
        }
        if (pageOne->wellPlateRadio->isChecked())
        {
            printType = 1;
            generatePlateArray();
        }
    }

    if (pages->currentIndex() == 1)
    {
        nameInput = templateEdit->nameEdit->text();
        yearInput = templateEdit->dateEdit->date().year();
        monthInput = templateEdit->dateEdit->date().month();
        dayInput = templateEdit->dateEdit->date().day();
        heightInput = templateEdit->heightEdit->value();
        widthInput = templateEdit->widthEdit->value();
        positionInput = templateEdit->positionEdit->value();
        materialInput = templateEdit->materialEdit->currentIndex();
        extrusionAmount = templateEdit->amountEdit->value();

        yearString = QString::number(yearInput);
        monthString = QString::number(monthInput);
        dayString = QString::number(dayInput);

        //build title based off of selections
        buildTitle();

        if (templateEdit->petriRadio->isChecked())
        {
            printType = 0;
            generatePetriArray();
        }
        if (templateEdit->wellPlateRadio->isChecked())
        {
            printType = 1;
            generatePlateArray();
        }
    }
}





void Wizard::buildTitle()
{
    //build title based off of form and selections
    QString title = "";

    switch(printType)
    {
    case 0:
        title += "Petri Dish ";
        break;
    case 1:
        title += "Well Plate ";
        break;
    }

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

    //to be picked up by pageTwo when file is saved
    emit emitTitle(title);
}





void Wizard::generatePetriArray()
{
    //calculations to allow variable size petri dishes
    int calc;
    int X_MOVE = DISH_DIAMETER - X_BORDER;
    int Y_MOVE = DISH_DIAMETER - Y_BORDER;

    X_MOVE = X_MOVE / widthInput;
    Y_MOVE = Y_MOVE / heightInput;

    //material string for input confirmation

    switch(materialInput)
    {
    case 0:
        materialString =  "CaCl2";
        break;
    case 1:
        materialString = "HPR";
        break;
    case 2:
        materialString = "ABTS";
        break;
    }

    output = "";

    //G-Code commented confirmation of inputs
    if (nameInput != "")
        output += "; Name: " + nameInput + " ;\n";
    switch(printType)
    {
    case 0:
        output += "; Type: Petri Dish ;\n";
        break;
    case 1:
        output += "; Type: Well Plate ;\n";
        break;
    }

    output += "; Material: " + materialString + " ;\n";
    output += "; Position: " + QString::number(positionInput) + " ;\n";
    output += "; Size: " + QString::number(widthInput) + "x" + QString::number(heightInput) + " ;\n";
    output += "; Date: " + monthString + "/" + dayString + "/" + yearString + " ;\n\n";

    //Begin building gcode
    output += "G90\n";
    output += "G1 Z" + DISH_HEIGHT + " F1000\n";

    //first position
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

    //initial drop height
    switch(materialInput)
    {
    case 0:
        //Calcium Carbonate
        output += "G1 Z" + PETRI_Z_CACL2 + " F1000\n";
        break;
    case 1:
        //HPR
        output += "G1 Z" + PETRI_Z_ALGINATE + " F1000\n";
        break;
    case 2:
        //ABTS
        output += "G1 Z" + PETRI_Z_ABTS + " F1000\n";
        break;
    }

    //Relative positioning start
    output += "\nG91\n\n";

    //begin printing
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
                output += "G1 Z" + PETRI_Z_MOVE + " F" + Z_FEEDRATE + "\n";

                calc = row % 2 ? -1 : 1;
                calc *= X_MOVE;
                QString temp  = QString::number(calc);

                output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n";
                output += "G1 Z-" + PETRI_Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
            }
            output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
            output += "G4 P" + DWELL + "\n";
            output += "G1 Z" + PETRI_Z_MOVE + " F" + Z_FEEDRATE + "\n";

            if (row < heightInput - 1)
            {
                output += "G1 Y" + QString::number(Y_MOVE) + " F" + FR_MOVE_XY + "\n";
                output += "G1 Z-" + PETRI_Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
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
                output += "G1 Y" + QString::number(Y_MOVE) + " F" + FR_MOVE_XY + "\n\n";
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
                output += "G1 Y" + QString::number(Y_MOVE) + " F" + FR_MOVE_XY + "\n\n";
            else
                output += "\n\n";

        }
        output += "G90\n";
        output += "G1 Z" + DISH_HEIGHT + " F1000\n";
        output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
        output += "G1 X100 Y10 F6000\n";
        output += "M84\n";
        break;
    }

    //signal to be picked up by pageTwo
    emit emitOutput(output);
}






void Wizard::generatePlateArray()
{
    int calc;

    //material string for input confirmation

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
        output += "; Name: " + nameInput + " ;\n";

    output += "; Type: Well Plate ;\n";
    output += "; Material: " + materialString + " ;\n";
    output += "; Extrusion amount: " + QString::number(extrusionAmount) + " μl ;\n";
    output += "; Size: " + QString::number(widthInput) + "x" + QString::number(heightInput) + " ;\n";
    output += "; Date: " + monthString + "/" + dayString + "/" + yearString + " ;\n\n";


    //Begin building gcode
    output += "G90\n";
    output += "G1 Z" + PLATE_HEIGHT + " F1000\n";
    output += "G1 X" + PLATE_START_X + " Y" + PLATE_START_Y + " F" + FR_MOVE_XY + "\n";

    switch(materialInput)
    {
        case 0:
            //Calcium Carbonate
            if (extrusionAmount < 50)
                output += "G1 Z" + PLATE_Z_CACL2 + " F1000\n";
            else
                output += "G1 Z16 F1000\n";
            break;
        case 1:
            //HPR
            output += "G1 Z" + PLATE_Z_ALGINATE + " F1000\n";
            break;
        case 2:
            //ABTS
            output += "G1 Z" + PLATE_Z_ABTS + " F1000\n";
            break;
    }

    //Relative positioning start
    output += "\nG91\n\n";


    //variable drop height depending on extrusion volume
    int z_move;

    if (extrusionAmount < 50)
        z_move = PLATE_Z_MOVE.toInt();
    else
        z_move = 0;

    //per g-code syntax
    extrusionAmount = extrusionAmount / 10;

    //being printing
    switch(materialInput)
    {
            //CaCl2 print
        case 0:
            for (int row = 0; row < widthInput; row++)
            {
                for (int col = 0; col < (heightInput - 1); col++)
                {
                    output += "G1 E" + QString::number(extrusionAmount) + " F" + FR_EXTRUDE + "\n";
                    output += "G4 P" + DWELL + "\n";
                    output += "G1 Z" + QString::number(z_move) + " F" + Z_FEEDRATE + "\n";

                    calc = row % 2 ? -1 : 1;
                    calc *= PLATE_XY_MOVE;
                    QString temp  = QString::number(calc);

                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n";
                    output += "G1 Z-" + QString::number(z_move) + " F" + Z_FEEDRATE + "\n\n";
                }
                output += "G1 E" + QString::number(extrusionAmount) + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + DWELL + "\n";
                output += "G1 Z" + QString::number(z_move) + " F" + Z_FEEDRATE + "\n";

                if (row < widthInput - 1)
                {
                    output += "G1 Y" + QString::number(PLATE_XY_MOVE) + " F" + FR_MOVE_XY + "\n";
                    output += "G1 Z-" + QString::number(z_move) + " F" + Z_FEEDRATE + "\n\n";
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
            for (int row = 0; row < widthInput; row++)
            {
                for (int col = 0; col < (heightInput - 1); col++)
                {
                    output += "G1 E" + QString::number(extrusionAmount) + " F" + FR_EXTRUDE + "\n";
                    output += "G1 E-" + ALG_EXT_REV + " F" + FR_EXTRUDE + "\n";
                    output += "G4 P" + ALG_DWELL + "\n";

                    calc = row % 2 ? -1 : 1;
                    calc *= PLATE_XY_MOVE;
                    QString temp = QString::number(calc);

                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n\n";
                }
                output += "G1 E" + QString::number(extrusionAmount) + " F" + FR_EXTRUDE + "\n";
                output +=  "G1 E-" + ALG_EXT_REV + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + ALG_DWELL + "\n";

                if (row < widthInput - 1)
                    output += "G1 Y" + QString::number(PLATE_XY_MOVE) + " F" + FR_MOVE_XY + "\n\n";
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
            for (int row = 0; row < widthInput; row++)
            {
                for (int col = 0; col < (heightInput - 1); col++)
                {
                    output += "G1 E" + QString::number(extrusionAmount) + " F" + FR_EXTRUDE + "\n";
                    output += "G1 E-" + ABTS_EXT_REV + " F" + FR_ABTS_EXT + "\n";
                    output += "G4 P" + DWELL + "\n";

                    calc = row % 2 ? -1 : 1;
                    calc *= PLATE_XY_MOVE;
                    QString temp = QString::number(calc);

                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n\n";
                }
                output += "G1 E " + QString::number(extrusionAmount) + " F " + FR_EXTRUDE + "\n";
                output += "G1 E-" + ABTS_EXT_REV + " F" + FR_ABTS_EXT + "\n";
                output += "G4 P" + DWELL + "\n";

                if (row < widthInput - 1)
                    output += "G1 Y" + QString::number(PLATE_XY_MOVE) + " F" + FR_MOVE_XY + "\n\n";
                else
                    output += "\n\n";

            }
            output += "G90\n";
            output += "G1 Z" + DISH_HEIGHT + " F1000\n";
            output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
            output += "G1 X100 Y10 F6000\n";
            output += "M84\n";
            break;
    }

    emit emitOutput(output);
}




//window navigation
void Wizard::doNext()
{
    previous->setEnabled(true);
   if (pageOne->tabWidget->currentIndex() == 0)
   {
       pages->setCurrentIndex(2);
       selection = 0;
   }
   else
   {
       pages->setCurrentIndex(pages->currentIndex() + 1);
       selection = 1;
   }

   if (pages->currentIndex() == 2)
      next->setDisabled(true);
}





void Wizard::doPrev()
{
    next->setEnabled(true);
    if (selection == 0)
        pages->setCurrentIndex(0);
    if (selection == 1)
        pages->setCurrentIndex(pages->currentIndex() - 1);

    if (pages->currentIndex() == 0)
    {
        templateEdit->petriRadio->setEnabled(true);
        templateEdit->wellPlateRadio->setEnabled(true);
        templateEdit->widthEdit->setEnabled(true);
        templateEdit->heightEdit->setEnabled(true);

    }
    if (pages->currentIndex() == 0)
        previous->setDisabled(true);
}






//functions to enable frameless window dragging
void Wizard::mousePressEvent(QMouseEvent *event)
{
    //tracks mouse clicks
    x_coord = event->x();
    y_coord = event->y();
}





void Wizard::mouseMoveEvent(QMouseEvent *event)
{
    //tracks mouse drags
    move(event->globalX()-x_coord,
         event->globalY()-y_coord);
}

