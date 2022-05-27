#include "XmlTree.h"
#include <iostream>
#include <fstream>
using namespace std;

XmlTree::XmlTree(const XmlElement& root) {
    this->root = new XmlElement(root);
}
XmlTree::XmlTree() {
    this->root = new XmlElement("tempWrapper", "rootId");
}
XmlTree::~XmlTree() {
    freeElement(root);
}
const XmlElement* XmlTree::getRoot() const {
    return root;
}

void XmlTree::saveInFile(const String& filePath) const {
    ofstream file(filePath.toString());
    for(int i = 0; i < root->getChildren().getSize(); i++) {
        root->getChildren()[i]->print(file);
    }
}

void XmlTree::print() const {
    for(int i = 0; i < root->getChildren().getSize(); i++) {
        root->getChildren()[i]->print(cout);
    }
}
XmlElement* XmlTree::getElementById(const String& id, XmlElement* el) const {
    if(el->getId() == id) return el;
    for(int i = 0; i < el->getChildren().getSize(); i++) {
        XmlElement* res = getElementById(id, el->getChildren()[i]);
        if(res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
void XmlTree::printAttribute(const String& id, const String& key) const {
    cout << getElementById(id, root)->getAttributes().find(key);
}
void XmlTree::setAttribute(const String& id,
const String& key, const String& value) {
    getElementById(id, root)->setAttribute(key, value);
}
void XmlTree::printChildren(const String& id) const {
    XmlElement* el = getElementById(id, root);
    if(el == nullptr) return;
    if(el->getChildren().getSize()) {
        cout << "There are no children of node with id " << id << endl;
    }
    for(int i = 0; i < el->getChildren().getSize(); i++) {
        el->getChildren()[i]->print(cout);
    }
}
const XmlElement* XmlTree::getChildByIndex(const String& id, int index) const {
    return getElementById(id, root)->getChildren()[index];
}
const XmlElement* XmlTree::getLastChild(const String& id) const {
    return getElementById(id, root)->getLastChild();
}
void XmlTree::changeTextContent(const String& id, const String& textContent) {
    getElementById(id, root)->setTextContent(textContent);
}
void XmlTree::deleteAttribute(const String& id, const String& key) {
    getElementById(id, root)->removeAttribute(key);
}
void XmlTree::addChild(const String& id, const XmlElement& el) {
    XmlElement* parent = getElementById(id, root);
    String idToBeAdded;
    XmlElement elToBeAdded = el;
    if(!ids.hasKey(el.getId()))
        idToBeAdded = el.getId();
    else idToBeAdded = el.getId().concat("_").concat(String(countOfElements));
    countOfElements++;
    parent->addChild(el.getType(), idToBeAdded, el.getText());
    
    for(int i = 0; i < el.getAttributes().getSize(); i++) {
        getElement(idToBeAdded)->setAttribute(
            el.getAttributes().getPairs()[i].first, el.getAttributes().getPairs()[i].second 
        );
    }
    ids.add(idToBeAdded, parent->getChildren()[parent->getChildren().getSize() - 1]);
}

XmlElement* XmlTree::getElement(const String& id) const {
    return getElementById(id, root);
}
void XmlTree::clear() {
    freeElement(root);
    root = new XmlElement("wrapper", "rootId");
    ids.clear();
    countOfElements = 0;
}

bool XmlTree::removeChild(const String& parentId, const String& childId) {
    XmlElement* el = getElement(parentId);
    if(el == nullptr) return false;
    return el->removeChild(childId);
}