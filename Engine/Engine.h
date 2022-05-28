#ifndef ENGINE_H
#define ENGINE_H
#include "../XmlParser/XmlParser.h"
#include "../XmlTree/XmlTree.h"
#include "../XmlPath/XmlPath.h"

class Engine {
    XmlParser parser;
    XmlTree tree;
    void openFile(const String&);
    void closeFile();
    void saveFile();
    void saveAs(const String&);
    void help();
    bool exit();
    void print();
    void printAttribute(const String& id,
    const String& key);
    void setAttribute(const String& id, const String& key,
    const String& value);
    void printChildren(const String& id);
    void printParent(const String& id);
    void printChildByIndex(const String& id, int index);
    void printText(const String& id);
    void setText(const String& id, const String& text);
    void removeAttribute(const String& id, const String& key);
    void addChild(const String& id, const String& type, const String& textContent = "defaultContent");
    void removeElement(const String& parentId, const String& childId);
    void remove(const String& id);
    void xmlPath(const String& xmlPath);
    bool fileIsOpened() const;
public:
    void run();
};

#endif