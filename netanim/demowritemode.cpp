/*Comhghall McKeating 12328401
 * Final Year Project.*/

#include "demowritemode.h"
#include "xmlmanager.h"
#include <QTextEdit>
#include <sys/stat.h>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace netanim
{

DemoWriteMode * pDemoWriteMode = 0;

DemoWriteMode *
DemoWriteMode::getInstance()
{
    pDemoWriteMode = new DemoWriteMode;
    return pDemoWriteMode;
}

DemoWriteMode::DemoWriteMode()
{
    init();
}

void
DemoWriteMode::setFocus(bool focus)
{
    if(focus)
    {
        //reload
    }
}

QString
DemoWriteMode::getTabName()
{
    return "+";
}

void
DemoWriteMode::setTabName(QString name)
{
    m_tabname = name;
}

QWidget *
DemoWriteMode::getCentralWidget()
{
    return m_centralWidget;
}

void
DemoWriteMode::init()
{
    m_state = INIT;
    m_gLayout = new QGridLayout;
    m_textEditor = new QTextEdit;

    m_saveButton = new QToolButton;
    m_saveButton->setText("SAVE");
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveButtonSlot()));

    m_filenameEdit = new QLineEdit;

    QLabel * filenameEditLabel = new QLabel;
    filenameEditLabel->setText("DEMO NAME:");

    m_gLayout->addWidget(m_textEditor, 1, 0);
    m_gLayout->addWidget(m_saveButton, 4, 0);
    m_gLayout->addWidget(filenameEditLabel, 2, 0);
    m_gLayout->addWidget(m_filenameEdit, 3, 0);

    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_gLayout);

    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);
    setWindowTitle("NetAnim");
}

void
DemoWriteMode::saveButtonSlot()
{
    XmlManager xmlManager;
    QString text = m_textEditor->toPlainText();
    QString demoName = "D_" + m_filenameEdit->text();
    QString xmlTextName = demoName + "_text.xml";

    QString fullDirPath = "/home/comhghall/Final-Year-Project/demos/" + demoName;
    QString fullWritepath = fullDirPath + "/" + xmlTextName;
    const char * stdDirPath = fullDirPath.toStdString().c_str();

    mkdir(stdDirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    qDebug(text.toLatin1());
    xmlManager.writeXmlFile(fullWritepath, text);
}

void
DemoWriteMode::addImageButtonSlot()
{

}

} //namespace netanim
