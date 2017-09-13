#ifndef PAGEONE_H
#define PAGEONE_H

#include "positionedit.h"

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

#include <QDebug>

class PageOne : public QWidget
{
    Q_OBJECT
public:
    PageOne();
    PageOne(QWidget *parent = 0);

    QLabel *customLabel;
    QLineEdit *nameEdit;

    QDateEdit *dateEdit;
    QSpinBox *heightEdit;
    QSpinBox *widthEdit;
    PositionEdit *positionEdit;
    QComboBox *materialEdit;
    QGroupBox *groupBox;
    QSpinBox *amountEdit;

    QRadioButton *petriRadio;
    QRadioButton *wellPlateRadio;
    QTabWidget *tabWidget;

    QLabel *positionGraphic;

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
    void gridPetriClicked();
    void gridPlateClicked();
    void fillWellClicked();
    void wellPlateColumnClicked();
    void positionHoverSlot();
    void leftPositionSlot();


signals:
    void rowTemplateSignal();
    void gridPetriSignal();
    void fillWellSignal();
    void gridPlateSignal();
    void wellPlateColumnSignal();
    void nextPage();


};

#endif //PAGEONE_H
