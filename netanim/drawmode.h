/*Comhghall McKeating 12328401
 * Final Year Project*/

#ifndef DRAWMODE_H
#define DRAWMODE_H

#include "common.h"
#include "mode.h"

namespace netanim
{

class DrawMode: public Mode
{
    Q_OBJECT

    typedef enum
    {

    }DrawType_t;

public:
    // Getters
    static DrawMode * getInstance();
    QWidget * getCentralWidget();
    QString getTabName();

    //Setters
    void setFocus(bool focus);
    void systemReset();

private:
    // state
    typedef enum
    {
        INIT,
        READY
    }DrawModeState_t;

    QWidget * m_centralWidget;
    QHBoxLayout * m_hLayout;
    QVBoxLayout * m_vLayout;
    QToolBar * m_topToolBar;
    QToolBar * m_sideToolBar;
    QToolButton * m_addHostButton;
    QToolButton * m_addSwitchButton;
    QToolButton * m_addRouterButton;
    QToolButton * m_saveButton;
    QToolButton * m_addLinkButton;
    QToolButton * m_runButton;
    QToolButton * m_deleteButton;
    QToolButton * m_runBlankModeButton;
    QToolButton * m_runDhcpModeButton;
    QLabel * m_linkFromLabel;
    QLabel * m_linkToLabel;
    QLabel * m_bwLabel;
    QLabel * m_delayLabel;
    QLabel * m_lossLabel;
    QLineEdit * m_linkFromEdit;
    QLineEdit * m_linkToEdit;
    QLineEdit * m_bwEdit;
    QLineEdit * m_delayEdit;
    QLineEdit * m_lossEdit;
    QScrollArea * m_toolbarScrollArea;
    QPointF m_minPoint;
    QPointF m_maxPoint;
    bool m_enableDhcp;
    bool m_enableBlank;
    bool m_enableBasic;

    DrawModeState_t m_state;

    DrawMode();
    void init();
    void initControls();
    void initToolbars();
    void initTopToolbar();
    void initSideToolbar();
    void launchMN();

private slots:
    void addHostButtonSlot();
    void addRouterButtonSlot();
    void addSwitchButtonSlot();
    void saveButtonSlot();
    void addLinkButtonSlot();
    void runButtonSlot();
    void deleteButtonSlot();
    void runBlankModeButtonSlot();
    void runDhcpModeButtonSlot();
};
} //namespace netanim

#endif // DRAWMODE_H
