/*Comhghall McKeating 12328401
 * Final Year Project */

#include "drawview.h"

namespace netanim
{

DrawView * pDrawView = 0;

DrawView::DrawView(QGraphicsScene * scene):
    QGraphicsView(scene)
{

}

DrawView *
DrawView::getInstance()
{
    if(!pDrawView)
    {
        pDrawView = new DrawView (DrawScene::getInstance());
    }
    return pDrawView;
}

DrawScene *
DrawView::getDrawScene(){
    return DrawScene::getInstance();
}
} //namespace netanim
