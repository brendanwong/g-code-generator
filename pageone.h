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

private:
    void customTab(QTabWidget *tabWidget);
    void templateTab(QTabWidget *tabWidget);
};

#endif //PAGEONE_H
