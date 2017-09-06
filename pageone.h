#ifndef PAGEONE_H
#define PAGEONE_H

#include <QWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QWizardPage>
#include <QDate>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidget>
#include <QListWidgetItem>

class PageOne : public QWidget
{
    Q_OBJECT
public:
    PageOne(QWidget *parent = 0);

    QLabel *customLabel;
    QLineEdit *nameEdit;

    QDateEdit *dateEdit;
    QSpinBox *heightEdit;
    QSpinBox *widthEdit;
    QSpinBox *positionEdit;
    QComboBox *materialEdit;
    QGroupBox *groupBox;
    QSpinBox *amountEdit;


    QRadioButton *petriRadio;
    QRadioButton *wellPlateRadio;
    QTabWidget *tabWidget;

    bool firstMessage = true;

private:
    void customTab(QTabWidget *tabWidget);
    void templateTab(QTabWidget *tabWidget);
    void buildPrintSelection();
    void buildCustomTemplate(QHBoxLayout *hlayout, QString title, QString iconPath);
    void buildTemplateItem(QHBoxLayout *hlayout, QString title, QString iconPath, const char *slot);


private slots:
    void onWellPlateRadioClicked();
    void onPetriRadioClicked();
    void onRowTemplateClicked();
    void templateTwo();
    void fillWell();

};

#endif //PAGEONE_H
