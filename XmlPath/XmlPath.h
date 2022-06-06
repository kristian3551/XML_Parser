#ifndef XML_PATH_H
#define XML_PATH_H
#include "../helperClasses/String/String.h"
#include "../helperClasses/ArrayList.hpp"
#include "../XmlTree/XmlTree.h"

class XmlPath {
public:
    static ArrayList<const XmlElement*> getElements(const String&, const XmlTree&);   
};

#endif