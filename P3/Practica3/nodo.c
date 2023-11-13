#include "nodo.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
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
    vector<Nodo*> hijos = children;
    Nodo* child;
    for(int i=0;i<hijos.size();i++){
        child=hijos[i];
        if(dynamic_cast<Malla*>(child)!=nullptr){
            dynamic_cast<Malla*>(child)->drawSmooth();
        }else if(dynamic_cast<Traslacion*>(child)!=nullptr){
            dynamic_cast<Traslacion*>(child)->draw();
        }else if(dynamic_cast<Rotacion*>(child)!=nullptr){
            dynamic_cast<Rotacion*>(child)->draw();
        }else if(dynamic_cast<Escalado*>(child)!=nullptr){
            dynamic_cast<Escalado*>(child)->draw();
        }
    }
}