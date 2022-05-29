#include "XmlParser.h"
#include <fstream>
#include <iostream>
using namespace std;

XmlParser::XmlParser(const String& filePath) {
    this->filePath = filePath;
    loadFileContent();
    iter = 0;
}

void XmlParser::setFilePath(const String& filePath) {
    this->filePath = filePath;
}

bool XmlParser::fileIsOpened() const {
    return filePath != String();
}

void XmlParser::loadFileContent() {
    if(filePath == String()) {
        fileContent = String();
        return;
    }
    ifstream file(filePath.toString());
    if(!file.is_open()) {
        fileContent = String();
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
    
    minify();
}

const String& XmlParser::getFilePath() const {
    return filePath;
}

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z');
}

void XmlParser::minify() {
    String minifiedContent;
    int iter = 0;
    while(iter < fileContent.getLength()) {
        if(fileContent.substring(iter).startsWith("  ")) {
            bool startsWithSpecialSymbol = fileContent.charAt(iter - 1) == '<'
            || fileContent.charAt(iter - 1) == '/'
            || fileContent.charAt(iter - 1) == '=';
            while(fileContent.charAt(iter) == ' ') {
                iter++;
            }
            bool endsWithSpecialSymbol = fileContent.charAt(iter) == '<'
            || fileContent.charAt(iter) == '/'
            || fileContent.charAt(iter) == '>'
            || fileContent.charAt(iter) == '=';
            if(!startsWithSpecialSymbol && !endsWithSpecialSymbol) minifiedContent += " ";
        }
        else if(fileContent.charAt(iter) == ' ') {
            bool startsWithSpecialSymbol = fileContent.charAt(iter - 1) == '<'
            || fileContent.charAt(iter - 1) == '/'
            || fileContent.charAt(iter - 1) == '=';
            
            bool endWithSpecialSymbol = 
            (fileContent.charAt(iter + 1) == '<'
            || fileContent.charAt(iter + 1) == '/'
            || fileContent.charAt(iter + 1) == '=');
            if(startsWithSpecialSymbol || endWithSpecialSymbol) 
                iter++;
            else minifiedContent += fileContent.charAt(iter++);
        }
        else {
            minifiedContent += fileContent.charAt(iter++);
        }
    }
    fileContent = minifiedContent;
}

void XmlParser::parse(const String& elementTextContent, XmlTree& tree, const XmlElement* parent) const {
    String tagInfo;
    while(elementTextContent.charAt(iter) != '>') {
        tagInfo += elementTextContent.charAt(iter);
        iter++;
    }
    ArrayList<String> tagElements = tagInfo.split(" ");
    XmlElement node(tagElements[0], "def", "", (XmlElement*)parent);
    for(int i = 1; i < tagElements.getSize(); i++) {
        ArrayList<String> attribute = tagElements[i].split("=");
        attribute[1] = (attribute[1].charAt(0) == '"') ? attribute[1].substring(1, attribute[1].getLength() - 1)
        : attribute[1];
        attribute[0] = (attribute[0].charAt(0) == '"') ? attribute[0].substring(1, attribute[0].getLength() - 1)
        : attribute[0];
        if(attribute[0] == "id") node.setId(attribute[1]);
        node.setAttribute(attribute[0], attribute[1]);
    }
    iter++;
    String textContent;
    while(elementTextContent.charAt(iter) != '<') {
        textContent += elementTextContent.charAt(iter);
        iter++;
    }
    node.setTextContent(textContent);
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