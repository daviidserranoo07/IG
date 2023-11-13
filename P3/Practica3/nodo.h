#ifndef nodo_h
#define nodo_h

#include <vector>

class Nodo{
private:
    Nodo* parent;
    std::vector<Nodo*> children;
public:
    Nodo();
    Nodo(Nodo* parent);
    Nodo(Nodo* parent, std::vector<Nodo*> children);
    void setParent(Nodo* parent);
    Nodo* getParent();
    void addChild(Nodo* child);
    std::vector<Nodo*> getChildren();
    void removeChildren(Nodo* child);
    virtual void draw();
};

#endif