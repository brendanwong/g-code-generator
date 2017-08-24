#include "pagetwo.h"
#include "wizard.h"
#include <QFileDialog>
#include <QTextStream>

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
    this->output = output;
    if (firstOutput == true)
    {
        firstOutput = false;

        textEdit = new QTextEdit;
        textEdit->setReadOnly(true);
        textEdit->setMinimumSize(300, 250);

        textEdit->setPlaceholderText("Output code should go here");
        textEdit->setText(output);

        layout->addWidget(textEdit);

        QPushButton *exportButton = new QPushButton(tr("Export as Text File"));
        layout->addWidget(exportButton);
        QObject::connect(exportButton, SIGNAL(clicked(bool)), this, SLOT(onExportButtonClicked()));
    } else
        onNewOutput(output);
    //otherwise, new output box will be created every single time
}





void PageTwo::onExportButtonClicked()
{
    QString saveDirectory;
    saveDirectory = QFileDialog::getExistingDirectory(this, tr("Export G-Code File"), title);
    //need to connect the save button to preFileIO()
    fileOutput(saveDirectory);


}





void PageTwo::fileOutput(QString directory)
{
       title = directory + "/" +title;
       title += ".txt";
       QFile file(title);
       file.open(QIODevice::WriteOnly | QIODevice::Text);
       QTextStream out(&file);
       out << this->output;
       file.close();

}





void PageTwo::onNewOutput(QString output)
{

    textEdit->setText(output);
    QApplication::processEvents();
}





void PageTwo::updateTitle(QString title)
{
    this->title = title;
}
