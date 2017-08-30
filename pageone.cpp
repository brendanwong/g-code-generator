#include "pageone.h"
#include "wizard.h"

PageOne::PageOne(QWidget *parent) : QWidget(parent)
{
    QTabWidget *tabWidget = new QTabWidget(this);

    customTab(tabWidget);
    templateTab(tabWidget);

    tabWidget->setStyleSheet("QTabWidget::pane {border: 0;}");

    tabWidget->setMinimumSize(400, 400);
}





void PageOne::customTab(QTabWidget *tabWidget)
{
    nameEdit = new QLineEdit;
    dateEdit = new QDateEdit;
    heightEdit = new QSpinBox;
    widthEdit = new QSpinBox;
    positionEdit = new QSpinBox;
    materialEdit = new QComboBox;
    QWidget *customWindow = new QWidget;

    heightEdit->setRange(1, 8);
    widthEdit->setRange(1, 8);

    //standard two digit input width for uniformity in print type switching
    widthEdit->setMinimumWidth(42);
    heightEdit->setMinimumWidth(42);
    positionEdit->setMinimumWidth(42);

    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());

    printGroup = new QGroupBox;
    petriRadio = new QRadioButton(tr("Petri Dish"));
    wellPlateRadio = new QRadioButton(tr("Well Plate"));

    petriRadio->setAutoExclusive(true);
    wellPlateRadio->setAutoExclusive(true);
    petriRadio->setChecked(true); //default selection

    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(petriRadio);
    groupBoxLayout->addWidget(wellPlateRadio);
    groupBoxLayout->setContentsMargins(0,0,0,0);
    printGroup->setLayout(groupBoxLayout);
    printGroup->setStyleSheet("border: 0");

    QObject::connect(petriRadio, SIGNAL(clicked(bool)), this, SLOT(onPetriRadioSelected()));
    QObject::connect(wellPlateRadio, SIGNAL(clicked(bool)), this, SLOT(onWellPlateSelected()));


    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", printGroup);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Material:", materialEdit);

    customWindow->setLayout(formLayout);
    tabWidget->addTab(customWindow, "Custom");
}





void PageOne::templateTab(QTabWidget *tabWidget)
{
    QHBoxLayout *layout = new QHBoxLayout;
    QWidget *templateWindow = new QWidget;
    QTextEdit *edit = new QTextEdit;
    layout->addWidget(edit);
    edit->setMinimumSize(300,280);
    templateWindow->setLayout(layout);
    tabWidget->addTab(templateWindow, "Templates");
}




void PageOne::onWellPlateSelected()
{
    if (firstMessage == true)
    {
        QMessageBox wellPlateWarning;
        wellPlateWarning.setText("Please note that this software currently only "
                                "supports the Greiner 650161 well plate");
        wellPlateWarning.exec();
        firstMessage = false;
        //display warning once
    }
    widthEdit->setRange(1, 12);
    widthEdit->repaint();
}

void PageOne::onPetriRadioSelected()
{
    widthEdit->setRange(1, 8);
    widthEdit->repaint();
}
