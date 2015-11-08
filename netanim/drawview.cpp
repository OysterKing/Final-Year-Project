/*Comhghall McKeating 12328401
 * Final Year Project */

#include "drawview.h"

namespace netanim
{

DrawView * pDrawView = 0;

DrawView::DrawView()
{

}

DrawView *
DrawView::getInstance()
{
    if(!pDrawView)
    {
        pDrawView = new DrawView;
    }
    return pDrawView;
}

} //namespace netanim
