/*Comhghall McKeating 12328401
 * FInal Year Project*/

#include "item.h"

Item::Item():
    m_type(Item::CIRCLE),
    m_r(255),
    m_g(0),
    m_b(0),
    m_alpha (240),
    m_pixmap (0),
    m_width (1),
    m_height (1)
{
    setAcceptHoverEvents(true);
}

Item::~Item()
{
    if(m_pixmap)
    {
        delete m_pixmap;
    }
}

void Item::setPixmap (QPixmap pix)
{
  m_pixmap = new QPixmap (pix);
  setType (Item::PIXMAP);
}

void Item::setType (ItemType_t t)
{
  m_type = t;
}

void
Item::setColor (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
{
  m_r = r;
  m_g = g;
  m_b = b;
  m_alpha = alpha;
}

void
Item::setWidth (qreal width)
{
  m_width = width;
  update ();
}

void
Item::setHeight (qreal height)
{
  m_height = height;
  update ();

}

void Item::setSize (qreal width, qreal height)
{
  setWidth (width);
  setHeight (height);
  qreal xScale = width/sceneBoundingRect ().width ();
  qreal yScale = height/sceneBoundingRect ().height ();
  setTransform (QTransform::fromScale (xScale, yScale), true);
}

void Item::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED (option)
  Q_UNUSED (widget)
  switch (m_type)
    {
    case Item::RECTANGLE:
      painter->drawRect (0, 0, m_width, m_height);
      break;
    case Item::CIRCLE:
    {
      QPen pen;
      pen.setCosmetic (true);
      QBrush brush;
      brush.setStyle (Qt::SolidPattern);
      brush.setColor (QColor (m_r, m_g, m_b, m_alpha));
      painter->setPen (pen);
      painter->setBrush (brush);
      painter->drawEllipse (QPointF (0, 0), m_width, m_height);

    }
    break;
    case Item::PIXMAP:
      if (m_pixmap)
        {
          //painter->drawPixmap (0, 0, m_width, m_height, *m_pixmap);
          painter->drawPixmap (-m_width/2, -m_height/2, m_width/2, m_height/2, *m_pixmap);
        }
      break;
    }
}

qreal Item::getItemWidth ()
{
  return sceneBoundingRect ().width ();
}

qreal Item::getItemHeight ()
{
  return sceneBoundingRect ().height ();
}

QPainterPath
Item::shape () const
{
  QPainterPath path;
  switch (m_type)
    {
      case Item::CIRCLE:
        path.addEllipse (QPointF (0, 0), m_width, m_height);
        break;
      default:
        path.addRect (QRectF (0, 0, m_width, m_height));
        break;
    }
  return path;
}

QRectF Item::boundingRect () const
{
  QPainterPath path;

  switch (m_type)
    {
      case Item::CIRCLE:
        path.addEllipse (QPointF (0, 0), m_width, m_height);
        return path.boundingRect();
        break;
      default:
        return QRectF (0, 0, m_width, m_height);
        break;
    }
}
