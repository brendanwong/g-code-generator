#include "pageone.h"
#include "wizard.h"
#include "templateitem.h"
#include <QScrollArea>


PageOne::PageOne(QWidget *parent) : QWidget(parent)
{
    QTabWidget *tabWidget = new QTabWidget(this);

    customTab(tabWidget);
    templateTab(tabWidget);

    tabWidget->setStyleSheet("QTabWidget::pane {border: 0;}");
    tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected{ color:#ffffff}");

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

    //standard two digit width for uniformity
    heightEdit->setMinimumWidth(42);
    widthEdit->setMinimumWidth(42);
    positionEdit->setMinimumWidth(42);

    heightEdit->setRange(1, 8);
    widthEdit->setRange(1, 8);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
//    materialEdit->setStyleSheet("QComboBox {background-color: white;}");
    dateEdit->setDate(QDate::currentDate());

    buildPrintSelection();

    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Print:", groupBox);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Position:", positionEdit);

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
    QHBoxLayout *layout = new QHBoxLayout;
    QWidget *templateWindow = new QWidget;


    QListWidget *templateWidget = new QListWidget;
    templateWidget->setViewMode(QListWidget::IconMode);
    templateWidget->setMovement(QListWidget::Static);

    buildTemplateItem(templateWidget, "Custom", "/Users/brendanwong/Desktop/custom-template.png");
    buildTemplateItem(templateWidget, "Template 1", "/Users/brendanwong/Desktop/template-1.png");
    buildTemplateItem(templateWidget, "Template 2", "/Users/brendanwong/Desktop/template-2.png");
    buildTemplateItem(templateWidget, "Template 3", "/Users/brendanwong/Desktop/template-3.png");
    buildTemplateItem(templateWidget, "Template 4", "/Users/brendanwong/Desktop/template-4.png");
    buildTemplateItem(templateWidget, "Template 5", "/Users/brendanwong/Desktop/template-5.png");

    layout->addWidget(templateWidget);
    templateWindow->setLayout(layout);
    tabWidget->addTab(templateWindow, "Templates");
}

void PageOne::buildTemplateItem(QListWidget *templateWidget, QString title, QString iconPath)
{
    TemplateItem *item = new TemplateItem;
    item->setText(title);
    QIcon icon(iconPath);
    item->setIcon(icon);
    templateWidget->addItem(item);

//    TemplateItem *item = new TemplateItem;
//    item->setText(title);
//    QVBoxLayout *layout = new QVBoxLayout;
//    QLabel *iconLabel = new QLabel;
//    QPixmap icon(iconPath);
//    icon.setDevicePixelRatio(devicePixelRatio());
//    iconLabel->setPixmap(icon.scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//    layout->addWidget(iconLabel);
//    item->setLayout(layout);
//    templateWidget->addItem(item);


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
}






void PageOne::onPetriRadioClicked()
{
    widthEdit->setRange(1, 8);
    widthEdit->update();
    positionEdit->setEnabled(true);
    positionEdit->update();
}
