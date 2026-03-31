#pragma once
#include "triangle.h"
#include <iostream>
class Model3D{
    public:

    int NVertex;
    int NFaces;
    int * adressOfVertex;

    Vector3 * Vertex;
    triangle * faces;

    void defineVertex(Vector3 * argVertex);
    void defineFaces(triangle * argFaces);

    
    Vector3 getVertex(int index);
    triangle getFace(int index);
    void setVertex(int index,Vector3 argVertex);
    void setFaces(int facesC, int * argIndexFaces);

    Model3D rotatedModel(Vector3 axis, double angle);
    Model3D offset(Vector3 offset);
    Model3D& operator=(const Model3D& other);
    /*Model3D(int numberofVertex,int numberofFaces,){
        Vertex;
        faces;
    }
    */
};