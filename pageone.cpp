#include "pageone.h"
#include "wizard.h"
#include "templateitem.h"
#include "customtemplate.h"
#include "constants.h"

PageOne::PageOne(QWidget *parent) : QWidget(parent)
{
    //create widget to hold tabs
    tabWidget = new QTabWidget(this);

    //build each tab
    customTab(tabWidget);
    templateTab(tabWidget);

    //set opening screen to templates
    tabWidget->setCurrentIndex(1);

    //adjust default tab styling
    tabWidget->setStyleSheet("QTabWidget::pane {border: 0;}");
    tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected{ color:#ffffff}");

    tabWidget->setMinimumSize(400, 350);
}





void PageOne::customTab(QTabWidget *tabWidget)
{
    nameEdit = new QLineEdit;
    dateEdit = new QDateEdit;
    heightEdit = new QSpinBox;
    widthEdit = new QSpinBox;
    positionEdit = new PositionEdit;
    materialEdit = new QComboBox;
    amountEdit = new QSpinBox;

    //standard two digit width for uniformity
    heightEdit->setMinimumWidth(INT_FORM_WIDTH);
    heightEdit->setMaximumWidth(INT_FORM_WIDTH);
    widthEdit->setMinimumWidth(INT_FORM_WIDTH);
    widthEdit->setMaximumWidth(INT_FORM_WIDTH);
    positionEdit->setMinimumWidth(INT_FORM_WIDTH);

    //set properties for each form
    heightEdit->setRange(ARRAY_MIN, ARRAY_MAX);
    widthEdit->setRange(ARRAY_MIN, ARRAY_MAX);
    positionEdit->setRange(POSITION_MIN, POSITION_MAX);
    amountEdit->setRange(EXTRUSION_MIN, EXTRUSION_MAX);
    materialEdit->addItem("Calcium Chloride");
    materialEdit->addItem("Biomolecule in 1% Alginate");
    materialEdit->addItem("Substrate Solution");
    dateEdit->setDate(QDate::currentDate());

    amountEdit->setValue(25);
    amountEdit->setDisabled(true);

    //to enable mouse tracking and pop up for bed pos
    positionEdit->setAttribute(Qt::WA_Hover);
    positionEdit->setMouseTracking(true);

    //builds the print selection row (petri vs well plate)
    buildPrintSelection();

    //add each row of the form
    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", groupBox);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addRow("&Rows:", heightEdit);
    formLayout->addRow("&Columns:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Extrusion Amount (μl):", amountEdit);

    //build reference graphic for positions, set hidden by default
    positionGraphic = new QLabel;
    positionGraphic->hide();

    //set frameless and non intrusive
    positionGraphic->setWindowFlag(Qt::FramelessWindowHint);
    positionGraphic->setAttribute(Qt::WA_ShowWithoutActivating);

    //connect appropriate show/hide slots for position reference graphic
    connect(positionEdit, SIGNAL(positionHoverSignal()), this, SLOT(positionHoverSlot()));
    connect(positionEdit, SIGNAL(leftPositionSignal()), this, SLOT(leftPositionSlot()));

    //add custom tab to the main tab widget
    QWidget *customWindow = new QWidget;
    customWindow->setLayout(formLayout);
    tabWidget->addTab(customWindow, "Custom");
}





void PageOne::buildPrintSelection()
{
    //build and group component selections
    groupBox = new QGroupBox;
    petriRadio = new QRadioButton(tr("Petri Dish"));
    wellPlateRadio = new QRadioButton(tr("Well Plate"));

    //set so that only one button may be selected
    petriRadio->setAutoExclusive(true);
    wellPlateRadio->setAutoExclusive(true);

    //default selection
    petriRadio->setChecked(true);

    //add buttons to layout
    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(petriRadio);
    groupBoxLayout->addWidget(wellPlateRadio);
    groupBox->setLayout(groupBoxLayout);

    groupBox->setStyleSheet("border: 0");
    groupBoxLayout->setContentsMargins(0, 0, 0, 0);

    //connect buttons to appropriate slots
    connect(wellPlateRadio, SIGNAL(clicked(bool)), this, SLOT(onWellPlateRadioClicked()));
    connect(petriRadio, SIGNAL(clicked(bool)), this, SLOT(onPetriRadioClicked()));
}






void PageOne::templateTab(QTabWidget *tabWidget)
{
    //encapsulating widget to house the layouts
    QFrame *templateWindow = new QFrame;

    //encapsulating horizontal widget to house each level of templates
    QHBoxLayout *firstRowLayout = new QHBoxLayout;
    QHBoxLayout *secondRowLayout = new QHBoxLayout;

    //paths to be changed once icons are finalized
    buildCustomTemplate(firstRowLayout, "Custom" ,
                        "://resources/custom-template.png");

    buildTemplateItem(firstRowLayout, "Row Print" ,
                      "://resources/template-1.png", SLOT(onRowTemplateClicked()));
    buildTemplateItem(firstRowLayout, "3x3 Petri Dish" ,
                      "://resources/template-2.png", SLOT(gridPetriClicked()));

    buildTemplateItem(secondRowLayout, "3x3 Well Plate" ,
                      "://resources/template-3.png", SLOT(gridPlateClicked()));
    buildTemplateItem(secondRowLayout, "Well Plate Column" ,
                      "://resources/template-4.png", SLOT(wellPlateColumnClicked()));
    buildTemplateItem(secondRowLayout, "Fill Well Plate" ,
                      "://resources/template5.png", SLOT(fillWellClicked()));

    //put together each row
    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->addLayout(firstRowLayout);
    vlayout->addLayout(secondRowLayout);

    //ensure consistent spacing
    firstRowLayout->setContentsMargins(0, 0, 0, 0);
    secondRowLayout->setContentsMargins(0, 0, 0, 0);

    //set layout and add template tab to main tab widget
    templateWindow->setLayout(vlayout);
    tabWidget->addTab(templateWindow, "Templates");

}





void PageOne::buildCustomTemplate(QHBoxLayout *hlayout, QString title, QString iconPath)
{
    //builds the custom template
    CustomTemplate *item = new CustomTemplate;

    QVBoxLayout *vlayout = new QVBoxLayout;

    //create template icon
    QLabel *iconLabel = new QLabel;
    QPixmap icon(iconPath);
    icon.setDevicePixelRatio(devicePixelRatio());
    iconLabel->setPixmap(icon);

    //set title of label
    QLabel *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    //put components together
    vlayout->addWidget(iconLabel);
    vlayout->addWidget(label);
    item->setLayout(vlayout);

    //add functionality
    QObject::connect(item, SIGNAL(switchTabs(int)), tabWidget, SLOT(setCurrentIndex(int)));

    hlayout->addWidget(item);
}





void PageOne::buildTemplateItem(QHBoxLayout *hlayout, QString title, QString iconPath, const char *slot)
{
    //builds a template item
    TemplateItem *item = new TemplateItem;

    QVBoxLayout *vlayout = new QVBoxLayout;

    //create template icon
    QLabel *iconLabel = new QLabel;
    QPixmap icon(iconPath);
    icon.setDevicePixelRatio(devicePixelRatio());
    iconLabel->setPixmap(icon.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    //set label title
    QLabel *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    //puts components together
    vlayout->addWidget(iconLabel);
    vlayout->addWidget(label);
    item->setLayout(vlayout);

    //adds functionality, switching the tab and changing appropriate settings
    QObject::connect(item, SIGNAL(activateTemplate()), this, slot);

    hlayout->addWidget(item);

}






void PageOne::onWellPlateRadioClicked()
{
    //shows warning message only once
    if (firstMessage == true)
    {
        QMessageBox warningMessage;
        warningMessage.setText("Note: Well plate prints currently only print "
                               "accurately to the Greiner 650161 well plate.");
        warningMessage.exec();
        firstMessage = false;
    }

    //new max width for well plate
    widthEdit->setRange(1, 12);
    widthEdit->update();

    //disabling position since not needed for well plate prints
    positionEdit->setDisabled(true);
    positionEdit->update();

    //enabling variable extrusion amount
    amountEdit->setEnabled(true);
    amountEdit->update();
}






void PageOne::onPetriRadioClicked()
{
    //new max value for petri dish
    widthEdit->setRange(1, 8);
    widthEdit->update();

    //enabling position for petri dish prints
    positionEdit->setEnabled(true);
    positionEdit->update();

    //disabling extrusion variability
    amountEdit->setDisabled(true);
    amountEdit->update();
}





//when positionEdit widget is hovered, show the graphic
void PageOne::positionHoverSlot()
{
    QPoint globalPos = positionEdit->mapToGlobal(QPoint(0,0));

    int x = globalPos.x();
    int y = globalPos.y();

    x += 100;
    positionGraphic->move(x, y);

    if(petriRadio->isChecked())
    {
        QPixmap icon("://resources/petri-template.png");
        icon.setDevicePixelRatio(devicePixelRatio());
        positionGraphic->setPixmap(icon.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if(wellPlateRadio->isChecked())
    {
        QPixmap icon("://resources/well-plate-template.png");
        icon.setDevicePixelRatio(devicePixelRatio());
        positionGraphic->setPixmap(icon.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    positionGraphic->show();
    positionGraphic->update();
}





//when positionEdit is no longer in focus, remove graphic
void PageOne::leftPositionSlot()
{
    positionGraphic->hide();
    positionGraphic->update();
}







/*
 *
 *
 * template signals/slots
 *
 *
 */
void PageOne::onRowTemplateClicked()
{
    emit rowTemplateSignal();
    emit nextPage();
}






void PageOne::gridPetriClicked()
{
    emit gridPetriSignal();
    emit nextPage();
}






void PageOne::fillWellClicked()
{
    emit fillWellSignal();
    emit nextPage();
}






void PageOne::gridPlateClicked()
{
    emit gridPlateSignal();
    emit nextPage();
}






void PageOne::wellPlateColumnClicked()
{
    emit wellPlateColumnSignal();
    emit nextPage();
}
