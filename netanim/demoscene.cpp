/*Comhghall McKeating 12328401
 * Final Year Project */

#include "demoscene.h"
#include "demomode.h"
#include "demoview.h"

namespace netanim
{

DemoScene * pDemoScene = 0;

DemoScene::DemoScene():
    QGraphicsScene(0, 0, 250, 250)
{

}

DemoScene *
DemoScene::getInstance()
{
    if(!pDemoScene){
        std::cout << "\n" << "DECLARED" << "\n";
        pDemoScene = new DemoScene;
    }
    return pDemoScene;
}

void
DemoScene::setCanvasBoundaries(QPointF minPoint, QPointF maxPoint){
    m_minPoint = minPoint;
    m_maxPoint = maxPoint;
    qreal boundaryWidth = m_maxPoint.x() * 0.1;
    qreal boundaryHeight = m_maxPoint.y() * 0.2;
    qreal boundary = qMax(boundaryWidth, boundaryHeight);

    m_sceneMinPoint = QPointF(m_minPoint.x() - boundary, m_minPoint.y() - boundary);
    m_sceneMaxPoint = QPointF(m_maxPoint.x() + boundary, m_maxPoint.y() + boundary);

    //Make it square
    qreal minimum = qMin(m_sceneMinPoint.x (), m_sceneMinPoint.y ());
    m_sceneMinPoint = QPointF (minimum, minimum);
    qreal maximum = qMax (m_sceneMaxPoint.x (), m_sceneMaxPoint.y ());
    m_sceneMaxPoint = QPointF (maximum, maximum);
    if ((m_sceneMaxPoint.x () == 0) && (m_sceneMaxPoint.y () == 0))
      {
        m_sceneMaxPoint = QPointF (1, 1);
      }

    setSceneRect (QRectF (m_sceneMinPoint, m_sceneMaxPoint));
}

QRectF
DemoScene::getBoundaryRect ()
{
  return QRectF (m_sceneMinPoint, m_sceneMaxPoint);
}

void
DemoScene::addTextItem(QString body, QString font, QString colour, QString size, QPointF pos)
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
    textItem->setPlainText(body);
    textItem->setDefaultTextColor(textColour);
    textItem->setFont(serifFont);
    textItem->setVisible(true);

    addItem(textItem);
}

} //namespace netanim
