/*Comhghall McKeating 12328401
Final Year Project*/

#include "demomode.h"
#include "demoscene.h"
#include "demoview.h"
#include "xmlmanager.h"
#include "QFile"
#include "QTextStream"

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
namespace netanim
{

DemoMode * pDemoMode = 0;

DemoMode *
DemoMode::getInstance()
{
    pDemoMode = new DemoMode;
    return pDemoMode;
}

DemoMode::DemoMode()
{
    init();
}

void
DemoMode::setFocus(bool focus)
{
    if(focus)
    {
        //reload
    }
}

void
DemoMode::setTabName(QString name)
{
    m_tabName = name;
}

QWidget *
DemoMode::getCentralWidget()
{
    return m_centralWidget;
}

QString
DemoMode::getTabName()
{
    return m_tabName;
}

void
DemoMode::init()
{
    m_state = INIT;
    m_hLayout = new QHBoxLayout;
    m_hLayout->addWidget(DemoView::getInstance());
    m_vLayout = new QVBoxLayout;
    m_vLayout->addLayout(m_hLayout);
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_vLayout);

    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);

    //scene->addText("DEMO");
    setWindowTitle("NetAnim");
    parse();
}

void
DemoMode::parse()
{
    DemoScene * scene = DemoScene::getInstance();
    scene->setCanvasBoundaries(m_minPoint, m_maxPoint);
    XmlManager xmlManager;
    QString demoTextFile = m_tabName + "_text.xml";
    QString filename = "/home/comhghall/Final-Year-Project/demos/" + m_tabName + "/" + demoTextFile;
//    QFile xmlFile("/home/comhghall/Final-Year-Project/demos/" + m_tabName + "/" + demoTextFile);
//    xmlManager.writeXmlFile("/home/comhghall/Final-Year-Project/demos/textXmlFile.xml");

    xmlManager.readXmlFile("/home/comhghall/Final-Year-Project/demos/textXmlFile.xml");
    std::vector<QString> strings = xmlManager.getStringVector();
    std::vector<QString> colours = xmlManager.getColourVector();
    std::vector<QString> fonts = xmlManager.getFontVector();
    std::vector<QString> sizes = xmlManager.getSizeVector();
    QPointF pos;
    pos.setX(0 + std::rand() % (101));
    pos.setY(0 + std::rand() % (101));

    for(int i = 0; i != strings.size(); i++){
        std::cout << "WE'RE TRYING.";
        scene->addTextItem(strings.at(i), fonts.at(i), colours.at(i), sizes.at(i), pos);
        scene->addText("test");
    }
}

} //namespace netanim
