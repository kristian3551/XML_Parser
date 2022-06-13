#include "XmlParser.h"
#include <fstream>
#include <iostream>
using namespace std;

const int EXCEPTION_PLACE_WIDTH = 20;

XmlParser::XmlParser(const String& filePath) {
    this->filePath = filePath;
    loadFileContent();
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
    minifiedContent = minifiedContent.trim();
    fileContent = minifiedContent.substring(0, minifiedContent.getLength() - 1);
}

void XmlParser::parseNodeByTagInfo(const String& tagInfo, XmlElement& node) const {
    int startIndex = tagInfo.indexOf(" ");
    String type = tagInfo.substring(0, startIndex);
    node.setType(type);
    bool isInParenthesis = false;
    for(int i = (startIndex++) + 1; i < tagInfo.getLength(); i++) {
        if(!isInParenthesis && tagInfo.charAt(i) == '\"') {
            isInParenthesis = true;
        }
        else if(isInParenthesis && tagInfo.charAt(i) == '\"') {
            String attributeStr = tagInfo.substring(startIndex, i);
            ArrayList<String> attributeData = attributeStr.split("=\"");
            node.setAttribute(attributeData[0], attributeData[1]);
            startIndex = i + 2;
            isInParenthesis = false;
        }
    }
}

void XmlParser::parse(const String& elementTextContent, XmlTree& tree, const XmlElement* parent, int& iter) const {
    String tagInfo;
    int searchingStartingIndex = iter;
    while(elementTextContent.charAt(iter) != '>') {
        tagInfo += elementTextContent.charAt(iter);
        iter++;
        if(iter >= elementTextContent.getLength() || elementTextContent.charAt(iter) == '<')
            throw String("Parsing error! \n... ").concat(elementTextContent.substring(searchingStartingIndex - EXCEPTION_PLACE_WIDTH, searchingStartingIndex + EXCEPTION_PLACE_WIDTH))
            .concat(String("... \nThere is a missing '>'"));
    }
    XmlElement node;
    parseNodeByTagInfo(tagInfo, node);
    iter++;
    String textContent;
    searchingStartingIndex = iter;
    while(elementTextContent.charAt(iter) != '<') {
        textContent += elementTextContent.charAt(iter);
        iter++;
        if(iter >= elementTextContent.getLength() || elementTextContent.charAt(iter) == '>')
            throw String("Parsing error! \n... ").concat(elementTextContent.substring(iter - EXCEPTION_PLACE_WIDTH, iter + EXCEPTION_PLACE_WIDTH))
            .concat(String("... \nThere is a missing '<'"));
    }
    node.setTextContent(textContent);
    tree.addChild(parent->getId(), node);
    iter++;
    if(elementTextContent.charAt(iter) != '/')
        parse(elementTextContent, tree, tree.getLastChild(parent->getId()), iter);
    searchingStartingIndex = iter;
    while(elementTextContent.charAt(iter) != '>') {
        iter++;
         if(iter >= elementTextContent.getLength() || elementTextContent.charAt(iter) == '<')
            throw String("Parsing error! \n... ").concat(elementTextContent.substring(searchingStartingIndex - EXCEPTION_PLACE_WIDTH, searchingStartingIndex + EXCEPTION_PLACE_WIDTH))
            .concat(String("... \nThere is a missing '>'"));
    }
    iter++;
    iter++;
    if(elementTextContent.charAt(iter) != 0 && elementTextContent.charAt(iter) != '/')
        parse(elementTextContent, tree, parent, iter);
}

void XmlParser::parseTree(XmlTree& tree) const {
    if(fileContent.getLength() <= 1) return;
    int iter = 0;
    parse(fileContent.substring(1), tree, tree.getRoot(), iter);
}