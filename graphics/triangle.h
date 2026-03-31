#pragma once
#include "Vector3.h"
#include <iostream>
class triangle{
    public:
    Vector3 ** vertex = new Vector3 * [3];
    Vector3 getVertex(int index);
    Vector3 getNormal();
    Vector3 getCenter();
    void setVertex(int index, Vector3* newVertex);
};