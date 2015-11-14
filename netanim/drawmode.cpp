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

    m_addElementButton = new QToolButton;
    m_addElementButton->setToolTip("Add node.");
    m_addElementButton->setText("X");
    m_addElementButton->setCheckable(true);
    connect (m_addElementButton, SIGNAL(clicked()), this, SLOT (addElementButtonSlot()));
    m_topToolBar->addWidget(m_addElementButton);

    m_runButton = new QToolButton;
    m_runButton->setToolTip("Run.");
    m_runButton->setText("A");
    connect (m_runButton, SIGNAL(clicked()), this, SLOT (runButtonSlot()));
    m_topToolBar->addWidget(m_runButton);
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
DrawMode::addElementButtonSlot()
{
    DrawScene::getInstance()->enableMousePositionLabel(m_addElementButton->isChecked());
    DrawScene::getInstance()->enableElementAddition(m_addElementButton->isChecked());
}

void
DrawMode::runButtonSlot()
{

}
}
