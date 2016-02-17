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
    void displayText();

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
    QPointF m_minPoint;
    QPointF m_maxPoint;
    std::vector<QString> m_parsedStrings;
    std::vector<QString> m_parsedFonts;
    std::vector<QString> m_parsedColours;
    std::vector<QString> m_parsedSizes;

    DemoModeState_t m_state;

    DemoMode();
    void init();
    void parse();
    void addTextItem(QGraphicsScene * scene, QString string, QString font, QString colour, QString size, QPointF pos);

};
} //namespace netanim

#endif // DEMOMODE_H
