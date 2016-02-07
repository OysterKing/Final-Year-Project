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
    void enableDelete(bool enable);
    void addLink(QString from, QString to, QString bw, QString d, QString l);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    int getNumHosts();
    int getNumSwitches();
    int getNumNodes();
    std::map<QString, QString> getLinkedNodesMap();
    std::vector<QString> getHostVector();
    std::vector<QString> getSwitchVector();
    std::map<QString, QString> getHostIpMap();
    std::map<QString, QString> getHostMacMap();
    std::map<QString, int> getHostSysIdMap();
    std::map<QString, QPointF> getHostLocMap();
    std::map<QString, QString> getSwitchMacMap();
    std::map<QString, int> getSwitchSysIdMap();
    std::map<QString, QPointF> getSwitchLocMap();
    std::vector<QString> getLinksVector();
    std::vector<QString> getLinkOptsVector();

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
    bool m_enableDelete;
    QPointF m_minPoint;
    QPointF m_maxPoint;
    QPointF m_sceneMinPoint;
    QPointF m_sceneMaxPoint;
    std::map<QString, QString> m_linkedNodesMap;
    std::map<QString, int> m_hostSysIdsMap;
    std::map<QString, int> m_switchSysIdsMap;
    std::map<QString, QString> m_hostIpMap;
    std::map<QString, QString> m_hostMacMap;
    std::map<QString, QString> m_switchMacMap;
    std::map<QString, QPointF> m_hostLocMap;
    std::map<QString, QPointF> m_switchLocMap;
    std::vector<QString> m_linksVector;
    std::vector<QString> m_hostVector;
    std::vector<QString> m_switchVector;
    std::vector<QString> m_linkOptsVector;

    void markGridCoordinates();
    void initGridCoordinates();
    QVector <QGraphicsSimpleTextItem*> getGridCoordinatesItems();
    void setMousePositionLabel(QPointF pos);
    void showMousePositionLabel(bool show);
    void addHost(QPointF pos);
    void addSwitch(QPointF pos);
    void deleteNode(QPointF pos);
};

} // namespace netanim

#endif // DRAWSCENE_H
