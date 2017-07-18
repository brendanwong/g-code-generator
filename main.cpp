#include "mainwindow.h"
#include <QApplication>

void mainWindow(QTabWidget *tabWidget);
void customTab(QWidget *customWindow, QTabWidget *tabWidget);
void templateTab(QWidget *templateTab, QTabWidget *tabWidget);

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);

    QTabWidget *tabWidget = new QTabWidget;

    mainWindow(tabWidget);

    QWidget *customWindow = new QWidget;
    QWidget *templateWindow = new QWidget;

    customTab(customWindow, tabWidget);
    templateTab(templateWindow, tabWidget);



    tabWidget->show();

    return prog.exec();
}
