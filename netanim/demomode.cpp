/*Comhghall McKeating 12328401
Final Year Project*/

#include "demomode.h"

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

QWidget *
DemoMode::getCentralWidget()
{
    return m_centralWidget;
}

QString
DemoMode::getTabName()
{
    return "Demo";
}

void
DemoMode::init()
{
    m_state = INIT;
    m_hLayout = new QHBoxLayout;
    m_vLayout = new QVBoxLayout;
    m_centralWidget = new QWidget;
}

} //namespace netanim
