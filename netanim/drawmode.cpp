/*Comhghall McKeating 12328401
 * Final Year Project*/

#include "animatormode.h"
#include "animatorscene.h"
#include "drawmode.h"
#include "drawview.h"
//#include "drawingconstants.h"

namespace netanim
{

DrawMode * pDrawMode = 0;

DrawMode *
DrawMode::getInstance()
{
    if(!pDrawMode)
    {
        pDrawMode = new DrawMode();
    }
    return pDrawMode;
}

DrawMode::DrawMode()
{
    init();
}

QWidget *
DrawMode::getCentralWidget()
{
    return m_centralWidget;
}

QString
DrawMode::getTabName()
{
    return "Draw";
}

void
DrawMode::init()
{
//    m_state = INIT;
    //DrawView::getInstance()->setScene(InterfaceStatsScene::getInstance());
    m_hLayout = new QHBoxLayout;
    m_vLayout = new QVBoxLayout;
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_vLayout);
    setWindowTitle("NetAnim");
    initControls();
}

void
DrawMode::initControls()
{

}

void
DrawMode::setFocus(bool focus)
{
    if(focus)
    {
        //reload
    }
}

void
DrawMode::systemReset()
{
//    m_state = INIT;
    //perform some form of reset
  //  m_state = READY;
}
}
