#ifndef XML_PARSER_H
#define XML_PARSER_H
#include "../XmlTree/XmlTree.h"
#include "../XmlElement/XmlElement.h"
#include "../helperClasses/String/String.h"

class XmlParser {
    String filePath;
    String fileContent;
    void parse(const String&, XmlTree&,
     const XmlElement*, int&) const;
    void loadFileContent();
    void minify();
    void parseNodeByTagInfo(const String&, XmlElement&) const;
public:
    XmlParser(const String& filePath = String());
    void setFilePath(const String&);
    bool fileIsOpened() const;
    void parseTree(XmlTree&) const;
    const String& getFilePath() const;
};

#endif