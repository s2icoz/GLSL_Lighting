#include "Model.h"
#include <iostream>

Model::Model(char path[23]) {
    this->ptr = NULL;
    if (!this->ptr) {
        this->ptr = glmReadOBJ(path);
        if (!this->ptr)
            exit(0);    //Inicialización fallida

        glmUnitize(this->ptr);
        glmFacetNormals(this->ptr);
        glmVertexNormals(this->ptr, 90.0);
    }
}

void Model::draw() {
    GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
    GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
    GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
    GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
    GLfloat material_Se = 20.0f;

    /*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);*/

    glmDraw(this->ptr, GLM_SMOOTH | GLM_MATERIAL);
}