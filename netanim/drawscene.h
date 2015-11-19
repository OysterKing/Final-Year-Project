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
    void enableHostAddition(bool enable);
    void enableSwitchAddition(bool enable);
    void enableLinkAddition(bool enable);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    int getNumHosts();
    int getNumSwitches();
    int getNumNodes();

private:
    typedef QVector <QGraphicsLineItem *>          LineItemVector_t;
    typedef QVector <QGraphicsSimpleTextItem*> GridCoordinatesVector_t;
    qreal m_gridStep;
    bool m_showGrid;
    int m_nGridLines;
    int m_numHosts;
    int m_numSwitches;
    int m_numNodes;
    LineItemVector_t             m_gridLines;
    GridCoordinatesVector_t m_gridCoordinates;
    QLabel * m_mousePositionLabel;
    QLabel * m_elementLabel;
    QGraphicsProxyWidget * m_mousePositionProxyWidget;
    bool m_enableMousePositionLabel;
    bool m_enableHostAddition;
    bool m_enableSwitchAddition;
    bool m_enableLinkAddition;
    QPointF m_minPoint;
    QPointF m_maxPoint;
    QPointF m_sceneMinPoint;
    QPointF m_sceneMaxPoint;

    void markGridCoordinates();
    void initGridCoordinates();
    QVector <QGraphicsSimpleTextItem*> getGridCoordinatesItems();
    void setMousePositionLabel(QPointF pos);
    void showMousePositionLabel(bool show);
    void addHost(QPointF pos);
    void addSwitch(QPointF pos);
    void addLink(QPointF fromPos, QPointF toPos);
};

} // namespace netanim

#endif // DRAWSCENE_H
