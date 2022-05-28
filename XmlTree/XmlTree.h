#ifndef XML_TREE
#define XML_TREE
#include "../XmlElement/XmlElement.h"
#include "../helperClasses/Dictionary.hpp"
#include "../helperClasses/String/String.h"

class XmlTree {
    XmlElement* root;
    unsigned countOfElements = 0;
    Dictionary<String, XmlElement*> ids;    
    XmlElement* getElementById(const String& id, XmlElement*) const;
public:
    XmlTree();
    XmlTree(const XmlElement& root);
    XmlTree(const XmlTree&) = delete;
    XmlTree& operator=(const XmlTree&) = delete;
    ~XmlTree();
    const XmlElement* getRoot() const;
    void saveInFile(const String& filePath) const;
    void print() const;
    bool printAttribute(const String& id, const String& key) const;
    void setAttribute(const String& id,
    const String& key, const String& value);
    void setText(const String& id, const String& textContent);
    void printChildren(const String& id) const;
    const XmlElement* getChildByIndex(const String& id, int index) const;
    const XmlElement* getLastChild(const String& id) const;
    const XmlElement* getParent(const String& id) const;
    void changeTextContent(const String& id, const String& textContent);
    bool deleteAttribute(const String& id, const String& key);
    void addChild(const String& id, const XmlElement& el);
    const XmlElement* getElement(const String& id) const;
    bool removeChild(const String&, const String&);
    bool remove(const String& id);
    const ArrayList<XmlElement*> getElementsByTagName(const String& tagName) const;
    const ArrayList<XmlElement*> getElementsByAttribute(const String& attribute, const String& value = String()) const;
    void clear();
};

#endif