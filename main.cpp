#include <QApplication>
#include "wizard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Wizard wizardWindow;

    wizardWindow.setWindowFlags(Qt::FramelessWindowHint);
    wizardWindow.setMinimumSize(600, 425);
    wizardWindow.show();

    return app.exec();
}
