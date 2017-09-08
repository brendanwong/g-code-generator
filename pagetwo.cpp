#include "pagetwo.h"
#include "wizard.h"

PageTwo::PageTwo(QWidget *parent) : QWidget(parent)
{
    //encapuslating layout widget
    layout = new QVBoxLayout( this );

    //title label
    QLabel *label = new QLabel;
    label->setText("G-Code Output");
    label->setAlignment(Qt::AlignCenter);

    layout->addWidget(label);
}





void PageTwo::updateOutput(const QString output)
{
    this->output = output;

    //firstOutput check to ensure new output text box is not created every time
    if (firstOutput == true)
    {
        //sets firstOutput to false so onNewOutput is called
        firstOutput = false;

        //creates text box and sets to read only so it is not editable but selectable
        textEdit = new QTextEdit;
        textEdit->setReadOnly(true);

        //placeholder just in case
        textEdit->setPlaceholderText("Output code should go here");

        //set text to calculated output
        textEdit->setText(output);

        layout->addWidget(textEdit);

        //creates buttons for file export (only one for now, text export removed)
        QWidget *buttonEncapsulator = new QWidget;
        QHBoxLayout *hlayout = new QHBoxLayout;

        QPushButton *exportGC = new QPushButton(tr("Export as G-Code File"));

        exportGC->setMaximumWidth(200);

        hlayout->addWidget(exportGC);
        buttonEncapsulator->setLayout(hlayout);
        layout->addWidget(buttonEncapsulator);

        //connect button to appropriate slot for functionality
        QObject::connect(exportGC, SIGNAL(clicked(bool)), this, SLOT(onExportGCClicked()));

    } else
        onNewOutput(output);

}





void PageTwo::onExportGCClicked()
{
    //obtains directory and passes it to GCOutput()
    QString saveDirectory;
    saveDirectory = QFileDialog::getSaveFileName(this, tr("Export G-Code File"), title);
    GCOutput(saveDirectory);
}





void PageTwo::GCOutput(QString directory)
{
    //creates file, writes data, and outputs to appropriate directory
    directory += ".gcode";

    QFile file(directory);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);
    out << this->output;

    file.close();
}






void PageTwo::onNewOutput(QString output)
{
    //sets the new output
    textEdit->setText(output);

    //refreshes the text box to show new output
    textEdit->update();
}





void PageTwo::updateTitle(QString title)
{
    this->title = title;
}
