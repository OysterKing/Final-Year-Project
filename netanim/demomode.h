/*COmhghall McKeating 12328401
 * Final Year Project.*/

#ifndef DEMOMODE_H
#define DEMOMODE_H

#include "common.h"
#include "mode.h"

namespace netanim
{

class DemoMode: public Mode
{
    Q_OBJECT

    typedef enum
    {

    }DemoType_t;

public:
    //getters
    static DemoMode * getInstance();
    QWidget * getCentralWidget();
    QString getTabName();

    //setters
    void setFocus(bool focus);
    void setTabName(QString name);
    void systemReset();

private:
    //state
    typedef enum
    {
        INIT,
        READY
    }DemoModeState_t;

    //widgets etc.
    QWidget * m_centralWidget;
    QHBoxLayout * m_hLayout;
    QVBoxLayout * m_vLayout;
    QString m_tabName;


    DemoModeState_t m_state;

    DemoMode();
    void init();

};
} //namespace netanim

#endif // DEMOMODE_H
