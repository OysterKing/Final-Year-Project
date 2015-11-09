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
    QToolButton * m_testButton;
    QScrollArea * m_toolbarScrollArea;

    DrawModeState_t m_state;

    DrawMode();
    void init();
    void initControls();
    void initToolbars();
    void initTopToolbar();
};
} //namespace netanim

#endif // DRAWMODE_H
