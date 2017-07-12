#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);

    QWidget *mainWindow = new QWidget;

    mainWindow->setWindowTitle("G-Code Generator");

    //label creation
    QLabel *titleLabel = new QLabel; //lineEdit
    QLabel *nameLabel = new QLabel;     //lineEdit
    QLabel *dateLabel = new QLabel; //dateEdit
    QLabel *heightLabel = new QLabel;   //spinbox 1-7
    QLabel *widthLabel = new QLabel;    //spinbox 1-7
    QLabel *positionLabel = new QLabel; //spinbox 1-4
    QLabel *materialLabel = new QLabel; //comboBox 3

    titleLabel->setText("G-Code Generator");
    nameLabel->setText("Name:");
    dateLabel->setText("Date:");
    heightLabel->setText("Height:");
    widthLabel->setText("Width:");
    positionLabel->setText("Position:");
    materialLabel->setText("Material:");

    //data edit
    QLineEdit *nameEdit = new QLineEdit;
    QDateEdit *dateEdit = new QDateEdit;
    QSpinBox *heightEdit = new QSpinBox;
    QSpinBox *widthEdit = new QSpinBox;
    QSpinBox *positionEdit = new QSpinBox;
    QComboBox *materialEdit = new QComboBox;

    //Constraints
    heightEdit->setRange(1, 7);
    widthEdit->setRange(1, 7);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());


    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(titleLabel);


    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);

    layout->addWidget(dateLabel);
    layout->addWidget(dateEdit);

    layout->addWidget(heightLabel);
    layout->addWidget(heightEdit);

    layout->addWidget(widthLabel);
    layout->addWidget(widthEdit);

    layout->addWidget(positionLabel);
    layout->addWidget(positionEdit);

    layout->addWidget(materialLabel);
    layout->addWidget(materialEdit);


    mainWindow->setLayout(layout);

    mainWindow->show();





    return prog.exec();
}
