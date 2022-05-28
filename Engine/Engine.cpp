#include "Engine.h"
#include <iostream>
using namespace std;
#include "../helperClasses/String/String.h"

const String END_OF_PROGRAM = "END_OF_PROGRAM";

void printDelimiter() {
    cout << "----------------------" << endl;
}
bool Engine::fileIsOpened() const {
    if(!parser.fileIsOpened()) {
        cout << "File hasn't been opened!" << endl;
        return false;
    }
    return true;
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
    tree.saveInFile(parser.getFilePath());
    cout << "Successfully saved " << parser.getFilePath() << endl;
}
void Engine::saveAs(const String& filePath) {
    tree.saveInFile(filePath);
    cout << "Successfully saved file in " << parser.getFilePath() << endl;
}
void Engine::help() {
    cout << "The following commands are supported: " << endl;
    cout << "  open <fileName>                    \t\t\topens <fileName>" << endl;
    cout << "  close                              \t\t\tcloses currently opened file" << endl;
    cout << "  save                               \t\t\tsaves the currently open file" << endl;
    cout << "  saveas <fileName>                  \t\t\tsaves the currently open file in <fileName>" << endl;
    cout << "  help                               \t\t\tprints this information" << endl;
    cout << "  exit                               \t\t\texits the program" << endl;
    cout << "  print                              \t\t\tprints the opened file" << endl;
    cout << "  select <id> <key>                  \t\t\tprints attribute to an element with <id> by key" << endl;
    cout << "  set <id> <key> <value>             \t\t\tsets attribute to an element with <id> by key and value" << endl;
    cout << "  children <id>                      \t\t\topens file" << endl;
    cout << "  child <id> <n>                     \t\t\tprints the n-th child of an element with <id>" << endl;
    cout << "  text <id>                          \t\t\tprints text of element with <id>" << endl;
    cout << "  settext <id> <newText>             \t\t\tsets textContent of element with <id> to <newText>" << endl;
    cout << "  delete <id> <key>                  \t\t\tremoves attribute <key> from element with <id>" << endl;
    cout << "  addchild <id> <type> <?textContent>\t\t\tcreates child element if <type> to element <id> (textContent is optional)" << endl;
    cout << "  removechild <parentId> <childId>   \t\t\tremoves element with <childId> given <parentId>" << endl;
    cout << "  remove <id>                        \t\t\tremoves element with <id>" << endl;
    cout << "  xmlpath <xmlPath>                  \t\t\tperforms basic XMLPath requests" << endl;
    
}
bool Engine::exit() {
    if(parser.getFilePath() != String()) {
        cout << "You have an open file with unsaved changes, please select close or save first." << endl;
        return false;
    }
    return true;
}
void Engine::print() {
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
void Engine::printParent(const String& id) {
    try {
        const XmlElement* el = tree.getParent(id);
        el->print(cout);
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
    const XmlElement* el = tree.getElement(id);
    if(el == nullptr) {
        cout << "There is no such element" << endl;
        return;
    }
    cout << el->getText() << endl;
}
void Engine::setText(const String& id, const String& text) {
    if(parser.getFilePath() == String()) {
        
    }
    try {
        tree.setText(id, text);
        cout << "Successfully set textContent to " << id << endl;
    }
    catch(const String& str) {
        cout << str << endl;
    }
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
void Engine::remove(const String& id) {
    try {
        tree.remove(id);
        cout << "Successfully removed element" << endl;
    }
    catch(const String& str)
    {
        cout << str << endl;
    }
    
}
void Engine::xmlPath(const String& xmlPath) {
    XmlPath path(xmlPath);
    const ArrayList<XmlElement*> elementsToFind = path.getElements(tree);
    cout << "Elements: " << endl;
    for(int i = 0; i < elementsToFind.getSize(); i++) {
        elementsToFind[i]->print(cout);
    }
}
void Engine::run() {
    cout << "Welcome to XML Parser app. To continue, please enter a command or type \"help\" for more information." << endl;
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
            if(fileIsOpened()) closeFile();
        }
        else if(command.equals("save")) {
            if(fileIsOpened()) saveFile();
        }
        else if(command.equals("saveas")) {
            if(fileIsOpened()) saveAs(parts[1]);
        }
        else if(command.equals("help")) {
            help();
        }
        else if(command.equals("exit")) {
            if(exit()) input = END_OF_PROGRAM;
        }
        else if(command.equals("print")) {
            if(fileIsOpened()) print();
        }
        else if(command.equals("select")) {
            if(fileIsOpened()) printAttribute(parts[1], parts[2]);
        }
        else if(command.equals("set")) {
            if(fileIsOpened()) setAttribute(parts[1], parts[2], parts[3]);
        }
        else if(command.equals("children")) {
           if(fileIsOpened()) printChildren(parts[1]);
        }
        else if(command.equals("child")) {
            if(fileIsOpened()) printChildByIndex(parts[1], atoi(parts[2].toString()));
        }
        else if(command.equals("text")) {
            if(fileIsOpened()) printText(parts[1]);
        }
        else if(command.equals("delete")) {
            if(fileIsOpened()) removeAttribute(parts[1], parts[2]);
        }
        else if(command.equals("newchild")) {
            if(parts.getSize() == 3) {
                if(fileIsOpened()) addChild(parts[1], parts[2]);
            }
            else if(parts.getSize() == 4) {
                if(fileIsOpened()) addChild(parts[1], parts[2], parts[3]);
            }
        }
        else if(command.equals("removechild")) {
            if(fileIsOpened()) removeElement(parts[1], parts[2]);
        }
        else if(command.equals("parent")) {
            if(fileIsOpened()) printParent(parts[1]);
        }
        else if(command.equals("remove")) {
            if(fileIsOpened()) remove(parts[1]);
        }
        else if(command.equals("clear")) {
            system("CLS");
        }
        else if(command.equals("settext")) {
            if(fileIsOpened()) setText(parts[1], parts[2]);
        }
        else if(command.equals("xmlpath")) {
            if(fileIsOpened()) xmlPath(parts[1]);
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