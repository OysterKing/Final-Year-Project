/*Comhghall McKeating 12328401
 * Final Year Project*/

#ifndef DLINK_H
#define DLINK_H
#include "common.h"

namespace netanim
{

class dLink: public QGraphicsLineItem
{
public:
    dLink(uint32_t fromId, uint32_t toId,
          QString pointADescription = "", QString pointBDescription = "",
          QString linkDescription = "", bool p2p = true);

    ~dLink();
    uint32_t m_fromId;
    uint32_t m_toId;
    QString * m_pointADescription;
    QString * m_pointBDescription;
    QString * m_currentLinkDescription;
    bool    m_p2p;
    void updateCurrentLinkDescription (QString linkDescription);
    void resetCurrentLinkDescription ();
    QString toString ();
    QPointF getInterfacePosA ();
    QPointF getInterfacePosB ();
    QString getInterfaceADescription ();
    QString getInterfaceBDescription ();
    void repairLink ();
    bool isP2p ();

protected:
  void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:

  QString * m_originalLinkDescription;

  QPointF getLinkDescriptionCenter (QPainter *, QPointF *);
  QPointF m_interfacePosA;
  QPointF m_interfacePosB;

};

class dLinkManager
{
public:
  typedef QVector <dLink *> dLinkVector_t;
  typedef std::map <uint32_t, dLinkVector_t> NodeIddLinkVectorMap_t;
  static dLinkManager * getInstance ();
  dLink * addLink (uint32_t fromId, uint32_t toId,
                     QString pointADescription,
                     QString pointBDescription, QString linkDescription, bool p2p = true);


  NodeIddLinkVectorMap_t * getLinks ();
  dLink * getdLink (uint32_t fromId, uint32_t toId, bool p2p = true);
  void updateLink (uint32_t fromId, uint32_t toId, QString linkDescription);
  void repairLinks (uint32_t nodeId);
  void systemReset ();

private:
  dLinkManager ();
  //AnimLinkVector_t             m_pointToPointLinks;
  NodeIddLinkVectorMap_t    m_pointToPointLinks;
};
} //namespace netanim

#endif // DLINK_H
