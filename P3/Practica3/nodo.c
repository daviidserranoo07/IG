#include <vector>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "nodo.h"
#include "malla.h"
#include "rotacion.h"
#include "traslacion.h"
#include "escalado.h"

using namespace std;


Nodo::Nodo(){
    this->parent=NULL;
}

Nodo::Nodo(Nodo* parent, std::vector<Nodo*> children){
    this->parent=parent;
    this->children=children;
}

Nodo::Nodo(Nodo* parent){
    this->parent=parent;
}

void Nodo::setParent(Nodo* parent){
    this->parent=parent;
}

Nodo* Nodo::getParent(){
    return this->parent;
}

void Nodo::addChild(Nodo* child){
    children.push_back(child);
    child->setParent(this);
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

void Nodo::draw(){
    
}

void Nodo::drawJerarquia(){
    vector<Nodo*> hijos = children;
    Nodo* child=NULL;
    for(int i=0;i<hijos.size();i++){
        child=hijos[i];
        child->draw();
        if(child!=NULL){
            child->drawJerarquia();
        }
    }
    
    
}