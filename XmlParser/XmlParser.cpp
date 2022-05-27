#include "XmlParser.h"
#include <fstream>
#include <iostream>
using namespace std;

XmlParser::XmlParser(const String& filePath) {
    ifstream file(filePath.toString());
    if(!file.is_open()) {
        return;
    }
    while(!file.eof()) {
        if(file.peek() != '\t' && file.peek() != '\n') {
            char buffer[2];
            buffer[0] = file.get();
            buffer[1] = '\0';
            fileContent += buffer;
        }
        else file.get();
    }
    iter = 0;
    this->filePath = filePath;
}

void XmlParser::setFilePath(const String& filePath) {
    ifstream file(filePath.toString());
    if(!file.is_open()) {
        this->filePath = String();
        this->fileContent = String();
        return;
    }
    while(!file.eof()) {
        if(file.peek() != '\t' && file.peek() != '\n') {
            char buffer[2];
            buffer[0] = file.get();
            buffer[1] = '\0';
            fileContent += buffer;
        }
        else file.get();
    }
    iter = 0;
    this->filePath = filePath;
}

const String& XmlParser::getFilePath() const {
    return filePath;
}

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z');
}

void XmlParser::parse(const String& elementTextContent, XmlTree& tree, const XmlElement* parent) const {
    String tagInfo;
    while(elementTextContent.charAt(iter) != '>') {
        tagInfo += elementTextContent.substring(iter, iter + 1);
        iter++;
    }
    ArrayList<String> tagElements = tagInfo.split(" ");
    XmlElement node(tagElements[0]);
    for(int i = 1; i < tagElements.getSize(); i++) {
        ArrayList<String> attribute = tagElements[i].split("=");
        attribute[1] = (attribute[1].charAt(0) == '"') ? attribute[1].substring(1, attribute[1].getLength() - 1)
        : attribute[1];
        attribute[0] = (attribute[0].charAt(0) == '"') ? attribute[0].substring(1, attribute[0].getLength() - 1)
        : attribute[0];
        if(attribute[0] == "id") node.setId(attribute[1]);
        else node.setAttribute(attribute[0], attribute[1]);
    }
    iter++;
    String textContent;
    while(elementTextContent.charAt(iter) != '<') {
        textContent += elementTextContent.substring(iter, iter + 1);
        iter++;
    }
    if(textContent != String()) node.setTextContent(textContent);
    tree.addChild(parent->getId(), node);
    iter++;
    if(elementTextContent.charAt(iter) != '/')
        parse(elementTextContent, tree, tree.getLastChild(parent->getId()));
    while(elementTextContent.charAt(iter) != '>') {
        iter++;
    }
    iter++;
    iter++;
    if(elementTextContent.charAt(iter) != 0 && elementTextContent.charAt(iter) != '/')
        parse(elementTextContent, tree, parent);
}

void XmlParser::parseTree(XmlTree& tree) const {
    if(fileContent.getLength() <= 1) return;
    parse(fileContent.substring(1), tree, tree.getRoot());
    iter = 0;
}