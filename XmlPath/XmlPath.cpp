#include "XmlPath.h"
#include <iostream>
using namespace std;

XmlPath::XmlPath(const String& xmlPath) {
    this->xmlPath = xmlPath;
}

const ArrayList<XmlElement*> XmlPath::getElements(const XmlTree& tree) const {
    ArrayList<String> parts = xmlPath.split("/");
    ArrayList<XmlElement*> elementsToFind;
    for(int i = 0; i < parts.getSize(); i++) {
        int attributeIndexStart = parts[i].indexOf("(");
        int childIndexStart = parts[i].indexOf("[");
        String tagName;
        if(parts[i].endsWith(")"))
            tagName = parts[i].substring(0, attributeIndexStart);
        else if(parts[i].endsWith("]"))
            tagName = parts[i].substring(0, childIndexStart);
        else tagName = parts[i];
        if(i == 0) {
                if(!tagName.startsWith("~")) elementsToFind += tree.getElementsByTagName(tagName);
                else elementsToFind += tree.getRoot()->getChildren()[0]->getChildrenByType(tagName.substring(1));
            }
        else {
            ArrayList<XmlElement*> updatedElementsToFind;
            for(int j = 0; j < elementsToFind.getSize(); j++) {
                updatedElementsToFind += elementsToFind[j]->getChildrenByType(tagName);
            }
            elementsToFind = updatedElementsToFind;
        }
        if(parts[i].endsWith(")")) {
            String attributeData = parts[i].substring(attributeIndexStart + 1, parts[i].getLength() - 1);
            if(attributeData.contains("&")) {
                String attributeType = attributeData.substring(1);
                ArrayList<XmlElement*> updatedElementsToFind;
                for(int j = 0; j < elementsToFind.getSize(); j++) {
                   if(elementsToFind[j]->hasAttribute(attributeType))
                        updatedElementsToFind += elementsToFind[j];
                }
                elementsToFind = updatedElementsToFind;
            }
            else {
                ArrayList<String> pair = attributeData.split("=");
                ArrayList<XmlElement*> updatedElementsToFind;
                for(int j = 0; j < elementsToFind.getSize(); j++) {
                    if(elementsToFind[j]->hasAttribute(pair[0], pair[1]))
                        updatedElementsToFind += elementsToFind[j];
                }
                elementsToFind = updatedElementsToFind;
            }
        }
        else if(parts[i].endsWith("]")) {
            String index = parts[i].substring(childIndexStart + 1, parts[i].getLength() - 1);
            int n = atoi(index.toString());
            ArrayList<XmlElement*> updatedElementsToFind;
            for(int j = 0; j < elementsToFind.getSize(); j++) {
                updatedElementsToFind += elementsToFind[j]->getChildrenByIndex(n);
            }
            elementsToFind = updatedElementsToFind;
        }
    }
    return elementsToFind;
}