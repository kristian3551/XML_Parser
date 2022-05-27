#ifndef XML_PARSER_H
#define XML_PARSER_H
#include "../XmlTree/XmlTree.h"
#include "../XmlElement/XmlElement.h"
#include "../helperClasses/String/String.h"

class XmlParser {
    String filePath;
    String fileContent;
    mutable int iter;
    void parse(const String&, XmlTree&,
     const XmlElement*) const;
public:
    XmlParser(const String& filePath = String());
    void setFilePath(const String&);
    void parseTree(XmlTree&) const;
    const String& getFilePath() const;
};

#endif