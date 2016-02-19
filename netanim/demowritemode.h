/*Comhghall McKeating 12328401
 * Final Year Project. */

#ifndef DEMOWRITEMODE_H
#define DEMOWRITEMODE_H

#include "common.h"
#include "mode.h"

namespace netanim
{


class DemoWriteMode: public Mode
{
    Q_OBJECT

    typedef enum
    {

    }DemoWriteType_t;

public:
    //getters
    static DemoWriteMode * getInstance();
    QWidget * getCentralWidget();
    QString getTabName();

    //setters
    void setFocus(bool focus);
    void setTabName(QString name);
    void systemReset();
    void displayText();

private:
    //State
    typedef enum
    {
        INIT,
        READY
    }DemoWriteModeState_t;

    //Widgets etc.
    QWidget * m_centralWidget;
    QGridLayout * m_gLayout;
    QString m_tabname;
    QPointF m_minPoint;
    QPointF m_maxPoint;

    DemoWriteModeState_t m_state;

    DemoWriteMode();
    void init();
};

} //namespace netanim

#endif // DEMOWRITEMODE_H
