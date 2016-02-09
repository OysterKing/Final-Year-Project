/*Comhghall McKeating 12328401
Final Year Project*/

#include "demomode.h"
#include "demoscene.h"
#include "demoview.h"

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
namespace netanim
{

DemoMode * pDemoMode = 0;

DemoMode *
DemoMode::getInstance()
{
    pDemoMode = new DemoMode;
    return pDemoMode;
}

DemoMode::DemoMode()
{
    init();
}

void
DemoMode::setFocus(bool focus)
{
    if(focus)
    {
        //reload
    }
}

void
DemoMode::setTabName(QString name)
{
    m_tabName = name;
}

QWidget *
DemoMode::getCentralWidget()
{
    return m_centralWidget;
}

QString
DemoMode::getTabName()
{
    return m_tabName;
}

void
DemoMode::init()
{
    m_state = INIT;
    m_hLayout = new QHBoxLayout;
    m_hLayout->addWidget(DemoView::getInstance());
    m_vLayout = new QVBoxLayout;
    m_centralWidget = new QWidget;
    m_vLayout->addLayout(m_hLayout);
    m_centralWidget->setLayout(m_vLayout);

    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);
    DemoScene::getInstance()->setCanvasBoundaries(m_minPoint, m_maxPoint);
    setWindowTitle("NetAnim");
}

} //namespace netanim
