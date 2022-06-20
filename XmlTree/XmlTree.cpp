#include "XmlTree.h"
#include <iostream>
#include <fstream>
using namespace std;

XmlTree::XmlTree() {
    this->root = new XmlElement("wrapper", "rootId");
}
XmlTree::~XmlTree() {
    freeElement(root);
}
const XmlElement* XmlTree::getRoot() const {
    return root;
}

bool XmlTree::hasElementWithId(const String& id) const {
    return ids.hasKey(id);
}

void XmlTree::saveInFile(const String& filePath) const {
    ofstream file(filePath.toString());
    for(int i = 0; i < root->getChildren().getSize(); i++) {
        root->getChildren()[i]->saveInFile(file);
    }
}

void XmlTree::print() const {
    for(int i = 0; i < root->getChildren().getSize(); i++) {
        root->getChildren()[i]->print(cout);
    }
}
const XmlElement* XmlTree::getElementById(const String& id, const XmlElement* el) const {
    if(el->getId() == id) return el;
    for(int i = 0; i < el->getChildren().getSize(); i++) {
        const XmlElement* res = getElementById(id, el->getChildren()[i]);
        if(res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
XmlElement* XmlTree::getElementById(const String& id, XmlElement* el) {
    if(el->getId() == id) return el;
    for(int i = 0; i < el->getChildren().getSize(); i++) {
        XmlElement* res = getElementById(id, el->getChildren()[i]);
        if(res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
bool XmlTree::printAttribute(const String& id, const String& key) const {
    const XmlElement* el = getElementById(id, root);
    if(el == nullptr) return false;
    cout << el->getAttributes().find(key);
    return true;
}
void XmlTree::setAttribute(const String& id,
const String& key, const String& value) {
    XmlElement* el = getElementById(id, root);
    if(el == nullptr) 
        throw String("There is no such element");
    el->setAttribute(key, value);
}
void XmlTree::setText(const String& id, const String& textContent) {
    XmlElement* el = getElementById(id, root);
    if(el == nullptr) 
        throw String("There is no such element");
    el->setTextContent(textContent);
}
void XmlTree::setId(const String& oldId, const String& newId) {
    XmlElement* el = getElementById(oldId, root);
    if(el == nullptr) 
        throw String("There is no such element");
    el->setId(newId);
    ids.add(newId, ids.find(oldId));
    ids.remove(oldId);
}
void XmlTree::printChildren(const String& id) const {
    const XmlElement* el = getElementById(id, root);
    if(el == nullptr) return;
    if(el->getChildren().getSize() == 0) {
        cout << "There are no children of node with id " << id << endl;
    }
    for(int i = 0; i < el->getChildren().getSize(); i++) {
        el->getChildren()[i]->print(cout);
    }
}
const XmlElement* XmlTree::getChildByIndex(const String& id, int index) const {
    const XmlElement* el = getElementById(id, root);
    if(el == nullptr) 
        throw String("There is no such element");
    return getElementById(id, root)->getChildren()[index];
}
const XmlElement* XmlTree::getLastChild(const String& id) const {
    const XmlElement* el = getElementById(id, root);
    if(el == nullptr)
        throw String("There is no such element");
    const XmlElement* res = el->getLastChild();
    if(res == nullptr)
        throw String("Element has no children");
    return el->getLastChild();
}
bool XmlTree::deleteAttribute(const String& id, const String& key) {
    XmlElement* el = getElementById(id, root);
    if(el == nullptr)
        throw String("There is no such element");
    return el->removeAttribute(key);
}
void XmlTree::addChild(const String& id, const XmlElement& el) {
    XmlElement* parent = getElementById(id, root);
    if(parent == nullptr) 
        throw String("There is no such element");
    String idToBeAdded = el.getId();
    XmlElement elToBeAdded = el;
    if(idToBeAdded == "def") idToBeAdded = el.getId().concat("_").concat(String(countOfElements));
    countOfElements++;
    elToBeAdded.setId(idToBeAdded);
    parent->addChild(elToBeAdded);
    ids.add(idToBeAdded, parent->getChildren()[parent->getChildren().getSize() - 1]);
}
const XmlElement* XmlTree::getParent(const String& id) const {
    for(int i = 0; i < ids.getSize(); i++) {
        if(ids.getPairs()[i].second->hasChild(id)) return ids.getPairs()[i].second;
    }
    throw String("There is no such element");
}

const XmlElement* XmlTree::getElement(const String& id) const {
    return getElementById(id, root);
}
void XmlTree::clear() {
    freeElement(root);
    root = new XmlElement("wrapper", "rootId");
    ids.clear();
    countOfElements = 0;
}
bool XmlTree::remove(const String& id) {
    return XmlElement::removeDescendant(id, root);
}

ArrayList<const XmlElement*> XmlTree::getElementsByTagName(const String& tagName) const {
    ArrayList<const XmlElement*> list;
    for(int i = 0; i < ids.getSize(); i++) {
        if(ids.getPairs()[i].second->getType() == tagName) 
            list.push(ids.getPairs()[i].second);
    }
    return list;
}

ArrayList<const XmlElement*> XmlTree::getElementsByAttribute(const String& attribute, const String& value) const {
    ArrayList<const XmlElement*> list;
    for(int i = 0; i < ids.getSize(); i++) {
        if(value == String())
            if(ids.getPairs()[i].second->getAttributes().hasKey(attribute)) 
                list.push(ids.getPairs()[i].second);
        else if(ids.getPairs()[i].second->getAttributes().hasKey(attribute)
        && ids.getPairs()[i].second->getAttributes().find(attribute) == value)
            list.push(ids.getPairs()[i].second);
    }
    return list;
}

ArrayList<const XmlElement*> XmlTree::getDescendants(const String& id) const {
    const XmlElement* el = getElementById(id, root);
    if(el == nullptr) 
        throw String("There is no such element");
    return el->getDescendants(el);
}