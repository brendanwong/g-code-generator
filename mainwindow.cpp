#include <QWidget>
#include <QCheckBox>
#include <QTextEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDate>

#include <QListWidget>
#include "mainwindow.h"

class PageOne : public QWidget
{
public:
    PageOne( QWidget *parent = 0 );
    void customTab(QTabWidget *tabWidget);
    void templateTab(QTabWidget *tabWidget);

    QCheckBox *acceptDeal;
    QLabel *customLabel;
    QLineEdit *nameEdit;
    QDateEdit *dateEdit;
    QSpinBox *heightEdit;
    QSpinBox *widthEdit;
    QSpinBox *positionEdit;
    QComboBox *materialEdit;
    QPushButton *nextButton;
    QWidget *customWindow;


};

PageOne::PageOne( QWidget *parent ) : QWidget(parent)
{
    QTabWidget *tabWidget = new QTabWidget(this);

    customTab(tabWidget);
    templateTab(tabWidget);

    tabWidget->setMinimumSize(400,400);


}

void PageOne::customTab(QTabWidget *tabWidget)
{


    nameEdit = new QLineEdit;
    dateEdit = new QDateEdit;
    heightEdit = new QSpinBox;
    widthEdit = new QSpinBox;
    positionEdit = new QSpinBox;
    materialEdit = new QComboBox;
    nextButton = new QPushButton;
    customWindow = new QWidget;

    heightEdit->setRange(1, 8);
    widthEdit->setRange(1, 8);
    positionEdit->setRange(1, 4);
    materialEdit->addItem("Calcium Carbonate");
    materialEdit->addItem("HPR");
    materialEdit->addItem("ABTS");
    dateEdit->setDate(QDate::currentDate());
    nextButton->setText("Next");

    QFormLayout *formLayout = new QFormLayout;


    formLayout->addRow("&Name:", nameEdit);
    formLayout->addRow("&Date:", dateEdit);
    formLayout->addRow("&Height:", heightEdit);
    formLayout->addRow("&Width:", widthEdit);
    formLayout->addRow("&Position:", positionEdit);
    formLayout->addRow("&Material:", materialEdit);
    formLayout->addWidget(nextButton);

    customWindow->setLayout(formLayout);

    tabWidget->addTab(customWindow, "Custom");
}

void PageOne::templateTab(QTabWidget *tabWidget)
{
    QGridLayout *layout = new QGridLayout;
    QWidget *templateWindow = new QWidget;
    acceptDeal = new QCheckBox( tr("I accept") );
    layout->addWidget( acceptDeal, 1, 1 );
    templateWindow->setLayout(layout);
    tabWidget->addTab(templateWindow, "Template");
}



class PageTwo : public QWidget
{
public:
    PageTwo( QWidget *parent = 0 );

    QCheckBox *doThis;
    QCheckBox *doThat;
    QCheckBox *extra;
};

PageTwo::PageTwo( QWidget *parent ) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout( this );

    doThis = new QCheckBox( tr("Do this") );
    doThat = new QCheckBox( tr("Do that") );
    extra = new QCheckBox( tr("Add something extra") );

    layout->addWidget( doThis, 0, 0 );
    layout->addWidget( doThat, 1, 0 );
    layout->addWidget( extra, 2, 0 );

    layout->setRowMinimumHeight( 3, 0 );
}



class PageThree : public QWidget
{
public:
    PageThree( QWidget *parent = 0 );
};

PageThree::PageThree( QWidget *parent ) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout( this );

    layout->addWidget( new QLabel( tr("All is ready. Press finish to get it done!") ), 0, 0 );
}



Wizard::Wizard() : QDialog()
{
    QGridLayout *layout = new QGridLayout( this );

    QPushButton *cancel = new QPushButton( tr("Cancel") );
    next = new QPushButton( tr("Next") );
    previous = new QPushButton( tr("Previous" ) );

    pages = new QStackedWidget();

    layout->addWidget( pages, 0, 0, 1, 5 );
    layout->setColumnMinimumWidth( 0, 50 );
    layout->addWidget( previous, 1, 1 );
    layout->addWidget( next, 1, 2 );
    layout->setColumnMinimumWidth( 3, 5 );
    layout->addWidget( cancel, 1, 4 );

    previous->setEnabled( false );
    next->setEnabled( false );

    connect( next, SIGNAL(clicked()), this, SLOT(doNext()) );
    connect( previous, SIGNAL(clicked()), this, SLOT(doPrev()) );
    connect( cancel, SIGNAL(clicked()), this, SLOT(reject()) );

    pages->addWidget(pageOne = new PageOne(pages));
    pages->addWidget(pageTwo = new PageTwo(pages));
    pages->addWidget(pageThree = new PageThree(pages));

    connect(pageOne->acceptDeal, SIGNAL(toggled(bool)), next, SLOT(setEnabled(bool)));
}

void Wizard::doNext()
{
    switch( pages->currentIndex() )
    {
      case 0:
        previous->setEnabled( true );
        disconnect( pageOne->acceptDeal, SIGNAL(toggled(bool)), next, SLOT(setEnabled(bool)) );
        break;
    case 1:
        next->setText( tr("Finish") );
        break;
    case 2:
        QMessageBox::information( this, tr("Finishing"), tr("Here is where the action takes place.") );
        accept();
        return;
    }

    pages->setCurrentIndex( pages->currentIndex()+1 );
}

void Wizard::doPrev()
{
    switch( pages->currentIndex() )
    {
      case 1:
        previous->setEnabled( false );
        next->setEnabled( pageOne->acceptDeal->isChecked() );

        connect( pageOne->acceptDeal, SIGNAL(toggled(bool)), next, SLOT(setEnabled(bool)) );

        break;
      case 2:
        next->setText( tr("Next") );

        break;
    }

    pages->setCurrentIndex( pages->currentIndex()-1 );
}

