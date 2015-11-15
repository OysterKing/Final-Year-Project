/*Comhghall McKeating
 * 12328401 Final Year Project*/

#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include "animatorconstants.h"

class Item : public QGraphicsItem
{

public:
    typedef enum{
        RECTANGLE,
        CIRCLE,
        PIXMAP
    }ItemType_t;
    enum{Type = DNODE_TYPE};
    int type () const
    {
        return Item::Type;
    }
    Item();
    ~Item();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    qreal getItemWidth ();
    qreal getItemHeight ();
    qreal getBorderWidth ();
    void setSize (qreal width, qreal height);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void setPixmap (QPixmap pix);
    void setType (ItemType_t t);
    void setWidth (qreal width);
    void setHeight (qreal height);
    void setColor (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);

protected:
    ItemType_t m_type;
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    uint8_t m_alpha;
    QPixmap * m_pixmap;

protected:
    qreal m_width;
    qreal m_height;
};

#endif // ITEM_H
