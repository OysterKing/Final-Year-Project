/*Comhghall McKeating 12328401
 * Final Year Project*/

#include "drawscene.h"
#include "drawmode.h"
#include "drawview.h"
#include "dlink.h"
#include "dnode.h"
#include "logqt.h"
using namespace std;

namespace netanim
{

DrawScene * pDrawScene = 0;

DrawScene::DrawScene():
    QGraphicsScene(0, 0, 250, 250),
    m_enableMousePositionLabel(false),
    m_enableSwitchAddition(false),
    m_enableHostAddition(false),
    m_numHosts(0),
    m_numSwitches(0),
    m_numNodes(0)
{
    m_mousePositionLabel = new QLabel("");
    m_mousePositionLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mousePositionProxyWidget = addWidget (m_mousePositionLabel, Qt::ToolTip);
    m_mousePositionProxyWidget->setFlag (QGraphicsItem::ItemIgnoresTransformations);
    m_nGridLines = 50;
    m_showGrid = true;
//    m_linkedNodesMap = new std::map<QString, QString>;
//    m_hostVector = new std::vector<QString>;
//    m_switchVector = new std::vector<QString>;

    initGridCoordinates();
}

DrawScene *
DrawScene::getInstance()
{
    if(!pDrawScene)
    {
        pDrawScene = new DrawScene;
    }
    return pDrawScene;
}

QVector <QGraphicsSimpleTextItem *>
DrawScene::getGridCoordinatesItems()
{
    return m_gridCoordinates;
}

void
DrawScene::initGridCoordinates()
{
    for(int i = 0; i < m_gridCoordinates.size(); i++){
        QGraphicsSimpleTextItem * item = m_gridCoordinates[i];
        removeItem(item);
        delete item;
    }

    m_gridCoordinates.clear();
    for(int i = 0; i < 9; i++){ //only 9 coordinates will be marked
        QGraphicsSimpleTextItem * item = new QGraphicsSimpleTextItem;
        item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        m_gridCoordinates.push_back(item);
        addItem(item);
    }
    markGridCoordinates();
}

void
DrawScene::setCanvasBoundaries(QPointF minPoint, QPointF maxPoint){
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

void
DrawScene::enableMousePositionLabel(bool enable)
{
    m_enableMousePositionLabel = enable;
}

void
DrawScene::enableHostAddition(bool enable)
{
    m_enableHostAddition = enable;
}

void
DrawScene::enableSwitchAddition(bool enable)
{
    m_enableSwitchAddition = enable;
}

void
DrawScene::enableLinkAddition(bool enable)
{
    m_enableLinkAddition = enable;
}

int
DrawScene::getNumHosts()
{
    return m_numHosts;
}

int
DrawScene::getNumSwitches()
{
    return m_numSwitches;
}

int
DrawScene::getNumNodes()
{
    return m_numNodes;
}

std::map<QString, QString>
DrawScene::getLinkedNodesMap()
{
    return m_linkedNodesMap;
}

std::vector<QString>
DrawScene::getHostVector()
{
    return m_hostVector;
}

std::vector<QString>
DrawScene::getSwitchVector()
{
    return m_switchVector;
}

std::map<QString, QString>
DrawScene::getHostIpMap()
{
    return m_hostIpMap;
}

std::map<QString, QString>
DrawScene::getHostMacMap()
{
    return m_hostMacMap;
}

std::map<QString, QPointF>
DrawScene::getHostLocMap()
{
    return m_hostLocMap;
}

std::map<QString, QString>
DrawScene::getSwitchMacMap()
{
    return m_switchMacMap;
}

std::map<QString, QPointF>
DrawScene::getSwitchLocMap()
{
    return m_switchLocMap;
}

std::map<QString, int>
DrawScene::getSwitchSysIdMap()
{
    return m_switchSysIdsMap;
}

std::map<QString, int>
DrawScene::getHostSysIdMap()
{
    return m_hostSysIdsMap;
}

std::vector<QString>
DrawScene::getLinksVector()
{
    return m_linksVector;
}

void
DrawScene::setMousePositionLabel (QPointF pos)
{
  QString string = "    (" + QString::number ( (pos.x ())) + "," + QString::number ( (pos.y ())) + ")";

  m_mousePositionLabel->setText (string);
  m_mousePositionProxyWidget->setPos (pos.x (), pos.y ());
  m_mousePositionLabel->adjustSize ();

}

void
DrawScene::addHost(QPointF pos)
{
    int hostNumber = getNumHosts();
    int nodeNumber = getNumNodes();
    QString description = "Host";
    QString ip = "10.0.0.";
    QString mac = "00:00:00:00:00:";
    dNode * drawnode = 0;
    drawnode = dNodeMgr::getInstance()->add(hostNumber, nodeNumber, pos.x(), pos.y(), description);
    drawnode->setSize(50, 50);
    ip = ip + QString::number(hostNumber + 1);
    mac = mac + QString::number(nodeNumber);
    drawnode->addIpv4Address(ip);
    drawnode->addMacAddress(mac);

    QString hostInfo = "h." + QString::number(hostNumber);

    QGraphicsTextItem * hostLabel = new QGraphicsTextItem;
    hostLabel->setPos(pos);
    hostLabel->setPlainText(hostInfo);

    m_hostVector.push_back(hostInfo);
    m_hostSysIdsMap.insert(std::pair<QString, int> (hostInfo, nodeNumber));
    m_hostIpMap.insert(std::pair<QString, QString> (hostInfo, ip));
    m_hostMacMap.insert(std::pair<QString, QString> (hostInfo, mac));
    m_hostLocMap.insert(std::pair<QString, QPointF> (hostInfo, pos));

    m_numNodes += 1;
    m_numHosts += 1;
    DrawScene::getInstance()->addItem(drawnode);
    DrawScene::getInstance()->addItem(hostLabel);
}

void
DrawScene::addSwitch(QPointF pos)
{
    int switchNumber = getNumSwitches();
    int nodeNumber = getNumNodes();
    QString string = "Switch";
    QString mac = "00:00:00:00:00:";
    dNode * drawnode = 0;
    drawnode = dNodeMgr::getInstance()->add(switchNumber, nodeNumber, pos.x(), pos.y(), string);
    drawnode->setSize(100, 100);
    drawnode->setColor(0, 255, 0);
    mac = mac + QString::number(nodeNumber);
    drawnode->addMacAddress(mac);

    QString switchInfo = "s." + QString::number(switchNumber);

    QGraphicsTextItem * switchLabel = new QGraphicsTextItem;
    switchLabel->setPos(pos);
    switchLabel->setPlainText(switchInfo);

    m_switchVector.push_back(switchInfo);
    m_switchSysIdsMap.insert(std::pair<QString, int> (switchInfo, nodeNumber));
    m_switchMacMap.insert(std::pair<QString, QString> (switchInfo, mac));
    m_switchLocMap.insert(std::pair<QString, QPointF> (switchInfo, pos));

    m_numNodes += 1;
    m_numSwitches += 1;
    DrawScene::getInstance()->addItem(drawnode);
    DrawScene::getInstance()->addItem(switchLabel);
}

void
DrawScene::addLink(QString toString, QString fromString)
{
    uint32_t fromNodeSysId;
    uint32_t toNodeSysId;
    QString to = toString;
    QString from = fromString;
    QString linkDescription = from + " -> " + to;
    QString bandwidth = "100";
    QString loss = "0";
    QString delay = "0";
    QString maxQueueSize = "1000";

    m_linksVector.push_back(to + " " + from);

    if(from.at(0) == 'h'){
        fromNodeSysId = m_hostSysIdsMap.find(from)->second;
    }

    else if(to.at(0) == 'h'){
        toNodeSysId = m_switchSysIdsMap.find(to)->second;
    }

    if(from.at(0) == 's'){
        fromNodeSysId = m_switchSysIdsMap.find(from)->second;
    }

    if(to.at(0) == 's'){
        toNodeSysId = m_switchSysIdsMap.find(to)->second;
    }

    dLink * drawlink = 0;
    drawlink = dLinkManager::getInstance()->addLink(fromNodeSysId, toNodeSysId, from, to, linkDescription, bandwidth,
                                                    loss, delay, maxQueueSize, true);
    DrawScene::getInstance()->addItem(drawlink);

}

void
DrawScene::showMousePositionLabel (bool show)
{
  m_mousePositionProxyWidget->setVisible (show);
}

void
DrawScene::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  if (m_enableMousePositionLabel)
    {
      QPointF scenePos = event->scenePos ();
    //   QString s = "Mouse:" + QString::number (event->scenePos ().x ()) + "," + QString::number (event->scenePos ().y ());
    //   qDebug (s.toAscii ().data ());
      setMousePositionLabel (scenePos);
      if ((scenePos.x () < 0) ||
          (scenePos.y () < 0))
        {
          showMousePositionLabel (false);
        }
      else
        {
          showMousePositionLabel (true);
        }
    }
  return QGraphicsScene::mouseMoveEvent (event);
}

void
DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_enableHostAddition){
        QPointF scenePos = event->scenePos();
        if((scenePos.x () > 0) && (scenePos.y () > 0)){
            addHost(scenePos);
        }
    }

    else if(m_enableSwitchAddition){
        QPointF scenePos = event->scenePos();
        if((scenePos.x () > 0) && (scenePos.y () > 0)){
            addSwitch(scenePos);
        }
    }
    return QGraphicsScene::mousePressEvent(event);
}

void
DrawScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_enableLinkAddition){
//        QList<QGraphicsItem*> items = DrawScene::items();
//        QPointF scenePos = event->scenePos();
//        for(int i = 0; i < items.size(); i++){
//            QPointF itemPos = items.at(i)->pos();
//            if(euclideanDistance(scenePos, itemPos) <)
//        }

    }
}

void
DrawScene::markGridCoordinates(){
    QRectF simulationRect(m_minPoint, m_maxPoint);
    if((simulationRect.width() == 0) && (simulationRect.height() == 0)){
        return;
    }
    int i = 0;
    for(qreal x = 0; x <= simulationRect.right(); x = x + simulationRect.right()/2){
        for(qreal y = 0; y <= simulationRect.bottom () ; y = y + (simulationRect.bottom ()/2)){
            if (i == 9)
              return;
            QString text = QString::number (x, 'f', 1)
                           + ","
                           + QString::number (y, 'f', 1);
            m_gridCoordinates[i]->setText (text);
            m_gridCoordinates[i]->setPos (QPointF (x, y));
            m_gridCoordinates[i]->setVisible (m_showGrid);
            i++;
        }
    }
}

void
DrawScene::addGrid(){
    m_showGrid = true;
    qreal maximum = qMax (m_maxPoint.x (), m_maxPoint.y ());
    QRectF gridRect (QPointF (0, 0), QPointF (maximum, maximum));
    qreal xStep = (gridRect.right ())/ (m_nGridLines-1);
    qreal yStep = (gridRect.bottom ())/ (m_nGridLines-1);
    //xStep = ceil (xStep);
    //yStep = ceil (yStep);
    QPen pen (QColor (100, 100, 155, 125));
    pen.setCosmetic (true);

    // draw horizontal grid
    qreal y = 0;
    qreal x = 0;
    for (int c = 0; c < m_nGridLines; ++c, y += yStep)
      {
        m_gridLines.push_back (addLine (0, y, gridRect.right (), y, pen));
      }
    // now draw vertical grid
    for (int c = 0; c < m_nGridLines; ++c, x += xStep)
      {
        m_gridLines.push_back (addLine (x, 0, x,  gridRect.bottom (), pen));
      }
    initGridCoordinates ();
    markGridCoordinates ();
}

QRectF
DrawScene::getBoundaryRect ()
{
  return QRectF (m_sceneMinPoint, m_sceneMaxPoint);
}

//void
//DrawScene::setGridLinesCount(int nGridLines){
//    m_nGridLines = nGridLines;
//    bool showGrid = m_showGrid;
//    resetGrid ();
//    m_showGrid = showGrid;
//    if (m_showGrid)
//      {
//        addGrid ();
//      }
//    update ();
//}

}
