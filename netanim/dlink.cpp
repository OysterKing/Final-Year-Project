/*Comhghall McKeating
 * Final Year Project */

#include "dlink.h"
#include "dnode.h"

namespace netanim
{

dLinkManager * pdLinkManager = 0;

dLink::dLink(uint32_t fromId, uint32_t toId,
             QString pointADescription,
             QString pointBDescription, QString linkDescription, QString bandwidth, QString loss,
             QString delay, QString maxQueueSize, bool p2p):
    m_fromId (fromId),
    m_toId (toId),
    m_p2p (p2p)
{
    m_pointADescription = 0;
    m_pointBDescription = 0;
    m_currentLinkDescription = 0;
    m_loss = loss;
    m_delay = delay;
    m_maxQueueSize = maxQueueSize;
    m_bandwidth = bandwidth;

    if (!m_p2p)
      {

        m_toId = m_fromId;
      }
    QLineF line(dNodeMgr::getInstance()->getNode(m_fromId)->getCenter(),
            dNodeMgr::getInstance()->getNode(m_toId)->getCenter());
    setLine(line);

    if(pointADescription != "")
    {
        m_pointADescription = new QString (pointADescription);
        QStringList parts = (*m_pointADescription).split ('~');
        if(parts.count() == 2)
        {
            dNodeMgr::getInstance()->addIpv4Address(fromId, parts.at(0));
            dNodeMgr::getInstance()->addMacAddress(fromId, parts.at(1));
        }
    }

    if(pointBDescription != "")
    {
        m_pointBDescription = new QString (pointBDescription);
        QStringList parts = (*m_pointBDescription).split ('~');
        if(parts.count() == 2)
        {
            dNodeMgr::getInstance()->addIpv4Address(toId, parts.at(0));
            dNodeMgr::getInstance()->addMacAddress(toId, parts.at(1));
        }
    }
    m_originalLinkDescription = new QString("");
    if(linkDescription != "")
    {
        m_currentLinkDescription = new QString(linkDescription);
        *m_originalLinkDescription = linkDescription;
    }
    setZValue(DLINK_ZVALUE);
}

dLink::~dLink()
{
    if (m_pointADescription)
      delete m_pointADescription;
    if (m_pointBDescription)
      delete m_pointBDescription;
    if (m_currentLinkDescription)
      delete m_currentLinkDescription;
    if (m_originalLinkDescription)
      delete m_originalLinkDescription;
}

bool
dLink::isP2p ()
{
  return m_p2p;
}

void
dLink::repairLink ()
{
  if (!m_p2p)
    return;
  QLineF line (dNodeMgr::getInstance ()->getNode (m_fromId)->getCenter (),
               dNodeMgr::getInstance ()->getNode (m_toId)->getCenter ());
  setLine (line);
}

QPointF
dLink::getLinkDescriptionCenter (QPainter * painter , QPointF * offset)
{
  QFontMetrics fm = painter->fontMetrics ();
  qreal x = (line ().length () - fm.width (GET_DATA_PTR (m_currentLinkDescription)))/2;
  QPointF pOffset = line ().p1 ().x () < line ().p2 ().x ()? line ().p1 ():line ().p2 ();
  *offset = pOffset;
  QPointF p = QPointF (x, -1);
  return p;
}

void
dLink::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED (option);
  Q_UNUSED (widget);
  QFont font;
  font.setPointSize (5);
  QPen pen;
  pen.setCosmetic (true);
  QColor bl(255, 0, 0, 100);
  pen.setColor (bl);
  painter->setFont (font);
  painter->setPen (pen);

  painter->drawLine (line ());
  bl = QColor (0, 0, 255);
  pen.setColor (bl);
  pen.setCosmetic (true);
  painter->setPen (pen);

  if (m_currentLinkDescription)
    {
      QPointF offset;
      QPointF center = getLinkDescriptionCenter (painter, &offset);
      painter->save ();
      painter->translate (offset);

      if (offset != line ().p1 ())
        {
          painter->rotate (180-line ().angle ());
        }
      else
        {
          painter->rotate (-line ().angle ());
        }
      painter->drawText (center, *m_currentLinkDescription);
      painter->restore ();
    }

  if (!m_p2p)
    {
      m_interfacePosA = line ().p1 ();
    }

  QList <QGraphicsItem *> collidingList = collidingItems ();
  for (QList <QGraphicsItem *>::const_iterator i = collidingList.begin ();
       i != collidingList.end ();
       ++i)
    {
      QGraphicsItem * item = *i;
      if (item->type () == DNODE_TYPE)
        {
          dNode * node = qgraphicsitem_cast <dNode *> (item);
          qreal radius = node->sceneBoundingRect ().width ()/2;
          QPointF center = node->getCenter ();


          QPointF other;
          if ( (center.x () == line ().x1 ()) && (center.y () == line ().y1 ()))
            {
              other = line ().p2 ();
              QLineF l (center, other);
              if (!m_p2p)
                {
                  l = QLineF (center, QPointF (center.x (), 0));
                }

              l.setLength (radius);
              m_interfacePosA = l.p1 ();
            }
          else
            {
              other = line ().p1 ();
              QLineF l (center, other);
              l.setLength (radius);
              m_interfacePosB = l.p2 ();
            }


        }
    }
}

void
dLink::updateCurrentLinkDescription (QString linkDescription)
{
  if (!m_currentLinkDescription)
    {
      m_currentLinkDescription = new QString (linkDescription);
      return;
    }
  *m_currentLinkDescription = linkDescription;
}

void
dLink::resetCurrentLinkDescription ()
{
  if (m_originalLinkDescription)
    {
      m_currentLinkDescription = m_originalLinkDescription;
    }
}

QString
dLink::toString ()
{
  QString s = QString ("From:") + QString::number (m_fromId) + " To:" + QString::number (m_toId);
  return s;
}

QPointF
dLink::getInterfacePosA ()
{
  return m_interfacePosA;
}

QPointF
dLink::getInterfacePosB ()
{
  return m_interfacePosB;
}

QString
dLink::getInterfaceADescription ()
{
  if (m_pointADescription)
    {
      return *m_pointADescription;
    }
  else
    {
      return "";
    }

}

QString
dLink::getInterfaceBDescription ()
{
  if (m_pointBDescription)
    {
      return *m_pointBDescription;
    }
  else
    {
      return "";
    }
}

QString
dLink::getBandwidth()
{
    return m_bandwidth;
}

QString
dLink::getDelay()
{
    return m_delay;
}

QString
dLink::getLoss()
{
    return m_loss;
}

QString
dLink::getMaxQueueSize()
{
    return m_maxQueueSize;
}

dLinkManager::dLinkManager ()
{

}

dLinkManager *
dLinkManager::getInstance ()
{
  if (!pdLinkManager)
    {
      pdLinkManager = new dLinkManager;
    }
  return pdLinkManager;
}

dLink *
dLinkManager::addLink (uint32_t fromId, uint32_t toId, QString pointADescription, QString pointBDescription, QString linkDescription,
                       QString bandwidth,
                       QString loss,
                       QString delay,
                       QString maxQueueSize,
                       bool p2p)
{
  dLink * item = new dLink (fromId, toId, pointADescription, pointBDescription, linkDescription, bandwidth, loss, delay, maxQueueSize, p2p);
  if (m_pointToPointLinks.find (fromId) == m_pointToPointLinks.end ())
    {
      dLinkManager::dLinkVector_t v;
      v.push_back (item);
      m_pointToPointLinks[fromId] = v;
      return item;
    }
  else
    {
      dLinkManager::dLinkVector_t & v = m_pointToPointLinks[fromId];
      v.push_back (item);
      return item;
    }
}

dLinkManager::NodeIddLinkVectorMap_t *
dLinkManager::getLinks ()
{
  return &m_pointToPointLinks;
}

dLink *
dLinkManager::getdLink (uint32_t fromId, uint32_t toId, bool p2p)
{
  dLink * theLink = 0;
  for (dLinkManager::NodeIddLinkVectorMap_t::const_iterator i = m_pointToPointLinks.begin ();
      i != m_pointToPointLinks.end ();
      ++i)
    {
      if (fromId != i->first)
        {
          continue;
        }
      dLinkManager::dLinkVector_t v = i->second;
      for (dLinkManager::dLinkVector_t::const_iterator j = v.begin ();
          j != v.end ();
          ++j)
        {
          dLink * link = *j;
          if (!p2p)
            {
              if (!link->isP2p ())
                return link;
            }
          if ( (link->m_fromId == fromId && link->m_toId == toId) ||
              (link->m_fromId == toId && link->m_toId == fromId))
            return link;
        }
    }
  return theLink;

}

void
dLinkManager::updateLink (uint32_t fromId, uint32_t toId, QString linkDescription)
{
  dLink * drawLink = getdLink (fromId, toId);
  if (drawLink)
    {
      drawLink->updateCurrentLinkDescription (linkDescription);
    }
  //animLink-
}

void
dLinkManager::systemReset ()
{
  // remove links
  m_pointToPointLinks.clear ();

}

void
dLinkManager::repairLinks (uint32_t nodeId)
{
  for (dLinkManager::NodeIddLinkVectorMap_t::const_iterator i = m_pointToPointLinks.begin ();
      i != m_pointToPointLinks.end ();
      ++i)
    {
      dLinkManager::dLinkVector_t v = i->second;
      for (dLinkManager::dLinkVector_t::const_iterator j = v.begin ();
          j != v.end ();
          ++j)
        {
          dLink * drawLink = *j;
          if ((drawLink->m_fromId == nodeId) || (drawLink->m_toId == nodeId))
            {
              drawLink->repairLink ();
            }
        }
    }

}

} //nsmespace netanim
