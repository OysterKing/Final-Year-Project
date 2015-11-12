/*Comhghall McKeating
 * 12328401 Final Year Project*/

#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include "common.h"
#include "drawscene.h"

namespace netanim
{

class DrawView:public QGraphicsView
{
public:
    static DrawView * getInstance();

private:
    explicit DrawView(QGraphicsScene *);
    DrawScene * getDrawScene();
};

} //namespace netanim

#endif // DRAWVIEW_H
