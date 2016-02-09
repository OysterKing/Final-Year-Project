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
    pDemoScene = new DemoScene;
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

} //namespace netanim
