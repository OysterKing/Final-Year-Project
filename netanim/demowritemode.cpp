/*Comhghall McKeating 12328401
 * Final Year Project.*/

#include "demowritemode.h"
#include "xmlmanager.h"
#include <QTextEdit>

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

    m_gLayout->addWidget(m_textEditor, 1, 0);
    m_gLayout->addWidget(m_saveButton, 2, 1);

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

}

void
DemoWriteMode::addImageButtonSlot()
{

}

} //namespace netanim
