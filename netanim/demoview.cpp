/*Comhghall McKeating 12328401
 * Final Year Project*/

#include "demoview.h"
#include "demoscene.h"

namespace netanim
{

DemoView * pDemoView = 0;

DemoView::DemoView(QGraphicsScene * scene):
    QGraphicsView(scene)
{

}

DemoView *
DemoView::getInstance()
{
    pDemoView = new DemoView(DemoScene::getInstance());
    return pDemoView;
}

DemoScene *
DemoView::getDemoScene(){
    return DemoScene::getInstance();
}

} //namespace netanim
