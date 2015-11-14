/*Comhghall McKeating 12328401
 * Final Year Project*/

#include "drawscene.h"
#include "drawmode.h"
#include "drawview.h"
#include "logqt.h"

namespace netanim
{

DrawScene * pDrawScene = 0;

DrawScene::DrawScene():
    QGraphicsScene(0, 0, 250, 250),
    m_enableMousePositionLabel(false)
{
    m_mousePositionLabel = new QLabel("");
    m_mousePositionLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mousePositionProxyWidget = addWidget (m_mousePositionLabel, Qt::ToolTip);
    m_mousePositionProxyWidget->setFlag (QGraphicsItem::ItemIgnoresTransformations);
    m_nGridLines = 50;
    m_showGrid = true;

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
DrawScene::enableElementAddition(bool enable)
{
    m_enableElementAddition = enable;
}

void
DrawScene::setMousePositionLabel (QPointF pos)
{

  //QString string = "    (" + QString::number (qRound (pos.x ())) + "," + QString::number (qRound (pos.y ())) + ")";
  QString string = "    (" + QString::number ( (pos.x ())) + "," + QString::number ( (pos.y ())) + ")";

  m_mousePositionLabel->setText (string);
  m_mousePositionProxyWidget->setPos (pos.x (), pos.y ());
  m_mousePositionLabel->adjustSize ();

}

void
DrawScene::addElement(QPointF pos)
{
    QString string = "    (" + QString::number ( (pos.x ())) + "," + QString::number ( (pos.y ())) + ")";
//    DrawScene::addItem(m_elementItem);
//    DrawScene::(m_elementWidget);
//    DrawScene::addText(string);
//    m_elementLabel->setText("TEST");
//    m_elementProxyItem->setPos(pos.x(), pos.y());
//    m_elementProxyItem->setVisible(true);
//    m_elementProxyWidget->pos() = pos;
//    m_elementText->setEnabled(true);
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
    if(m_enableElementAddition){
        QPointF scenePos = event->scenePos();
        if((scenePos.x () > 0) && (scenePos.y () > 0)){
            addElement(scenePos);
        }
    }
    return QGraphicsScene::mousePressEvent(event);
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
