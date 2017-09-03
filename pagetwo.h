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
    void updateTitle(QString title);
    void updateOutput(const QString output);
    void onNewOutput(QString output);
    void onExportTextClicked();
    void onExportGCClicked();

private:
    QVBoxLayout *layout;
    QTextEdit *textEdit;
    bool firstOutput;
    QString title;
    QString output;

    void textOutput(QString directory);
    void GCOutput(QString directory);


};

#endif // PAGETWO_H
