#include "nodo.h"
#include <vector>
#include <stdlib.h>

using namespace std;


Nodo::Nodo(){
    this->parent=NULL;
}

Nodo::Nodo(Nodo* parent, std::vector<Nodo*> children){
    this->parent=parent;
    this->children=children;
}

void Nodo::setParent(Nodo* parent){
    this->parent=parent;
}

Nodo* Nodo::getParent(){
    return this->parent;
}

void Nodo::addChild(Nodo* child){
    children.push_back(child);
}

vector<Nodo*> Nodo::getChildren(){
    return children;
}

void Nodo::removeChildren(Nodo* child){
    vector<Nodo*>::iterator it;
    for(it=children.begin();it<children.end();++it){
        if(*it==child){
            children.erase(it);
        }
    }
}