#include "templateedit.h"
#include <QHBoxLayout>
#include <QFormLayout>

TemplateEdit::TemplateEdit(QWidget *parent) : QWidget(parent)
{
    templateEdit = new QWidget(this);

    buildTemplateEdit();
}


void TemplateEdit::buildTemplateEdit()
{
    title = new QLabel;
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
    title->setText("Template Edit");
    title->setAlignment(Qt::AlignCenter);
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

    groupBox = new QGroupBox;
    petriRadio = new QRadioButton(tr("Petri Dish"));
    wellPlateRadio = new QRadioButton(tr("Well Plate"));

    petriRadio->setAutoExclusive(true);
    wellPlateRadio->setAutoExclusive(true);

    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(petriRadio);
    groupBoxLayout->addWidget(wellPlateRadio);
    groupBox->setLayout(groupBoxLayout);
    groupBox->setStyleSheet("border: 0");
    groupBoxLayout->setContentsMargins(0, 0, 0, 0);


    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", groupBox);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addRow("&Rows:", heightEdit);
    formLayout->addRow("&Columns:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Extrusion Amount (μl):", amountEdit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(title);

    layout->addLayout(formLayout);
    templateEdit->setLayout(layout);

}
