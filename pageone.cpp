#include "wizard.h"
#include "pageone.h"

PageOne::PageOne(QWidget *parent) : QWidget(parent)
{
    QTabWidget *tabWidget = new QTabWidget(this);

    customTab(tabWidget);
    templateTab(tabWidget);

    tabWidget->setMinimumSize(400,400);
}

void PageOne::customTab(QTabWidget *tabWidget)
{
    nameEdit = new QLineEdit;
    dateEdit = new QDateEdit;
    heightEdit = new QSpinBox;
    widthEdit = new QSpinBox;
    positionEdit = new QSpinBox;
    materialEdit = new QComboBox;
    nextButton = new QPushButton;
    QWizardPage *customWindow = new QWizardPage;

    heightEdit->setRange(1, 8);
    widthEdit->setRange(1, 8);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());
    nextButton->setText("Next");

    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addWidget(nextButton);

    customWindow->setLayout(formLayout);

    tabWidget->addTab(customWindow, "Custom");



    //registerField("nameEdit", nameEdit);



}

void PageOne::templateTab(QTabWidget *tabWidget)
{
    QGridLayout *layout = new QGridLayout;
    QWidget *templateWindow = new QWidget;
    acceptDeal = new QCheckBox( tr("I accept") );
    layout->addWidget( acceptDeal, 1, 1 );
    templateWindow->setLayout(layout);
    tabWidget->addTab(templateWindow, "Template");
}
