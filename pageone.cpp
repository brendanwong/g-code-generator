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

    QGroupBox *groupBox = new QGroupBox;
    QRadioButton *petriRadio = new QRadioButton(tr("Petri Dish"));
    QRadioButton *wellPlateRadio = new QRadioButton(tr("Well Plate"));
    petriRadio->setAutoExclusive(true);
    wellPlateRadio->setAutoExclusive(true);
    petriRadio->setChecked(true); //default selected
    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(petriRadio);
    groupBoxLayout->addWidget(wellPlateRadio);
    groupBox->setLayout(groupBoxLayout);


    heightEdit->setRange(1, 8);
    widthEdit->setRange(1, 8);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());
    groupBox->setStyleSheet("QGroupBox::pane {border: 0;}");

    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", groupBox);
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
