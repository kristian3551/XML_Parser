#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H
#include "../helperClasses/ArrayList.hpp"
#include "../helperClasses/Dictionary.hpp"
#include "../helperClasses/String/String.h"
#include <iostream>

class XmlElement {
    String type;
    String id;
    String textContent;
    ArrayList<XmlElement*> children;
    Dictionary<String, String> attributes;
public:
    XmlElement(const String& type = "defaultType", const String& id = "dId",
     const String& textContent = "defaultContent");
    bool addChild(const String& type, const String& id, 
    const String& textContent = "defaultContent");
    bool addChild(const XmlElement& el);
    bool setTextContent(const String& textContent);
    bool setId(const String& id);
    bool removeChild(const String& id);
    bool setAttribute(const String& key, const String& value);
    bool removeAttribute(const String& key);
    const XmlElement* getChild(int index) const;
    const ArrayList<XmlElement*> getChildren() const;
    const XmlElement* getLastChild() const;
    const String& getText() const;
    const String& getId() const;
    const Dictionary<String, String>& getAttributes() const;
    const String& getType() const;
    void print(std::ostream& os, int k = 0) const;
    friend void freeElement(XmlElement*);
};


#endif