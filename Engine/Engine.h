#ifndef ENGINE_H
#define ENGINE_H
#include "../XmlParser/XmlParser.h"
#include "../XmlTree/XmlTree.h"
#include "../XmlPath/XmlPath.h"

class Engine {
    XmlParser parser;
    XmlTree tree;
    bool hasChanged = false;
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
    void setText(const String& id);
    void removeAttribute(const String& id, const String& key);
    void addChild(const String& id, const String& type);
    void removeElement(const String& parentId, const String& childId);
    void remove(const String& id);
    void xmlPath(const String& xmlPath);
    void printDescendants(const String& id);
    bool fileIsOpened() const;
public:
    void run();
};

#endif