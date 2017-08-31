#include <QApplication>
#include "wizard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Wizard wizardWindow;

    app.setWindowIcon(QIcon(":/Resources/se3d-circle-logo.svg"));

    //window adjustments
    wizardWindow.setWindowFlags(Qt::FramelessWindowHint);
    wizardWindow.setMinimumWidth(660);
    //round the window
    QPainterPath path;
    path.addRoundedRect(wizardWindow.rect(), 5, 5);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    wizardWindow.setMask(mask);

    wizardWindow.show();

    return app.exec();
}
