#include <QApplication>

#include "mainwindow.h"

int main( int argc, char **argv )
{
  QApplication app( argc, argv );

  Wizard wizardWindow;
  wizardWindow.setMinimumSize(500, 500);
  wizardWindow.show();

  return app.exec();
}
