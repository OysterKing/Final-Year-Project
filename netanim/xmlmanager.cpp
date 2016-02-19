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
XmlManager::writeXmlFile(QString filename, QString text)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("DEMO");

    xmlWriter.writeStartElement("TEXT1");
    xmlWriter.writeTextElement("Body", text );
    xmlWriter.writeTextElement("Font", "fontvalue");
    xmlWriter.writeTextElement("Colour", "colourvalue");
    xmlWriter.writeTextElement("Size", "10");

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    file.close();
}

void
XmlManager::readXmlFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader rxml;
    rxml.setDevice(&file);
    rxml.readNext();

    //For each of the elements that describe the body of text,
    // add it to a vector that can be read later by the demo class that
    // adds it to the demo view as a QGraphicsText object.

    while (!rxml.atEnd()){
        std::cout << "loop";

        if(rxml.isStartElement()){

            if(rxml.name() == "DEMO"){
                rxml.readNext();
            }

            else if(rxml.name().contains("TEXT")){

                while(!rxml.atEnd()){

                    if(rxml.isEndElement()){
                        rxml.readNext();
                        break;
                    }

                    else if(rxml.isCharacters()){
                        rxml.readNext();
                    }

                    else if(rxml.isStartElement()){
                        if(rxml.name() == "Body"){
                            while(!rxml.atEnd())
                                {
                                    if(rxml.isEndElement())
                                    {
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isStartElement())
                                    {
                                        QString body = rxml.readElementText();   //Get the xml value
                                        stringVector.push_back(body);
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isCharacters())
                                    {
                                        rxml.readNext();
                                    }
                                    else
                                    {
                                        rxml.readNext();
                                    }
                                }
                        }

                        else if(rxml.name() == "Font"){
                            while(!rxml.atEnd())
                                {
                                    if(rxml.isEndElement())
                                    {
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isStartElement())
                                    {
                                        QString font = rxml.readElementText();   //Get the xml value
                                        fontVector.push_back(font);
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isCharacters())
                                    {
                                        rxml.readNext();
                                    }
                                    else
                                    {
                                        rxml.readNext();
                                    }
                                }
                        }

                        else if(rxml.name() == "Colour"){
                            while(!rxml.atEnd())
                                {
                                    if(rxml.isEndElement())
                                    {
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isStartElement())
                                    {
                                        QString colour = rxml.readElementText();   //Get the xml value
                                        colourVector.push_back(colour);
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isCharacters())
                                    {
                                        rxml.readNext();
                                    }
                                    else
                                    {
                                        rxml.readNext();
                                    }
                                }
                        }

                        else if(rxml.name() == "Size"){
                            while(!rxml.atEnd())
                                {
                                    if(rxml.isEndElement())
                                    {
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isStartElement())
                                    {
                                        QString size = rxml.readElementText();   //Get the xml value
                                        sizeVector.push_back(size);
                                        rxml.readNext();
                                        break;
                                    }
                                    else if(rxml.isCharacters())
                                    {
                                        rxml.readNext();
                                    }
                                    else
                                    {
                                        rxml.readNext();
                                    }
                                }
                        }

                        rxml.readNext();
                    }

                    else{
                        rxml.readNext();
                    }
                }
            }
        }

        else{
            rxml.readNext();
        }

        file.close();
    }
}

std::vector<QString>
XmlManager::getStringVector()
{
    return stringVector;
}

std::vector<QString>
XmlManager::getFontVector()
{
    return fontVector;
}

std::vector<QString>
XmlManager::getColourVector()
{
    return colourVector;
}

std::vector<QString>
XmlManager::getSizeVector()
{
    return sizeVector;
}

} //namespace netanim
