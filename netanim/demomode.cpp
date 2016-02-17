/*Comhghall McKeating 12328401
Final Year Project*/

#include "demomode.h"
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
}

void
DemoMode::displayText()
{
    m_hLayout = new QHBoxLayout;
    QGraphicsView * view = new QGraphicsView;
    QGraphicsScene * scene = new QGraphicsScene(0, 0, 250, 250);
    m_hLayout->addWidget(view);
    m_vLayout = new QVBoxLayout;
    m_vLayout->addLayout(m_hLayout);
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_vLayout);

    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);
    parse();

    QPointF pos;
    pos.setX(std::rand() % 101);
    pos.setY(std::rand() % 101);

    for(int i = 0; i < m_parsedStrings.size(); i++){
        addTextItem(scene, m_parsedStrings.at(i), m_parsedFonts.at(i), m_parsedColours.at(i), m_parsedSizes.at(i), pos);
    }
    //scene->addText("DEMO");
    view->setScene(scene);
    setWindowTitle("NetAnim");
}

void
DemoMode::parse()
{
    XmlManager xmlManager;
    QString demoTextFile = m_tabName + "_text.xml";
    QString filename = "/home/comhghall/Final-Year-Project/demos/" + m_tabName + "/" + demoTextFile;
//    QFile xmlFile("/home/comhghall/Final-Year-Project/demos/" + m_tabName + "/" + demoTextFile);
//    xmlManager.writeXmlFile("/home/comhghall/Final-Year-Project/demos/textXmlFile.xml");

    xmlManager.readXmlFile(filename);
    m_parsedStrings = xmlManager.getStringVector();
    m_parsedColours = xmlManager.getColourVector();
    m_parsedFonts = xmlManager.getFontVector();
    m_parsedSizes = xmlManager.getSizeVector();
}

void
DemoMode::addTextItem(QGraphicsScene * scene, QString string, QString font, QString colour, QString size, QPointF pos)
{
    QGraphicsTextItem * textItem = new QGraphicsTextItem;

    textItem->setPos(pos);
    bool ok = 0;
    QColor textColour;

    QString r = colour.mid(1, 2);
    QString g = colour.mid(3, 4);
    QString b = colour.mid(5, 6);

    int red = r.toUInt(&ok, 16);
    int green = g.toUInt(&ok, 16);
    int blue = b.toUInt(&ok, 16);

    int fontSize = size.toUInt(&ok, 10);
    QFont serifFont(font, fontSize, QFont::Bold);

    textColour.setRed(red);
    textColour.setGreen(green);
    textColour.setBlue(blue);
    textItem->setPlainText(string);
    textItem->setDefaultTextColor(textColour);
    textItem->setFont(serifFont);
    textItem->setVisible(true);

    scene->addItem(textItem);
}

} //namespace netanim
