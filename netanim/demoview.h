/*Comhghall McKeating 12328401
 * Final Year Project*/

#ifndef DEMOVIEW_H
#define DEMOVIEW_H

#include "common.h"
#include "demoscene.h"

namespace netanim
{
class DemoView:public QGraphicsView
{
public:
    static DemoView * getInstance();

private:
    explicit DemoView(QGraphicsScene *);
    DemoScene * getDemoScene();
};

} //namespace netanim

#endif // DEMOVIEW_H
