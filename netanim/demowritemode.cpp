/*Comhghall McKeating 12328401
 * Final Year Project.*/

#include "demowritemode.h"
#include "xmlmanager.h"

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
    QGraphicsView * view = new QGraphicsView;
    QGraphicsScene * scene = new QGraphicsScene(0, 0, 250, 250);
    m_gLayout->addWidget(view);
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_gLayout);

    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);

    view->setScene(scene);
}

} //namespace netanim
