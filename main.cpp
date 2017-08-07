#include <QApplication>
#include "wizard.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    Wizard wizardWindow;

    wizardWindow.setMinimumSize(500, 400);
    wizardWindow.show();

    return app.exec();
}
