#include "triangle.h"


    Vector3 triangle::getVertex(int index){
        return *(vertex[index]);
    }
    Vector3 triangle::getNormal(){
        return Vector3::crossproduct((*this).getVertex(1) - (*this).getVertex(0),(*this).getVertex(2) - (*this).getVertex(1));
    }
    Vector3 triangle::getCenter(){
        return ((*this).getVertex(0)+(*this).getVertex(1)+(*this).getVertex(2))/3.0;
    }
    void triangle::setVertex(int index, Vector3* newVertex){
        vertex[index] = newVertex;
    }