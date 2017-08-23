#include "pagetwo.h"
#include "wizard.h"

PageTwo::PageTwo(QWidget *parent) : QWidget(parent)
{
    layout = new QFormLayout( this );
    QLabel *label = new QLabel;
    firstOutput = true;
    label->setText("G-Code Output");
    layout->addWidget(label);
}

void PageTwo::updateOutput(const QString output)
{
    if (firstOutput == true)
    {
        textEdit = new QTextEdit;
        textEdit->setReadOnly(true);
        textEdit->setMinimumSize(300, 280);

        textEdit->setPlaceholderText("Output code should go here");

        textEdit->setText(output);
        layout->addWidget(textEdit);
        firstOutput = false;
    } else
        onNewOutput(output);
    //otherwise, new output box will be created every single time

}

void PageTwo::onNewOutput(QString output)
{

    textEdit->setText(output);
    QApplication::processEvents();
}
