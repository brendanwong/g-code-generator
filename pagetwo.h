#ifndef PAGETWO_H
#define PAGETWO_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>

class PageTwo : public QWidget
{
    Q_OBJECT
public:
    PageTwo(QWidget *parent = 0);

private slots:
    void updateOutput(const QString output);
    void onNewOutput(QString output);
    void onExportButtonClicked();
    void updateTitle(QString title);
    void fileOutput(QString directory);

private:
    QFormLayout *layout;
    QTextEdit *textEdit;
    bool firstOutput;
    QString title;
    QString output;
};

#endif // PAGETWO_H
