#include "XmlElement.h"
#include <iostream>
using namespace std;

XmlElement::XmlElement(const String& type, const String& id,
     const String& textContent) {
         this->type = type;
         this->id = id;
         this->textContent = textContent;
     }
bool XmlElement::addChild(const String& type, const String& id,
const String& textContent) {
    XmlElement* child = new XmlElement(type, id, textContent);
    this->children.push(child);
    return true;
}
bool XmlElement::addChild(const XmlElement& el) {
    XmlElement* child = new XmlElement(el.type, el.id, el.textContent);
    for(int i = 0; i < el.attributes.getSize(); i++) {
        child->setAttribute(
            el.attributes.getPairs()[i].first,
            el.attributes.getPairs()[i].second
        );
    }
    return this->children.push(child);
}
bool XmlElement::removeChild(const String& id) {
    XmlElement* element = nullptr;
    for(int i = 0; i < children.getSize(); i++)
        if(children[i]->id == id) {
            element = children[i];
            break;
        }
    if(element == nullptr) return false;
    freeElement(element);
    return this->children.remove(element);
}
bool XmlElement::setTextContent(const String& textContent) {
    this->textContent = textContent;
    return true;
}
bool XmlElement::setId(const String& id) {
    this->id = id;
    return true;
}
bool XmlElement::setAttribute(const String& key, const String& value) {
    return attributes.setValue(key, value);
}
bool XmlElement::removeAttribute(const String& key) {
    return attributes.remove(key);
}
const XmlElement* XmlElement::getChild(int index) const {
    if(index < 0 || index >= children.getSize()) 
        throw String("Invalid index");
    return children[index];
}
const ArrayList<XmlElement*> XmlElement::getChildren() const {
    return children;
}
const XmlElement* XmlElement::getLastChild() const {
    if(children.getSize() == 0) return nullptr;
    return children[children.getSize() - 1];
}
const String& XmlElement::getText() const {
    return textContent;
}
void XmlElement::print(std::ostream& os, int k) const {
    for(int i = 0; i < k; i++)
        os << "\t";
    os << "<" << type;
    os << " id=\"" << id << "\"";
    for(int i = 0; i < attributes.getSize(); i++) {
        os << " " << attributes.getPairs()[i].first << "="
        << "\"" << attributes.getPairs()[i].second << "\"";
    }
    os << ">";
    if(textContent != "defaultContent") {
        os << textContent;
    }
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