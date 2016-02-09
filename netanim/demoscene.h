/*Comhghall McKeating 12328401
 * Final Year Project*/

#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "common.h"

namespace netanim
{

class DemoScene : public QGraphicsScene
{
    Q_OBJECT

public:
    static DemoScene * getInstance();
    DemoScene();
    QRectF getBoundaryRect();
    void setCanvasBoundaries(QPointF minPoint, QPointF maxPoint);

private:
    QPointF m_minPoint;
    QPointF m_maxPoint;
    QPointF m_sceneMinPoint;
    QPointF m_sceneMaxPoint;

};

} //namespace netanim

#endif // DEMOSCENE_H
