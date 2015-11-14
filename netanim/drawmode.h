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
    QToolButton * m_addElementButton;
    QToolButton * m_runButton;
    QScrollArea * m_toolbarScrollArea;
    QPointF m_minPoint;
    QPointF m_maxPoint;

    DrawModeState_t m_state;

    DrawMode();
    void init();
    void initControls();
    void initToolbars();
    void initTopToolbar();

private slots:
    void addElementButtonSlot();
    void runButtonSlot();
};
} //namespace netanim

#endif // DRAWMODE_H