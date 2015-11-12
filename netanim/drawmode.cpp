/*Comhghall McKeating 12328401
 * Final Year Project*/

#include "animatormode.h"
#include "animatorscene.h"
#include "drawmode.h"
#include "drawview.h"
#include "drawscene.h"
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
    m_state = INIT;
//    DrawView::getInstance()->setScene(InterfaceStatsScene::getInstance());
    initToolbars();
    m_hLayout = new QHBoxLayout;
//    m_hLayout->addWidget(m_toolbarScrollArea);
    m_hLayout->addWidget(DrawView::getInstance());

    m_vLayout = new QVBoxLayout;
    m_vLayout->addWidget(m_topToolBar);
    m_vLayout->addSpacing(0);
    m_vLayout->addLayout(m_hLayout);
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_vLayout);
    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);
    DrawScene::getInstance()->setCanvasBoundaries(m_minPoint, m_maxPoint);
    DrawScene::getInstance()->addGrid();
    setWindowTitle("NetAnim");

    initControls();
}

void
DrawMode::initControls()
{

}

void
DrawMode::initToolbars()
{
    initTopToolbar();
}

void
DrawMode::initTopToolbar()
{
    m_topToolBar = new QToolBar;
    m_testButton = new QToolButton;
    m_testButton->setToolTip("TEST");
    m_testButton->setText("X");
    connect (m_testButton, SIGNAL(clicked()), this, SLOT (testButtonSlot()));
    m_topToolBar->addWidget(m_testButton);
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
    m_state = INIT;
    //perform some form of reset
    m_state = READY;
}

void
DrawMode::testButtonSlot()
{
 //
}
}
