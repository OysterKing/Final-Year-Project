/*Comhghall McKeating 12328401
 * FInal Year Project*/

#include "dnode.h"
#include "drawview.h"
#include <QColor>

namespace netanim
{

dNodeMgr * pdNodeMgr = 0;

dNode::dNode(uint32_t nodeId, uint32_t nodeSysId, qreal x, qreal y, QString nodeDescription):
    m_nodeDescription(0),
    m_nodeId(nodeId),
    m_nodeSysId(nodeSysId),
    m_x(x),
    m_y(y),
    m_showNodeId (true),
    m_showNodeSysId (false),
    m_resourceId (-1)
//    m_showNodeTrajectory (false),
//    m_showBatteryCapcity (false)
{
    setZValue (DNODE_ZVALUE);
    m_r = 255;
    m_g = 0;
    m_b = 0;
    if (nodeDescription == "")
      {
        nodeDescription = QString::number (nodeId);
      }
    m_nodeDescription = new QGraphicsTextItem (nodeDescription);
    m_nodeDescription->setFlag (QGraphicsItem::ItemIgnoresTransformations);
    setFlag (QGraphicsItem::ItemIsSelectable);
}

dNode::~dNode()
{
    if (m_nodeDescription)
      {
        delete m_nodeDescription;
      }
}

void
dNode::showNodeId (bool show)
{
  m_showNodeId = show;
  m_nodeDescription->setVisible (m_showNodeId);
}

QColor
dNode::generateColor (size_t index, uint8_t alpha)
{

  static const size_t colors[] =
    { Qt::blue, Qt::magenta, Qt::darkCyan, Qt::darkYellow, Qt::darkRed, Qt::darkMagenta, Qt::darkGreen, Qt::darkBlue,
    Qt::black, Qt::darkGray, Qt::lightGray };
  static const size_t COUNT = sizeof (colors) / sizeof (size_t);
  QColor result;

  if (index < COUNT)
    result = QColor (Qt::GlobalColor (colors[index]));
  else
    {
      result = QColor (Qt::GlobalColor (colors[index % COUNT]));
      const int step = 256 * 3 % COUNT;

      result.setRed ((result.red () + step * index) % 255);
      result.setGreen ((result.blue () + step * index) % 255);
      result.setBlue (abs ((int)result.green () - step * index) % 255);
    }
  if (alpha)
    result.setAlpha (alpha);

  return result;
}

void
dNode::showNodeSysId (bool show)
{
  if (show)
    {
      m_lastColor = this->getColor ();
      int r, g, b, a;
      m_lastColor.getRgb(&r, &g, &b, &a);
      const QColor &color = generateColor (m_nodeSysId, a);
      color.getRgb (&r, &g, &b, &a);
      setColor (static_cast<uint8_t> (r), static_cast<uint8_t> (g), static_cast<uint8_t> (b), static_cast<uint8_t> (a));
    }
  else
    {
      if(m_showNodeSysId)
    {
      int r, g, b, a;
      m_lastColor.getRgb (&r, &g, &b, &a);
      setColor (r, g, b, a);
    }
    }
  m_showNodeSysId = show;
  m_nodeDescription->setPlainText (QString::number (m_nodeId) + (m_showNodeSysId ? QString(" SysId:") +
  QString::number (m_nodeSysId): QString()));
}

bool
dNode::isVisibleNodeSysId() const
{
  return m_showNodeSysId;
}

void
dNode::updateNodeSysId (uint32_t sysId, bool show)
{
  m_nodeSysId = sysId;
  //m_nodeSysIdDescription->setPlainText ("sysId: " + QString::number (sysId));
  showNodeSysId (show);
}

uint32_t
dNode::getUint32CounterValue (uint32_t counterId, bool & result)
{
  result = false;
  if (m_counterIdToValuesUint32.find (counterId) == m_counterIdToValuesUint32.end ())
    return -1;
  result = true;
  return m_counterIdToValuesUint32[counterId];
}

qreal
dNode::getDoubleCounterValue (uint32_t counterId, bool & result)
{
  result = false;
  if (m_counterIdToValuesDouble.find (counterId) == m_counterIdToValuesDouble.end ())
    return -1;
  result = true;
  return m_counterIdToValuesDouble[counterId];
}

void
dNode::updateCounter (uint32_t counterId, qreal counterValue, CounterType_t counterType)
{
  if (counterType == DOUBLE_COUNTER)
    {
      m_counterIdToValuesDouble[counterId] = counterValue;
    }

  if (counterType == UINT32_COUNTER)
    {
      m_counterIdToValuesUint32[counterId] = counterValue;
    }
}

void
dNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//    Item::mouseDoubleClickEvent(event);
//    if(!m_linked)
//    {
//        m_linked = true;
//        update();
//    }

//    else
//    {
//        m_linked = false;
//        update();
//    }
}

//int
//dNode::getResourceId ()
//{
//  return m_resourceId;
//}


//void
//dNode::setResource (int resourceId)
//{
//  m_resourceId = resourceId;
//  QString resourcePath = AnimResourceManager::getInstance ()->get (resourceId);
  //NS_LOG_DEBUG ("Res:" << resourcePath.toAscii ().data ());
//  QPixmap pix;
//  if (resourcePath.endsWith (".png"))
//    pix = QPixmap (resourcePath, "png");
//  else if (resourcePath.endsWith (".svg"))
//    pix = QPixmap (resourcePath, "svg");
//  setPixmap (pix);
//  update ();
//}

void
dNode::setColor (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
{
  m_r = r;
  m_g = g;
  m_b = b;
  m_alpha = alpha;
  Item::setColor (r, g, b, alpha);
  update ();
}

QColor
dNode::getColor ()
{
  QColor c (m_r, m_g, m_b, 255);
  return c;
}

qreal
dNode::getWidth ()
{
  return m_width;
}

qreal
dNode::getX ()
{
  return m_x;
}

qreal
dNode::getY ()
{
  return m_y;
}


void
dNode::setPos (qreal x, qreal y)
{
  m_x = x;
  m_y = y;
  QGraphicsItem::setPos (x, y);
}

void
dNode::setX (qreal x)
{
  m_x = x;
}

void
dNode::setY (qreal y)
{
  m_y = y;
}

uint32_t
dNode::getNodeId ()
{
  return m_nodeId;
}

uint32_t
dNode::getNodeSysId ()
{
  return m_nodeSysId;
}

QGraphicsTextItem *
dNode::getDescription ()
{
  return m_nodeDescription;
}

QPointF dNode::getCenter ()
{
  //return sceneBoundingRect ().center ();
  return QPointF (m_x, m_y);
}

void dNode::setNodeDescription (QString description)
{
  m_nodeDescription->setPlainText (description);
}

void dNode::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Item::paint (painter, option, widget);
//      updateBatteryCapacityImage (m_showBatteryCapcity);
//      QPointF bottomLeft = sceneBoundingRect ().bottomLeft ();
      //NS_LOG_DEBUG ("Pix Width:" << m_batteryPixmap->width());
//      bottomLeft = QPointF (-1, 1);
//      painter->save ();
//      painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing | QPainter::NonCosmeticDefaultPen, true);      painter->scale (0.5, 1);
//      painter->drawPixmap (bottomLeft.x (), bottomLeft.y (), 1, 1, m_batteryPixmap);

//      painter->restore ();
}

dNode::Ipv4Vector_t
dNode::getIpv4Addresses ()
{
  return m_ipv4Vector;
}

dNode::MacVector_t
dNode::getMacAddresses ()
{
  return m_macVector;
}

void
dNode::addIpv4Address (QString ip)
{
  m_ipv4Vector.push_back (ip);
}

void
dNode::addMacAddress (QString mac)
{
  m_macVector.push_back (mac);
}

bool
dNode::hasIpv4 (QString ip)
{
  bool result = false;
  QStringList quads = ip.split (".");
  if (quads.count () == 4)
    {
      if (quads.at (3) == "255")
        return true;
      for (Ipv4Vector_t::const_iterator i = m_ipv4Vector.begin ();
          i != m_ipv4Vector.end ();
          ++i)
        {
          if (*i == ip)
            {
              //QDEBUG (ip);
              return true;
            }
        }
    }

  return result;
}

bool
dNode::hasMac (QString mac)
{
  bool result = false;
  QStringList bytes = mac.split (":");
  if (bytes.count () == 6)
    {
      for (MacVector_t::const_iterator i = m_macVector.begin ();
          i != m_macVector.end ();
          ++i)
        {
          if (*i == mac)
            {
              return true;
            }
        }
    }

  return result;
}

dNodeMgr::dNodeMgr ():
  m_minX (0),
  m_minY (0),
  m_maxX (0),
  m_maxY (0)
{

}

dNodeMgr * dNodeMgr::getInstance ()
{
  if (!pdNodeMgr)
    {
      pdNodeMgr = new dNodeMgr;
    }
  return pdNodeMgr;
}

dNode * dNodeMgr::add (uint32_t nodeId, uint32_t nodeSysId, qreal x, qreal y, QString nodeDescription)
{
  if (m_nodes.find (nodeId) != m_nodes.end ())
    {
      //NS_FATAL_ERROR ("NodeId:" << nodeId << " Already exists");
    }
  QPixmap pix (":/resources/ns3logo2.png","png");
  dNode * node = new dNode (nodeId, nodeSysId, x, y, nodeDescription);
  node->setPos (x, y);
  //node->setPixmap (pix);
  m_nodes[nodeSysId] = node;
  m_minX = qMin (m_minX, x);
  m_minY = qMin (m_minY, y);
  m_maxX = qMax (m_maxX, x);
  m_maxY = qMax (m_maxY, y);

  return node;
}

void
dNodeMgr::setSize (qreal width, qreal height)
{
  for (NodeIddNodeMap_t::const_iterator i = m_nodes.begin ();
      i != m_nodes.end ();
      ++i)
    {
      dNode * drawNode = i->second;
      drawNode->setSize (width, height);
    }
}

dNode * dNodeMgr::getNode (uint32_t nodeSysId)
{
  return m_nodes[nodeSysId];
}

uint32_t
dNodeMgr::getCount ()
{
  return m_nodes.size ();
}


QPointF
dNodeMgr::getMinPoint ()
{
  return QPointF (m_minX, m_minY);
}

QPointF
dNodeMgr::getMaxPoint ()
{
  qreal m = qMax (m_maxX, m_maxY);
  return QPointF (m, m);
}

void
dNodeMgr::systemReset ()
{
  m_nodes.clear ();
  m_minX = 0;
  m_minY = 0;
  m_maxX = 0;
  m_maxY = 0;
  m_counterIdToNamesDouble.clear ();
  m_counterIdToNamesUint32.clear ();
}

void
dNodeMgr::addIpv4Address (uint32_t nodeId, QString ip)
{
  getNode (nodeId)->addIpv4Address (ip);
}

void
dNodeMgr::addMacAddress (uint32_t nodeId, QString mac)
{
  getNode (nodeId)->addMacAddress (mac);
}

void
dNodeMgr::showNodeId (bool show)
{
  for (NodeIddNodeMap_t::const_iterator i = m_nodes.begin ();
      i != m_nodes.end ();
      ++i)
    {
      dNode * drawNode = i->second;
      drawNode->showNodeId (show);
    }

}

void
dNodeMgr::showNodeSysId (bool show)
{
  for (NodeIddNodeMap_t::const_iterator i = m_nodes.begin ();
      i != m_nodes.end ();
      ++i)
    {
      dNode * drawNode = i->second;
      drawNode->showNodeSysId (show);
    }
}

dNodeMgr::TimePosVector_t
dNodeMgr::getPositions (uint32_t nodeId)
{
  return m_nodePositions[nodeId];
}

void
dNodeMgr::addAPosition (uint32_t nodeId, qreal t, QPointF pos)
{
  if (m_nodePositions.find (nodeId) == m_nodePositions.end ())
    {
      TimePosVector_t posVector;
      m_nodePositions[nodeId] = posVector;
    }
  TimePosVector_t & pv = m_nodePositions[nodeId];
  TimePosition_t tp;
  tp.p = pos;
  tp.t = t;
  pv.push_back (tp);
}

void
dNodeMgr::addNodeCounterUint32 (uint32_t counterId, QString counterName)
{
  m_counterIdToNamesUint32[counterId] = counterName;
}

void
dNodeMgr::addNodeCounterDouble (uint32_t counterId, QString counterName)
{
  m_counterIdToNamesDouble[counterId] = counterName;
}

void
dNodeMgr::updateNodeCounter (uint32_t nodeId, uint32_t counterId, qreal counterValue)
{
  dNode * drawNode = getNode (nodeId);
  dNode::CounterType_t ct;
  bool counterFound = false;
  for (CounterIdName_t::const_iterator i = m_counterIdToNamesDouble.begin ();
       i != m_counterIdToNamesDouble.end ();
       ++i)
    {
      if (counterId == i->first)
        {
          ct = dNode::DOUBLE_COUNTER;
          counterFound = true;
          break;
        }
    }
  if (!counterFound)
    {
    for (CounterIdName_t::const_iterator i = m_counterIdToNamesUint32.begin ();
         i != m_counterIdToNamesUint32.end ();
         ++i)
      {
        if (counterId == i->first)
          {
            ct = dNode::UINT32_COUNTER;
            counterFound = true;
            break;
          }
      }
    }
  drawNode->updateCounter (counterId, counterValue, ct);
}

dNodeMgr::CounterIdName_t
dNodeMgr::getUint32CounterNames ()
{
  return m_counterIdToNamesUint32;
}

dNodeMgr::CounterIdName_t
dNodeMgr::getDoubleCounterNames ()
{
  return m_counterIdToNamesDouble;
}

uint32_t
dNodeMgr::getCounterIdForName (QString counterName, bool &result, dNode::CounterType_t & counterType)
{
  result = false;
  for (CounterIdName_t::const_iterator i = m_counterIdToNamesDouble.begin ();
       i != m_counterIdToNamesDouble.end ();
       ++i)
    {
      QString n = i->second;
      if (n == counterName)
        {
          result = true;
          counterType = dNode::DOUBLE_COUNTER;
          return i->first;
        }
    }
  for (CounterIdName_t::const_iterator i = m_counterIdToNamesUint32.begin ();
       i != m_counterIdToNamesUint32.end ();
       ++i)
    {
      QString n = i->second;
      if (n == counterName)
        {
          result = true;
          counterType = dNode::UINT32_COUNTER;
          return i->first;
        }
    }
  return -1;
}


} //namespace netanim
