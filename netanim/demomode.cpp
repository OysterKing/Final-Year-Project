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
    m_gLayout = new QGridLayout;
    m_textEditor = new QTextEdit;
    m_textEditor->setReadOnly(true);
    m_gLayout->addWidget(m_textEditor, 1, 0);
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_gLayout);
    parse();
    m_textEditor->insertHtml(m_parsedHtml);

    setWindowTitle("NetAnim");
}

void
DemoMode::parse()
{
    QString demoTextFile = m_tabName + "_text.html";
    QFile htmlFile("/home/comhghall/Final-Year-Project/demos/" + m_tabName + "/" + demoTextFile);
    htmlFile.open(QIODevice::ReadOnly);
    QTextStream in(&htmlFile);
    m_parsedHtml = in.readAll();
    htmlFile.close();
}

void
DemoMode::addTextItem(QGraphicsScene * scene, QString string, QString font, QString colour, QString size, QPointF pos)
{
    QGraphicsTextItem * textItem = new QGraphicsTextItem;

    textItem->setPos(pos);
    bool ok = 0;
    QColor textColour;

    QString r = colour.mid(0, 2);
    QString g = colour.mid(2, 2);
    QString b = colour.mid(4, 2);

    qDebug(r.toLatin1());
    qDebug(g.toLatin1());
    qDebug(b.toLatin1());

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
