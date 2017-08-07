#include "pagetwo.h"
#include "wizard.h"


PageTwo::PageTwo(QWidget *parent) : QWidget(parent)
{
    layout = new QFormLayout( this );
    QLabel *label = new QLabel;

    label->setText("THIS is the output. it is selectable");
    layout->addWidget(label);


}

void PageTwo::onNewOutput(const QString output)
{
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    textEdit->setPlaceholderText("code should go here");

    textEdit->setText(output);

    layout->addWidget(textEdit);
}

