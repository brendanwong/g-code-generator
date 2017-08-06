#ifndef WIZARD_H
#define WIZARD_H

#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QStackedWidget>
#include <QMessageBox>

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

    QString output = "";

private slots:
    void doNext();
    void doPrev();
    void saveFormInfo();
    void generateCode();

private:
    QPushButton *next;
    QPushButton *previous;

    QStackedWidget *pages;

    PageOne *pageOne;
    PageTwo *pageTwo;
    PageThree *pageThree;
};

#endif //WIZARD_H

