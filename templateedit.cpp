#include "templateedit.h"

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
    title->setText("Template Edit");
    title->setAlignment(Qt::AlignCenter);
    heightEdit->setRange(PETRI_MIN, PETRI_MAX);
    widthEdit->setRange(PETRI_MIN, PETRI_MAX);
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

    //to enable mouse tracking and pop up for bed pos
    positionEdit->setAttribute(Qt::WA_Hover);
    positionEdit->setMouseTracking(true);

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

    //build reference graphic for positions, set hidden by default
    positionGraphic = new QLabel;
    positionGraphic->hide();

    //set frameless and non intrusive
    positionGraphic->setWindowFlag(Qt::FramelessWindowHint);
    positionGraphic->setAttribute(Qt::WA_ShowWithoutActivating);

    connect(positionEdit, SIGNAL(positionHoverSignal()), this, SLOT(positionHoverSlot()));
    connect(positionEdit, SIGNAL(leftPositionSignal()), this, SLOT(leftPositionSlot()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(title);

    layout->addLayout(formLayout);
    templateEdit->setLayout(layout);
}




void TemplateEdit::buildPrintSelection()
{
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

    QObject::connect(wellPlateRadio, SIGNAL(clicked(bool)), this, SLOT(onWellPlateRadioClicked()));
    QObject::connect(petriRadio, SIGNAL(clicked(bool)), this, SLOT(onPetriRadioClicked()));
}


void TemplateEdit::onWellPlateRadioClicked()
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


void TemplateEdit::onPetriRadioClicked()
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

void TemplateEdit::rowTemplate()
{
    title->setText("Row Print Template");

    wellPlateRadio->click();
    widthEdit->setValue(12);
    heightEdit->setValue(1);

    petriRadio->setDisabled(true);
    wellPlateRadio->setDisabled(true);
    widthEdit->setDisabled(true);
    heightEdit->setDisabled(true);
}

void TemplateEdit::gridPetriSlot()
{
    title->setText("3x3 Petri Template");

    petriRadio->click();
    widthEdit->setValue(3);
    heightEdit->setValue(3);

    petriRadio->setDisabled(true);
    wellPlateRadio->setDisabled(true);
    widthEdit->setDisabled(true);
    heightEdit->setDisabled(true);
}

void TemplateEdit::fillWellSlot()
{
    title->setText("Fill Well Plate Template");

    wellPlateRadio->click();
    widthEdit->setValue(12);
    heightEdit->setValue(8);

    petriRadio->setDisabled(true);
    wellPlateRadio->setDisabled(true);
    widthEdit->setDisabled(true);
    heightEdit->setDisabled(true);

}

void TemplateEdit::gridPlateSlot()
{
    title->setText("3x3 Well Plate Template");

    wellPlateRadio->click();
    widthEdit->setValue(3);
    heightEdit->setValue(3);

    petriRadio->setDisabled(true);
    wellPlateRadio->setDisabled(true);
    widthEdit->setDisabled(true);
    heightEdit->setDisabled(true);
}


void TemplateEdit::wellPlateColumnSlot()
{
    title->setText("Well Plate Column Template");

    wellPlateRadio->click();
    widthEdit->setValue(1);
    heightEdit->setValue(8);

    petriRadio->setDisabled(true);
    wellPlateRadio->setDisabled(true);
    widthEdit->setDisabled(true);
    heightEdit->setDisabled(true);
}


void TemplateEdit::positionHoverSlot()
{
    QPoint globalPos = positionEdit->mapToGlobal(QPoint(0,0));

    int x = globalPos.x();
    int y = globalPos.y();

    x += OFFSET;
    positionGraphic->move(x, y);

    if(petriRadio->isChecked())
    {
        QPixmap icon("://resources/petri-template.png");
        icon.setDevicePixelRatio(devicePixelRatio());
        positionGraphic->setPixmap(icon.scaled(HOVER_GRAPHIC_DIMS, HOVER_GRAPHIC_DIMS,
                                               Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if(wellPlateRadio->isChecked())
    {
        QPixmap icon("://resources/well-plate-template.png");
        icon.setDevicePixelRatio(devicePixelRatio());
        positionGraphic->setPixmap(icon.scaled(HOVER_GRAPHIC_DIMS, HOVER_GRAPHIC_DIMS,
                                               Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    positionGraphic->show();
    positionGraphic->update();
}



//when positionEdit is no longer in focus, remove graphic
void TemplateEdit::leftPositionSlot()
{
    positionGraphic->hide();
    positionGraphic->update();
}
