#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void mainWindow(QTabWidget *tabWidget)
{
    tabWidget->setMinimumSize(500, 300);

}

void customTab(QWidget *customWindow, QTabWidget *tabWidget)
{
    QLabel *customLabel = new QLabel;
    customLabel->setText("Custom Print");

    QLineEdit *nameEdit = new QLineEdit;
    QDateEdit *dateEdit = new QDateEdit;
    QSpinBox *heightEdit = new QSpinBox;
    QSpinBox *widthEdit = new QSpinBox;
    QSpinBox *positionEdit = new QSpinBox;
    QComboBox *materialEdit = new QComboBox;
    QPushButton *nextCustom = new QPushButton;

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

    formLayout->addWidget(customLabel);

    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addWidget(nextCustom);

    customWindow->setLayout(formLayout);

    tabWidget->addTab(customWindow, "Custom");


}

void templateTab(QWidget *templateWindow, QTabWidget *tabWidget)
{
    QLabel *templateLabel = new QLabel;
    templateLabel->setText("Template tab");
    QPushButton *quitButton = new QPushButton;
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    templateLabel->setAlignment(Qt::Alignment(5));

    QHBoxLayout *templateLayout = new QHBoxLayout;

    templateLayout->addWidget(templateLabel);
    templateLayout->addWidget(quitButton);

    templateWindow->setLayout(templateLayout);

    tabWidget->addTab(templateWindow, "Template");

}
