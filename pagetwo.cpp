#include "pagetwo.h"
#include "wizard.h"


PageTwo::PageTwo(QWidget *parent) : QWidget(parent)
{
    layout = new QFormLayout( this );
    QLabel *label = new QLabel;

    label->setText("G-Code Output");
    layout->addWidget(label);
}

void PageTwo::onNewOutput(const QString output)
{
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setMinimumSize(300, 300);
    textEdit->setPlaceholderText("Output code should go here");

    textEdit->setText(output);
    layout->addWidget(textEdit);
}

