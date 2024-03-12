#include "mesh3D.h"
#include <vector>

using namespace std;

vector<float> Mesh3D::getVertices(){
    return this->vertices_ply;
}

vector<int> Mesh3D::getCaras(){
    return this->caras_ply;
}

vector<float> Mesh3D::getNormalesVertice(){
    return this->normalesVertice;
}

void Mesh3D::setVertices(vector<float> vertices){
    this->vertices_ply=vertices;
}

void Mesh3D::setCaras(vector<int> caras){
    this->caras_ply=caras;
}

void Mesh3D::setNormalesVertice(vector<float> normales){
    this->normalesVertice=normales;
}