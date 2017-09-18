#ifndef WIZARD_H
#define WIZARD_H

#include "pageone.h"
#include "pagetwo.h"
#include "link.h"
#include "constants.h"
#include "templateedit.h"

#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QStackedWidget>
#include <QMessageBox>
#include <QMouseEvent>

class Wizard : public QDialog
{
    Q_OBJECT

public:
    Wizard();
    QStackedWidget *pages;


signals:
    void emitOutput(const QString &output);
    void emitTitle(const QString &output);

private slots:
    void doNext();
    void doPrev();
    void saveFormInfo();

private:
    void generatePetriArray();
    void generatePlateArray();
    void buildTitle();
    void buildSideBar(QHBoxLayout *mainLayout);
    void buildSidebarLink(QVBoxLayout *sidebarLayout, QString inLink, QString location, QString inLabel, QString inDescr);
    void addDivider(QVBoxLayout *sidebarLayout);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QPushButton *next;
    QPushButton *previous;
    QPushButton *cancel;

    PageOne *pageOne;
    TemplateEdit *templateEdit;
    PageTwo *pageTwo;

    int x_coord;
    int y_coord;

    QString nameInput;
    QString materialString;
    int yearInput;
    int monthInput;
    int dayInput;
    int heightInput;
    int widthInput;
    int positionInput;
    int materialInput;
    int printType;
    double extrusionAmount;

    QString yearString;
    QString monthString;
    QString dayString;

    QString output;

    int selection = 1;
};

#endif //WIZARD_H
