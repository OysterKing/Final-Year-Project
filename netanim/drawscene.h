/*Comhghall McKeating 12328401
 * Final Year Project*/

#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include "common.h"

namespace netanim
{

class DrawScene : public QGraphicsScene
{
    Q_OBJECT
public:
    static DrawScene * getInstance();
    DrawScene();
    void addGrid();
//    void setGridLinesCount(int nGridLines);
    QRectF getBoundaryRect();
    void setCanvasBoundaries(QPointF minPoint, QPointF maxPoint);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//    void addNode(qreal x, qreal y);
    void enableMousePositionLabel(bool show);
    void enableNodeAddition(bool enable);
    void enableSwitchAddition(bool enable);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

private:
    typedef QVector <QGraphicsLineItem *>          LineItemVector_t;
    typedef QVector <QGraphicsSimpleTextItem*> GridCoordinatesVector_t;
    qreal m_gridStep;
    bool m_showGrid;
    int m_nGridLines;
    LineItemVector_t             m_gridLines;
    GridCoordinatesVector_t m_gridCoordinates;
    QLabel * m_mousePositionLabel;
    QLabel * m_elementLabel;
    QGraphicsProxyWidget * m_mousePositionProxyWidget;
//    QGraphicsWidget * m_elementWidget;
    bool m_enableMousePositionLabel;
    bool m_enableNodeAddition;
    bool m_enableSwitchAddition;
    QPointF m_minPoint;
    QPointF m_maxPoint;
    QPointF m_sceneMinPoint;
    QPointF m_sceneMaxPoint;

    void markGridCoordinates();
    void initGridCoordinates();
    QVector <QGraphicsSimpleTextItem*> getGridCoordinatesItems();
    void setMousePositionLabel(QPointF pos);
    void showMousePositionLabel(bool show);
    void addNode(QPointF pos);
    void addSwitch(QPointF pos);

};

} // namespace netanim

#endif // DRAWSCENE_H
