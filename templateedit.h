#ifndef TEMPLATEEDIT_H
#define TEMPLATEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QMessageBox>
#include <QFormLayout>
#include <QHBoxLayout>

#include "positionedit.h"




class TemplateEdit : public QWidget
{
    Q_OBJECT
public:
    TemplateEdit(QWidget *parent = 0);
    void buildTemplateEdit();
    void buildPrintSelection();

    QLabel *title;
    QWidget *templateEdit;

    QLineEdit *nameEdit;
    QDateEdit *dateEdit;
    QSpinBox *heightEdit;
    QSpinBox *widthEdit;
    PositionEdit *positionEdit;
    QComboBox *materialEdit;
    QSpinBox *amountEdit;
    QLabel *positionGraphic;

    QGroupBox *groupBox;
    QRadioButton *petriRadio;
    QRadioButton *wellPlateRadio;

    bool firstMessage = true;



private slots:
    void onWellPlateRadioClicked();
    void onPetriRadioClicked();
    void positionHoverSlot();
    void leftPositionSlot();

public slots:
    void rowTemplate();
    void gridPetriSlot();
    void gridPlateSlot();
    void wellPlateColumnSlot();
    void fillWellSlot();


};

#endif // TEMPLATEEDIT_H
