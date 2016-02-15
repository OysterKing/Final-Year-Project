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
    std::vector<QString> getStringVector();
    std::vector<QString> getColourVector();
    std::vector<QString> getFontVector();
    std::vector<QString> getSizeVector();

private:
    std::vector<QString> stringVector;
    std::vector<QString> fontVector;
    std::vector<QString> colourVector;
    std::vector<QString> sizeVector;
};
} //namespace netanim

#endif // XMLMANAGER_H
