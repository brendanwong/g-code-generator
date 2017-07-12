#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QFormLayout>

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);

    QTabWidget *tabWidget = new QTabWidget;

    QWidget *customWindow = new QWidget;
    QWidget *templateWindow = new QWidget;

    //Window properties
    customWindow->setWindowTitle("G-Code Generator");
    templateWindow->setWindowTitle("Custom G-Code Generator");
    tabWidget->setMinimumSize(500, 300);


    //Label creation
    QLabel *customLabel = new QLabel;
    QLabel *templateLabel = new QLabel;

    //Label text
    customLabel->setText("Custom Print");
    templateLabel->setText("Template tab");

    //Field creation
    QLineEdit *nameEdit = new QLineEdit;
    QDateEdit *dateEdit = new QDateEdit;
    QSpinBox *heightEdit = new QSpinBox;
    QSpinBox *widthEdit = new QSpinBox;
    QSpinBox *positionEdit = new QSpinBox;
    QComboBox *materialEdit = new QComboBox;

    QPushButton *nextCustom = new QPushButton;

    //Constraints/properties
    templateLabel->setAlignment(Qt::Alignment(5));

    customLabel->setAlignment(Qt::Alignment(5));
    heightEdit->setRange(1, 7);
    widthEdit->setRange(1, 7);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());
    nextCustom->setMaximumSize(50, 20);
    nextCustom->setText("Next");

    QFormLayout *formLayout = new QFormLayout;
    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    formLayout->addWidget(customLabel);

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addWidget(nextCustom);

    horizontalLayout->addWidget(templateLabel);

    templateWindow->setLayout(horizontalLayout);
    customWindow->setLayout(formLayout);

    tabWidget->addTab(templateWindow, "Template");
    tabWidget->addTab(customWindow, "Custom");

    //need to add in functionality for closing
    //and frameless dragging  before removal
    //tabWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    tabWidget->show();

    return prog.exec();
}


