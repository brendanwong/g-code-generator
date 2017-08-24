#ifndef PAGETWO_H
#define PAGETWO_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QApplication>

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

private:
    QFormLayout *layout;
    QTextEdit *textEdit;
    bool firstOutput;
    QString title;
};

#endif // PAGETWO_H
