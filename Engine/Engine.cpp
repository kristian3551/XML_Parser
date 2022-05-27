#include "Engine.h"
#include <iostream>
using namespace std;
#include "../helperClasses/String/String.h"

const String END_OF_PROGRAM = "END_OF_PROGRAM";

void printDelimiter() {
    cout << "----------------------" << endl;
}
void Engine::openFile(const String& filePath) {
    if(parser.getFilePath() != String()) {
        cout << "File has been already opened! Close it and try again!" << endl;
        return;
    }
    if(!filePath.endsWith(".xml")) {
        cout << "Wrong file format" << endl;
        return;
    }
    parser = XmlParser(filePath);
    parser.parseTree(tree);
    cout << "Successfully opened " << filePath << endl;
}
void Engine::closeFile() {
    if(parser.getFilePath() != String()) {
        parser.setFilePath(String());
        tree.clear();
        cout << "Successfully closed file!" << endl;
        return;
    }
    cout << "File hasn't been opened!" << endl;
}
void Engine::saveFile() {
    if(parser.getFilePath() == String()) {
        cout << "File hasn't been opened!" << endl;
        return;
    }
    tree.saveInFile(parser.getFilePath());
    cout << "Successfully saved " << parser.getFilePath() << endl;
}
void Engine::saveAs(const String& filePath) {
    if(parser.getFilePath() == String()) {
        cout << "File hasn't been opened!" << endl;
        return;
    }
    tree.saveInFile(filePath);
    cout << "Successfully saved file in " << parser.getFilePath() << endl;
}
void Engine::help() {
    cout << "Some help for you!" << endl;
}
bool Engine::exit() {
    if(parser.getFilePath() != String()) {
        cout << "You have an open file with unsaved changes, please select close or save first." << endl;
        return false;
    }
    return true;
}
void Engine::print() {
    if(parser.getFilePath() == String()) {
        cout << "File hasn't been opened!" << endl;
        return;
    }
    tree.print();
}
void Engine::printAttribute(const String& id,
    const String& key) {
    try {
        bool res = tree.printAttribute(id, key);
        if(!res) cout << "There is no such attribute to element " << id << endl;
        cout << endl;
    }
    catch(const String& str) {
        cout << str << endl;
    }
}
void Engine::setAttribute(const String& id, const String& key,
    const String& value) {
    try {
        tree.setAttribute(id, key, value);
    }
    catch(const String& str) {
        cout << str << endl;
        return;
    }
    
    cout << "Successfully set attribute " << key << " to " << value << endl;
}
void Engine::printChildren(const String& id) {
    try {
        tree.printChildren(id);
    }
    catch(const String& str) {
        cout << str << endl;
    }
}
void Engine::printChildByIndex(const String& id, int index) {
    try {
        const XmlElement* el = tree.getChildByIndex(id, index);
        el->print(cout);
    }
    catch(const String& str) {
        cout << str << endl;
    }
}
void Engine::printText(const String& id) {
    XmlElement* el = tree.getElement(id);
    if(el == nullptr) {
        cout << "There is no such element" << endl;
        return;
    }
    cout << el->getText() << endl;
}
void Engine::removeAttribute(const String& id, const String& key) {
    try {
        bool res = tree.deleteAttribute(id, key);
        if(res) cout << "Successfully removed attribute to an XML element" << endl;
        else cout << "Attribute removed unsuccessfully" << endl;
    }
    catch(const String& str) {
        cout << str << endl;
    }
}
void Engine::addChild(const String& id, const String& type, const String& textContent) {
    XmlElement el(type, "dId", textContent);
    try {
        tree.addChild(id, el);
    }
    catch(const String& str) {
        cout << str << endl;
        return;
    }
    cout << "Successfully added child." << endl;
}
void Engine::removeElement(const String& parentId, const String& childId) {
    bool res = tree.removeChild(parentId, childId);
    if(res) cout << "Successfully removed child of element " << parentId << endl;
    else cout << "Child removed unsuccessfully!" << endl;
}
void Engine::run() {
    cout << "Welcome to XML Parser app. To continue, please enter a command or type \"\" help for more information." << endl;
    String input;
    while(input != END_OF_PROGRAM) {
        cout << "> ";
        cin >> input;
        ArrayList<String> parts = input.split(" ");
        String command = parts[0];
        try
        {
            if(command.equals("open")) {
            openFile(parts[1]);
        }
        else if(command.equals("close")) {
            closeFile();
        }
        else if(command.equals("save")) {
            saveFile();
        }
        else if(command.equals("saveas")) {
            saveAs(parts[1]);
        }
        else if(command.equals("help")) {
            help();
        }
        else if(command.equals("exit")) {
            if(exit()) input = END_OF_PROGRAM;
        }
        else if(command.equals("print")) {
            print();
        }
        else if(command.equals("select")) {
            printAttribute(parts[1], parts[2]);
        }
        else if(command.equals("set")) {
            setAttribute(parts[1], parts[2], parts[3]);
        }
        else if(command.equals("children")) {
            printChildren(parts[1]);
        }
        else if(command.equals("child")) {
            printChildByIndex(parts[1], atoi(parts[2].toString()));
        }
        else if(command.equals("text")) {
            printText(parts[1]);
        }
        else if(command.equals("delete")) {
            removeAttribute(parts[1], parts[2]);
        }
        else if(command.equals("newchild")) {
            if(parts.getSize() == 3) {
                addChild(parts[1], parts[2]);
            }
            else if(parts.getSize() == 4) {
                addChild(parts[1], parts[2], parts[3]);
            }
        }
        else if(command.equals("removechild")) {
            removeElement(parts[1], parts[2]);
        }
        else if(command.equals("clear")) {
            system("CLS");
        }
        }
        catch(int value)
        {
            cout << "Input error!" << endl;
        }
        
        printDelimiter();
    }
    cout << "Exiting program..." << endl;
}