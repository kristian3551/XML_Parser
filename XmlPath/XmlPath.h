#ifndef XML_PATH_H
#define XML_PATH_H
#include "../helperClasses/String/String.h"
#include "../helperClasses/ArrayList.hpp"
#include "../XmlTree/XmlTree.h"

class XmlPath {
    String xmlPath;
public:
    XmlPath(const String&);
    const ArrayList<XmlElement*> getElements(const XmlTree&) const;    
};

#endif