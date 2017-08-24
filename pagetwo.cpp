#include "pagetwo.h"
#include "wizard.h"
#include <QFileDialog>

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
        textEdit->setMinimumSize(300, 250);

        textEdit->setPlaceholderText("Output code should go here");

        textEdit->setText(output);
        layout->addWidget(textEdit);
        firstOutput = false;
        QPushButton *exportButton = new QPushButton(tr("Export as Text File"));
        layout->addWidget(exportButton);
        QObject::connect(exportButton, SIGNAL(clicked(bool)), this, SLOT(onExportButtonClicked()));

    } else
        onNewOutput(output);
    //otherwise, new output box will be created every single time
}





void PageTwo::onNewOutput(QString output)
{

    textEdit->setText(output);
    QApplication::processEvents();
}





void PageTwo::onExportButtonClicked()
{
    QString ayylmao = "text.txt";
    ayylmao = QFileDialog::getSaveFileName(this, tr("Export G-Code File"), title);
}





void PageTwo::updateTitle(QString title)
{
    this->title = title;
}
