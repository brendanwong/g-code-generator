#include "pagetwo.h"
#include "wizard.h"

PageTwo::PageTwo(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout( this );
    QLabel *label = new QLabel;
    firstOutput = true;

    label->setText("G-Code Output");
    label->setAlignment(Qt::AlignCenter);
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
        textEdit->setMinimumSize(300, 270);

        textEdit->setPlaceholderText("Output code should go here");
        textEdit->setText(output);

        layout->addWidget(textEdit);

        QWidget *buttonEncapsulator = new QWidget;
        QHBoxLayout *hlayout = new QHBoxLayout;

        QPushButton *exportText = new QPushButton(tr("Export as Text File"));
        QPushButton *exportNC = new QPushButton(tr("Export as .nc File"));

        hlayout->addWidget(exportText);
        hlayout->addWidget(exportNC);
        buttonEncapsulator->setLayout(hlayout);
        layout->addWidget(buttonEncapsulator);

        QObject::connect(exportText, SIGNAL(clicked(bool)), this, SLOT(onExportTextClicked()));
        QObject::connect(exportNC, SIGNAL(clicked(bool)), this, SLOT(onExportNCClicked()));

    } else
        onNewOutput(output);
    //otherwise, new output box will be created every single time
}






void PageTwo::onExportTextClicked()
{
    QString saveDirectory;
    saveDirectory = QFileDialog::getSaveFileName(this, tr("Export G-Code File"), title);
    textOutput(saveDirectory);
}






void PageTwo::textOutput(QString directory)
{
    directory += ".txt";
    QFile file(directory);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << this->output;
    file.close();
}





void PageTwo::onExportNCClicked()
{
    QString saveDirectory;
    saveDirectory = QFileDialog::getSaveFileName(this, tr("Export G-Code File"), title);
    NCOutput(saveDirectory);
}





void PageTwo::NCOutput(QString directory)
{
    directory += ".nc";
    QFile file(directory);
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
