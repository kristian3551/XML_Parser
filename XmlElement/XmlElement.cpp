#include "XmlElement.h"
#include <iostream>
using namespace std;

XmlElement::XmlElement(const String& type, const String& id,
     const String& textContent, XmlElement* parent) {
         this->type = type;
         this->id = id;
         this->textContent = textContent;
     }
bool XmlElement::addChild(const XmlElement& el) {
    XmlElement* child = new XmlElement(el);
    return this->children.push(child);
}
bool XmlElement::removeChild(const String& id) {
    for(int i = 0; i < children.getSize(); i++) {
        if(children[i]->id == id) {
            freeElement(children[i]);
            children.removeByIndex(i);
            return true;
        }
    }
    return false;
}
bool XmlElement::removeDescendant(const String& id, XmlElement* el) {
    for(int i = 0; i < el->children.getSize(); i++) {
        if(el->children[i]->getId() == id) {
            el->children.removeByIndex(i);
            return true;
        }
        else if(removeDescendant(id, el->children[i])) {
            return true;
        }
    }
    return false;
}
bool XmlElement::setTextContent(const String& textContent) {
    this->textContent = textContent;
    return true;
}
bool XmlElement::setId(const String& id) {
    this->id = id;
    return true;
}
bool XmlElement::setType(const String& type) {
    this->type = type;
    return true;
}
bool XmlElement::setAttribute(const String& key, const String& value) {
    return attributes.setValue(key, value);
}
bool XmlElement::hasAttribute(const String& key, const String& value) const {
    try {
        if(value == String()) {
            return attributes.hasKey(key);
        }
        else {
            return attributes.find(key) == value;
        }
    }
    catch(const String& str) {
        return false;
    }
}
bool XmlElement::hasChild(const String& id) const {
    for(int i = 0; i < children.getSize(); i++) {
        if(children[i]->id == id) return true;
    }
    return false;
}
ArrayList<const XmlElement*> XmlElement::getChildrenByAttribute(const String& key, const String& value) const {
    ArrayList<const XmlElement*> res;
    for(int i = 0; i < children.getSize(); i++) {
        if(children[i]->hasAttribute(key, value)) {
            res.push(children[i]);
        }
    }
    return res;
}
ArrayList<const XmlElement*> XmlElement::getChildrenByIndex(int index) const {
    ArrayList<const XmlElement*> res;
    if(index < 0 || index >= children.getSize()) return res;
    res.push(children[index]);
    return res;
}
ArrayList<const XmlElement*> XmlElement::getChildrenByType(const String& type) const {
    ArrayList<const XmlElement*> res;
    for(int i = 0; i < children.getSize(); i++) {
        if(children[i]->getType() == type) {
            res.push(children[i]);
        }
    }
    return res;
}
ArrayList<const XmlElement*> XmlElement::getDescendants(const XmlElement* current) const {
    ArrayList<const XmlElement*> res;
    for(int i = 0; i < current->getChildren().getSize(); i++) {
        res.push(current->getChildren()[i]);
        res += getDescendants(current->getChildren()[i]);
    }
    return res;
}
bool XmlElement::removeAttribute(const String& key) {
    return attributes.remove(key);
}
const XmlElement* XmlElement::getChild(int index) const {
    if(index < 0 || index >= children.getSize()) 
        throw String("Invalid index");
    return children[index];
}
ArrayList<XmlElement*> XmlElement::getChildren() {
    return children;
}
ArrayList<const XmlElement*> XmlElement::getChildren() const {
    ArrayList<const XmlElement*> res;
    for(int i = 0; i < children.getSize(); i++) {
        res.push(children[i]);
    }
    return res;
}
const XmlElement* XmlElement::getLastChild() const {
    if(children.getSize() == 0) return nullptr;
    return children[children.getSize() - 1];
}
const String& XmlElement::getText() const {
    return textContent;
}
void XmlElement::saveInFile(std::ostream& os, int k) const {
    for(int i = 0; i < k; i++)
        os << "\t";
    os << "<" << type;
    if(!id.startsWith("def")) os << " id=\"" << id << "\"";
    for(int i = 0; i < attributes.getSize(); i++) {
        if(attributes.getPairs()[i].first != "id") os << " " << attributes.getPairs()[i].first << "="
        << "\"" << attributes.getPairs()[i].second << "\"";
    }
    os << ">";
    os << textContent;
    if(!this->children.isEmpty()) os << endl;
    for(int i = 0; i < this->children.getSize(); i++) {
        this->children[i]->saveInFile(os, k + 1);
    }
    if(!this->children.isEmpty()) for(int i = 0; i < k; i++)
        os << "\t";
    os << "</" << type << ">" << endl;
}
void XmlElement::print(std::ostream& os, int k) const {
    for(int i = 0; i < k; i++)
        os << "\t";
    os << "<" << type;
    os << " id=\"" << id << "\"";
    for(int i = 0; i < attributes.getSize(); i++) {
        if(attributes.getPairs()[i].first != "id") os << " " << attributes.getPairs()[i].first << "="
        << "\"" << attributes.getPairs()[i].second << "\"";
    }
    os << ">";
    os << textContent;
    if(!this->children.isEmpty()) os << endl;
    for(int i = 0; i < this->children.getSize(); i++) {
        this->children[i]->print(os, k + 1);
    }
    if(!this->children.isEmpty()) for(int i = 0; i < k; i++)
        os << "\t";
    os << "</" << type << ">" << endl;
}

const Dictionary<String, String>& XmlElement::getAttributes() const {
    return attributes;
}


void freeElement(XmlElement* el) {
    for(int i = 0; i < el->children.getSize(); i++) {
        freeElement(el->children[i]);
    }
    delete el;
}

const String& XmlElement::getType() const {
    return type;
}
const String& XmlElement::getId() const {
    return id;
}