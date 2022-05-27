#include <iostream>
using namespace std;
#include "helperClasses/Dictionary.hpp"
#include "helperClasses/String/String.h"
#include "./XmlElement/XmlElement.h"
#include "./XmlTree/XmlTree.h"
#include "./XmlParser/XmlParser.h"
#include "./Engine/Engine.h"

int main() {
    Engine engine;
    engine.run();
    // XmlParser parser("example.xml");
    // XmlElement root("wrapper", "1");
    // XmlTree tree(root);
    // parser.parseTree(tree);
    // tree.setAttribute("defaultId_8", "lang", "BG");
    // tree.clear();
    // parser.parseTree(tree);
    // tree.print();
}