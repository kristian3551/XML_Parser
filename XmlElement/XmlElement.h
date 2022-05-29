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
    XmlElement* parent;
public:
    XmlElement(const String& type = "defaultType", const String& id = "dId",
     const String& textContent = String(), XmlElement* parent = nullptr);
    bool addChild(const String& type, const String& id, 
    const String& textContent = String(), XmlElement* parent = nullptr);
    bool addChild(const XmlElement& el);
    bool setTextContent(const String& textContent);
    bool setParent(const XmlElement*);
    bool setId(const String& id);
    bool removeChild(XmlElement*);
    bool remove();
    bool setAttribute(const String& key, const String& value);
    bool hasAttribute(const String& key, const String& value = String()) const;
    const ArrayList<XmlElement*> getChildrenByType(const String& type) const;
    const ArrayList<XmlElement*> getChildrenByAttribute(const String& key, const String& value = String()) const;
    const ArrayList<XmlElement*> getChildrenByIndex(int index) const;
    bool removeAttribute(const String& key);
    const XmlElement* getChild(int index) const;
    const ArrayList<XmlElement*> getChildren() const;
    const XmlElement* getLastChild() const;
    const String& getText() const;
    const String& getId() const;
    const XmlElement* getParent() const;
    const Dictionary<String, String>& getAttributes() const;
    const String& getType() const;
    void print(std::ostream& os, int k = 0) const;
    friend void freeElement(XmlElement*);
};


#endif