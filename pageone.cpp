#include "pageone.h"
#include "wizard.h"
#include "templateitem.h"
#include "customtemplate.h"

#include "constants.h"
#include <QScrollArea>

PageOne::PageOne(QWidget *parent) : QWidget(parent)
{
    tabWidget = new QTabWidget(this);

    customTab(tabWidget);
    templateTab(tabWidget);
    tabWidget->setCurrentIndex(1);

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


    buildPrintSelection();

    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", groupBox);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addRow("&Rows:", heightEdit);
    formLayout->addRow("&Columns:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Extrusion Amount (μl):", amountEdit);


    QWidget *customWindow = new QWidget;
    customWindow->setLayout(formLayout);
    tabWidget->addTab(customWindow, "Custom");
}





void PageOne::buildPrintSelection()
{
    groupBox = new QGroupBox;
    petriRadio = new QRadioButton(tr("Petri Dish"));
    wellPlateRadio = new QRadioButton(tr("Well Plate"));

    petriRadio->setAutoExclusive(true);
    wellPlateRadio->setAutoExclusive(true);
    petriRadio->setChecked(true); //default selected

    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(petriRadio);
    groupBoxLayout->addWidget(wellPlateRadio);
    groupBox->setLayout(groupBoxLayout);

    groupBox->setStyleSheet("border: 0");
    groupBoxLayout->setContentsMargins(0, 0, 0, 0);


    QObject::connect(wellPlateRadio, SIGNAL(clicked(bool)), this, SLOT(onWellPlateRadioClicked()));
    QObject::connect(petriRadio, SIGNAL(clicked(bool)), this, SLOT(onPetriRadioClicked()));
}






void PageOne::templateTab(QTabWidget *tabWidget)
{
    //encapsulating widget to house the layouts
    QFrame *templateWindow = new QFrame;
    //encapsulating horizontal widget to house first few

    QHBoxLayout *firstRowLayout = new QHBoxLayout;
    buildCustomTemplate(firstRowLayout, "Custom" , "/Users/brendanwong/Desktop/custom-template.png");
    buildTemplateItem(firstRowLayout, "Row Print" , "/Users/brendanwong/Desktop/template-1.png", SLOT(onRowTemplateClicked()));
    buildTemplateItem(firstRowLayout, "3x3 CaCl2" , "/Users/brendanwong/Desktop/template-2.png", SLOT(templateTwo()));

    QHBoxLayout *secondRowLayout = new QHBoxLayout;
    buildTemplateItem(secondRowLayout, "Fill Well Plate" , "/Users/brendanwong/Desktop/template-3.png", SLOT(fillWell()));
    buildTemplateItem(secondRowLayout, "Template 4" , "/Users/brendanwong/Desktop/template-4.png", SLOT(templateTwo()));
    buildTemplateItem(secondRowLayout, "Template 5" , "/Users/brendanwong/Desktop/template-5.png", SLOT(templateTwo()));

    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->addLayout(firstRowLayout);
    vlayout->addLayout(secondRowLayout);

    firstRowLayout->setContentsMargins(0,0,0,0);
    secondRowLayout->setContentsMargins(0,0,0,0);



    templateWindow->setLayout(vlayout);

    tabWidget->addTab(templateWindow, "Templates");

}





void PageOne::buildCustomTemplate(QHBoxLayout *hlayout, QString title, QString iconPath)
{
    CustomTemplate *item = new CustomTemplate;

    QVBoxLayout *vlayout = new QVBoxLayout;

    QLabel *iconLabel = new QLabel;
    QPixmap icon(iconPath);
    icon.setDevicePixelRatio(devicePixelRatio());
    iconLabel->setPixmap(icon);

    QLabel *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    vlayout->addWidget(iconLabel);
    vlayout->addWidget(label);
    item->setLayout(vlayout);

    QObject::connect(item, SIGNAL(switchTabs(int)), tabWidget, SLOT(setCurrentIndex(int)));

    hlayout->addWidget(item);
}





void PageOne::buildTemplateItem(QHBoxLayout *hlayout, QString title, QString iconPath, const char *slot)
{
    TemplateItem *item = new TemplateItem;

    QVBoxLayout *vlayout = new QVBoxLayout;

    QLabel *iconLabel = new QLabel;
    QPixmap icon(iconPath);
    icon.setDevicePixelRatio(devicePixelRatio());
    iconLabel->setPixmap(icon);

    QLabel *label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);

    vlayout->addWidget(iconLabel);
    vlayout->addWidget(label);
    item->setLayout(vlayout);

    QObject::connect(item, SIGNAL(rowPrint()), this, slot);
    QObject::connect(item, SIGNAL(switchTabs(int)), tabWidget, SLOT(setCurrentIndex(int)));

    hlayout->addWidget(item);
}










void PageOne::onWellPlateRadioClicked()
{
    if (firstMessage == true)
    {
        QMessageBox warningMessage;
        warningMessage.setText("Note: This will only print accurately to the Greiner 650161 well plate.");
        warningMessage.exec();
        firstMessage = false;
    }
    widthEdit->setRange(1, 12);
    widthEdit->update();
    positionEdit->setDisabled(true);
    positionEdit->update();
    amountEdit->setEnabled(true);
    amountEdit->update();

}






void PageOne::onPetriRadioClicked()
{
    widthEdit->setRange(1, 8);
    widthEdit->update();
    positionEdit->setEnabled(true);
    positionEdit->update();
    amountEdit->setDisabled(true);
    amountEdit->update();
}



void PageOne::onRowTemplateClicked()
{
    wellPlateRadio->click();
    widthEdit->setValue(12);
    heightEdit->setValue(1);
}


void PageOne::templateTwo()
{
   petriRadio->click();
   widthEdit->setValue(3);
   heightEdit->setValue(3);

}


void PageOne::fillWell()
{
    wellPlateRadio->click();
    widthEdit->setValue(12);
    heightEdit->setValue(8);
}


