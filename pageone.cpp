#include "pageone.h"
#include "wizard.h"
#include "templateitem.h"
#include "customtemplate.h"

#include "constants.h"
#include <QScrollArea>

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
    positionEdit = new QSpinBox;
    materialEdit = new QComboBox;
    amountEdit = new QSpinBox;

    //standard two digit width for uniformity
    heightEdit->setMinimumWidth(42);
    widthEdit->setMinimumWidth(42);
    positionEdit->setMinimumWidth(42);

    //set properties for each form
    heightEdit->setRange(1, 8);
    widthEdit->setRange(1, 8);
    positionEdit->setRange(1, 4);
    amountEdit->setRange(10, 150);
    materialEdit->addItem("Calcium Chloride");
    materialEdit->addItem("Biomolecule in 1% Alginate");
    materialEdit->addItem("Substrate Solution");
    dateEdit->setDate(QDate::currentDate());

    amountEdit->setValue(25);
    amountEdit->setDisabled(true);

    //builds the print selection row (petri vs well plate)
    buildPrintSelection();

    //add each part of the form
    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", groupBox);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addRow("&Rows:", heightEdit);
    formLayout->addRow("&Columns:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Extrusion Amount (μl):", amountEdit);

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
    QObject::connect(wellPlateRadio, SIGNAL(clicked(bool)), this, SLOT(onWellPlateRadioClicked()));
    QObject::connect(petriRadio, SIGNAL(clicked(bool)), this, SLOT(onPetriRadioClicked()));
}






void PageOne::templateTab(QTabWidget *tabWidget)
{
    //encapsulating widget to house the layouts
    QFrame *templateWindow = new QFrame;

    //encapsulating horizontal widget to house each level of templates
    QHBoxLayout *firstRowLayout = new QHBoxLayout;
    QHBoxLayout *secondRowLayout = new QHBoxLayout;

    //paths to be changed once icons are finalized
    buildCustomTemplate(firstRowLayout, "Custom" , "/Users/brendanwong/Desktop/custom-template.png");
    buildTemplateItem(firstRowLayout, "Row Print" , "/Users/brendanwong/Desktop/template-1.png", SLOT(onRowTemplateClicked()));
    buildTemplateItem(firstRowLayout, "3x3 CaCl2" , "/Users/brendanwong/Desktop/template-2.png", SLOT(templateTwo()));

    buildTemplateItem(secondRowLayout, "Fill Well Plate" , "/Users/brendanwong/Desktop/template-3.png", SLOT(fillWell()));
    buildTemplateItem(secondRowLayout, "Template 4" , "/Users/brendanwong/Desktop/template-4.png", SLOT(templateTwo()));
    buildTemplateItem(secondRowLayout, "Template 5" , "/Users/brendanwong/Desktop/template-5.png", SLOT(templateTwo()));

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
    iconLabel->setPixmap(icon);

    //set label title
    QLabel *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    //puts components together
    vlayout->addWidget(iconLabel);
    vlayout->addWidget(label);
    item->setLayout(vlayout);

    //adds functionality, switching the tab and changing appropriate settings
    QObject::connect(item, SIGNAL(rowPrint()), this, slot);
    QObject::connect(item, SIGNAL(switchTabs(int)), tabWidget, SLOT(setCurrentIndex(int)));

    hlayout->addWidget(item);
}







void PageOne::onWellPlateRadioClicked()
{
    //shows warning message only once
    if (firstMessage == true)
    {
        QMessageBox warningMessage;
        warningMessage.setText("Note: This will only print accurately to the Greiner 650161 well plate.");
        warningMessage.exec();
        firstMessage = false;
    }

    //new max value for well plate
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



void PageOne::onRowTemplateClicked()
{
    //slot for row print settings
    wellPlateRadio->click();
    widthEdit->setValue(12);
    heightEdit->setValue(1);
}


void PageOne::templateTwo()
{
    //slot for 3x3 CaCl2 prints
   petriRadio->click();
   widthEdit->setValue(3);
   heightEdit->setValue(3);

}


void PageOne::fillWell()
{
    //slot to fill entire well plate
    wellPlateRadio->click();
    widthEdit->setValue(12);
    heightEdit->setValue(8);
}


