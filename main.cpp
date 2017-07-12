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

    QWidget *mainWindow = new QWidget;

    //Window properties
    mainWindow->setWindowTitle("GCG Splash");
    mainWindow->setMinimumSize(600, 400);

    //Label creation
    QLabel *titleLabel = new QLabel;

    //Label text
    titleLabel->setText("G-Code Generator");

    //Field creation
    QLineEdit *nameEdit = new QLineEdit;
    QDateEdit *dateEdit = new QDateEdit;
    QSpinBox *heightEdit = new QSpinBox;
    QSpinBox *widthEdit = new QSpinBox;
    QSpinBox *positionEdit = new QSpinBox;
    QComboBox *materialEdit = new QComboBox;

    QPushButton *nextButton = new QPushButton;

    //Constraints/properties
    titleLabel->setAlignment(Qt::Alignment(5));
    heightEdit->setRange(1, 7);
    widthEdit->setRange(1, 7);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());
    nextButton->setMaximumSize(50, 20);
    nextButton->setText("Next");

    QFormLayout *formLayout = new QFormLayout;

    formLayout->addWidget(titleLabel);


    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Name:", materialEdit);

    mainWindow->setLayout(formLayout);
    mainWindow->show();

    return prog.exec();
}
