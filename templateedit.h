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


class TemplateEdit : public QWidget
{
    Q_OBJECT
public:
    TemplateEdit(QWidget *parent = 0);
    void buildTemplateEdit();

    QLabel *title;
    QWidget *templateEdit;

    QLineEdit *nameEdit;
    QDateEdit *dateEdit;
    QSpinBox *heightEdit;
    QSpinBox *widthEdit;
    QSpinBox *positionEdit;
    QComboBox *materialEdit;
    QSpinBox *amountEdit;

    QGroupBox *groupBox;
    QRadioButton *petriRadio;
    QRadioButton *wellPlateRadio;

};

#endif // TEMPLATEEDIT_H
