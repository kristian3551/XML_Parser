#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H
#include "../helperClasses/ArrayList.hpp"
#include "../helperClasses/Dictionary.hpp"
#include "../helperClasses/String/String.h"
#include <iostream>

const String DEFAULT_ID = "def";
const String DEFAULT_TEXT_CONTENT = "";

class XmlElement {
    String type;
    String id;
    String textContent;
    ArrayList<XmlElement*> children;
    Dictionary<String, String> attributes;
    XmlElement* parent;
public:
    XmlElement(const String& type = "defaultType", const String& id = DEFAULT_ID,
     const String& textContent = DEFAULT_TEXT_CONTENT, XmlElement* parent = nullptr);
    bool addChild(const String& type, const String& id, 
    const String& textContent = DEFAULT_TEXT_CONTENT, XmlElement* parent = nullptr);
    bool addChild(const XmlElement& el);
    bool setTextContent(const String& textContent);
    bool setParent(const XmlElement*);
    bool setId(const String& id);
    bool setType(const String&);
    bool removeChild(XmlElement*);
    bool remove();
    bool setAttribute(const String& key, const String& value);
    bool hasAttribute(const String& key, const String& value = String()) const;
    ArrayList<const XmlElement*> getChildrenByType(const String& type) const;
    ArrayList<const XmlElement*> getChildrenByAttribute(const String& key, const String& value = String()) const;
    ArrayList<const XmlElement*> getChildrenByIndex(int index) const;
    ArrayList<const XmlElement*> getDescendants(const XmlElement*) const;
    bool removeAttribute(const String& key);
    const XmlElement* getChild(int index) const;
    ArrayList<const XmlElement*> getChildren() const;
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