#include <QApplication>
#include "wizard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Wizard wizardWindow;

    wizardWindow.setWindowFlags(Qt::FramelessWindowHint);
    wizardWindow.setMinimumSize(650, 400);


//    wizardWindow.setAttribute(Qt::WA_TranslucentBackground, true);

    wizardWindow.show();


    return app.exec();
}
