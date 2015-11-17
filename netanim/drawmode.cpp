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

    m_addHostButton = new QToolButton;
    m_addHostButton->setToolTip("Add node.");
    m_addHostButton->setText("X");
    m_addHostButton->setCheckable(true);
    connect (m_addHostButton, SIGNAL(clicked()), this, SLOT (addHostButtonSlot()));
    m_topToolBar->addWidget(m_addHostButton);

    m_addSwitchButton = new QToolButton;
    m_addSwitchButton->setToolTip("Add switch.");
    m_addSwitchButton->setText("Y");
    m_addSwitchButton->setCheckable(true);
    connect (m_addSwitchButton, SIGNAL(clicked()), this, SLOT (addSwitchButtonSlot()));
    m_topToolBar->addWidget(m_addSwitchButton);

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
DrawMode::addHostButtonSlot()
{
    if(m_addHostButton->isChecked()){
        m_addSwitchButton->setDisabled(true);
        m_runButton->setDisabled(true);
    }

    else{
        m_addSwitchButton->setEnabled(true);
        m_runButton->setEnabled(true);
    }
    DrawScene::getInstance()->enableMousePositionLabel(m_addHostButton->isChecked());
    DrawScene::getInstance()->enableHostAddition(m_addHostButton->isChecked());
}

void
DrawMode::addSwitchButtonSlot()
{
    if(m_addSwitchButton->isChecked()){
        m_addHostButton->setDisabled(true);
        m_runButton->setDisabled(true);
    }

    else{
        m_addHostButton->setEnabled(true);
        m_runButton->setEnabled(true);
    }
    DrawScene::getInstance()->enableMousePositionLabel(m_addSwitchButton->isChecked());
    DrawScene::getInstance()->enableSwitchAddition(m_addSwitchButton->isChecked());
}

void
DrawMode::runButtonSlot()
{

}
}
