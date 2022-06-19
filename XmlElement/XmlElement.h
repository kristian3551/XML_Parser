#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H
#include "../helperClasses/ArrayList.hpp"
#include "../helperClasses/Dictionary.hpp"
#include "../helperClasses/String/String.h"
#include <iostream>

const String DEFAULT_ID = "def";
const String DEFAULT_TEXT_CONTENT = "";
const String DEFAULT_TYPE = "type";

class XmlElement {
    String type;
    String id;
    String textContent;
    ArrayList<XmlElement*> children;
    Dictionary<String, String> attributes;
public:
    XmlElement(const String& type = DEFAULT_TYPE, const String& id = DEFAULT_ID,
     const String& textContent = DEFAULT_TEXT_CONTENT, XmlElement* parent = nullptr);
    bool addChild(const XmlElement& el);
    bool setTextContent(const String& textContent);
    bool setId(const String& id);
    bool setType(const String&);
    bool removeChild(const String& id);
    static bool removeDescendant(const String& id, XmlElement*);
    bool setAttribute(const String& key, const String& value);
    bool hasAttribute(const String& key, const String& value = String()) const;
    bool hasChild(const String& id) const;
    ArrayList<const XmlElement*> getChildrenByType(const String& type) const;
    ArrayList<const XmlElement*> getChildrenByAttribute(const String& key, const String& value = String()) const;
    ArrayList<const XmlElement*> getChildrenByIndex(int index) const;
    ArrayList<const XmlElement*> getDescendants(const XmlElement* el) const;
    bool removeAttribute(const String& key);
    const XmlElement* getChild(int index) const;
    ArrayList<XmlElement*> getChildren();
    ArrayList<const XmlElement*> getChildren() const;
    const XmlElement* getLastChild() const;
    const String& getText() const;
    const String& getId() const;
    const Dictionary<String, String>& getAttributes() const;
    const String& getType() const;
    void saveInFile(std::ostream& os, int k = 0) const;
    void print(std::ostream& os, int k = 0) const;
    friend void freeElement(XmlElement*);
};


#endif