#ifndef WIZARD_H
#define WIZARD_H

#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QStackedWidget>
#include <QMessageBox>
#include <QMouseEvent>

#include "pageone.h"
#include "pagetwo.h"
#include "link.h"

class Wizard : public QDialog
{
    Q_OBJECT

public:
    Wizard();

private slots:
    void doNext();
    void doPrev();
    void saveFormInfo();

private:
    void generateCode();
    void buildSideBar(QHBoxLayout *mainLayout);
    void buildSidebarLink(QVBoxLayout *sidebarLayout, QString inLink, QString location, QString inLabel, QString inDescr);
    void addDivider(QVBoxLayout *sidebarLayout);

signals:
    void emitOutput(const QString &output);

private:
    QStackedWidget *pages;
    QPushButton *next;
    QPushButton *previous;
    QPushButton *cancel;

    PageOne *pageOne;
    PageTwo *pageTwo;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

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

    QString output;
};

#endif //WIZARD_H
