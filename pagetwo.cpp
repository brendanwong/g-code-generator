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

        textEdit->setPlaceholderText("Output code should go here");
        textEdit->setText(output);

        layout->addWidget(textEdit);

        QWidget *buttonEncapsulator = new QWidget;
        QHBoxLayout *hlayout = new QHBoxLayout;

        QPushButton *exportGC = new QPushButton(tr("Export as G-Code File"));

        exportGC->setMaximumWidth(200);

        hlayout->addWidget(exportGC);
        buttonEncapsulator->setLayout(hlayout);
        layout->addWidget(buttonEncapsulator);

        QObject::connect(exportGC, SIGNAL(clicked(bool)), this, SLOT(onExportGCClicked()));

    } else
        onNewOutput(output);
    //otherwise, new output box will be created every single time
}





void PageTwo::onExportGCClicked()
{
    QString saveDirectory;
    saveDirectory = QFileDialog::getSaveFileName(this, tr("Export G-Code File"), title);
    GCOutput(saveDirectory);
}





void PageTwo::GCOutput(QString directory)
{
    directory += ".gcode";
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
