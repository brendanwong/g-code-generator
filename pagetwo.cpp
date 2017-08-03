#include "pagetwo.h"
#include "wizard.h"

PageTwo::PageTwo(QWidget *parent) : QWidget(parent)
{
    QFormLayout *layout = new QFormLayout( this );
    QLabel *label = new QLabel;

    label->setText("THIS is the output. it is selectable");
    layout->addWidget(label);

    displayOutput(layout);
}

void PageTwo::displayOutput(QFormLayout *layout)
{
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    textEdit->setPlaceholderText("code should go here");

    QString hola;

    textEdit->setText("not yet");

    layout->addWidget(textEdit);
}
