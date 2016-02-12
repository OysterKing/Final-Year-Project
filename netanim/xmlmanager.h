/*Comhghall McKeating 12328401
 * Final Year Project */

#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include "common.h"

namespace netanim
{
class XmlManager
{
public:
    XmlManager();
    void readXmlFile(QString filename);
    void writeXmlFile(QString filename);
};
} //namespace netanim

#endif // XMLMANAGER_H
