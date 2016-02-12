/*Comhghall McKeating 12328401
 * Final Year Project */

#include "xmlmanager.h"
#include "common.h"

namespace netanim
{
XmlManager::XmlManager()
{

}

void
XmlManager::writeXmlFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("DEMO");

    xmlWriter.writeStartElement("TEXT1");
    xmlWriter.writeTextElement("Body", "bodyvalue" );
    xmlWriter.writeTextElement("Font", "fontvalue");
    xmlWriter.writeTextElement("Colour", "colourvalue");

    xmlWriter.writeEndElement();

    file.close();
}

void
XmlManager::readXmlFile(QString filename)
{

}

} //namespace netanim
