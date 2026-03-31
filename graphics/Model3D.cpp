#include "Model3D.h"
using namespace std;

    void Model3D::defineVertex(Vector3 * argVertex){
        Vertex = argVertex;
    }

    void Model3D::defineFaces(triangle * argFaces){
            faces = argFaces;
    }

    Vector3 Model3D::getVertex(int index){
        return Vertex[index];
    }

    triangle Model3D::getFace(int index){
        return faces[index];
    }

    void Model3D::setVertex(int index,Vector3 argVertex){
        Vertex[index] = argVertex;
    }

    void Model3D::setFaces(int facesC,int * argIndexFaces){
        (*this).adressOfVertex = new int[facesC*3];
        //std::cout <<std::endl<< "ASSIGNING ADRESS OF VERTEX "<<std::endl;
        for(int i = 0; i< facesC*3;i++){
            (*this).adressOfVertex[i] = argIndexFaces[i];
            //std::cout << argIndexFaces[i]<< " : ";
        }

        (*this).faces = new triangle[facesC];
        //std::cout << "The Vertex Faces "<<std::endl;
        for(int i = 0; i< facesC; i++){
            
            for(int j = 0; j< 3; j++){
                //std::cout << argIndexFaces[0]<<" "<< (*this).Vertex[argIndexFaces[i*3+j]-1]<< " " << i*3+j;
            (*this).faces[i].setVertex(j ,&((*this).Vertex[argIndexFaces[i*3+j]-1]));
            }
            //std::cout << std::endl;
        }
    }

    Model3D Model3D::rotatedModel(Vector3 axis, double angle){
        //std::cout << "ROTATING " << (*this).adressOfVertex[0] << std::endl;
        Model3D rModel;
        
        rModel = *this;
        
        for(int i = 0 ; i < rModel.NVertex; i++){
            rModel.Vertex[i] = rModel.Vertex[i].rotation(axis,angle);
        }
        //cout << "is okay? "<< rModel.getVertex(0)<<  endl;
        return rModel;
    }

    Model3D Model3D::offset(Vector3 offset){
        Model3D oModel;
        oModel = *this;
        for(int i = 0 ; i < oModel.NVertex; i++){
            oModel.Vertex[i] = oModel.Vertex[i] + offset;
        }
        return oModel;
    }

    Model3D& Model3D::operator=(const Model3D& other){
    //std::cout << "ASSIGNING " << other.adressOfVertex[0] << std::endl;
     (*this).NVertex = other.NVertex;
     (*this).NFaces = other.NFaces;
     (*this).Vertex = new Vector3[(*this).NVertex];
     //std::cout << "warn? vertex" << std::endl;
    for(int i =0; i < (*this).NVertex; i++){
        (*this).Vertex[i] = other.Vertex[i];
        //std::cout << (*this).Vertex[i] << std::endl;
    }


    Model3D::setFaces((*this).NFaces,other.adressOfVertex);
    return *this;
    }