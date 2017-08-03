#ifndef WIZARD_H
#define WIZARD_H

#include <QWidget>
#include <QCheckBox>
#include <QTextEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDate>
#include <QListWidget>
#include <QWizardPage>
#include <QDialog>

#include "pageone.h"
#include "pagetwo.h"
#include "pagethree.h"

class Wizard : public QDialog
{
    Q_OBJECT

public:
    Wizard();

    QString nameInput;
    int yearInput;
    int monthInput;
    int dayInput;
    int heightInput;
    int widthInput;
    int positionInput;
    int materialInput;

    QString yearString;
    QString monthString;
    QString dayString;

private slots:
    void doNext();
    void doPrev();
    void saveFormInfo();

private:
    QPushButton *next;
    QPushButton *previous;

    QStackedWidget *pages;

    PageOne *pageOne;
    PageTwo *pageTwo;
    PageThree *pageThree;


};

#endif //WIZARD_H

