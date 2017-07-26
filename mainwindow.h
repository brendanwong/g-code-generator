#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class QPushButton;
class QStackedWidget;

class PageOne;
class PageTwo;
class PageThree;

class Wizard : public QDialog
{
  Q_OBJECT

public:
  Wizard();

private slots:
  void doNext();
  void doPrev();

private:
  QPushButton *next;
  QPushButton *previous;

  QStackedWidget *pages;

  PageOne *pageOne;
  PageTwo *pageTwo;
  PageThree *pageThree;
};

#endif //

