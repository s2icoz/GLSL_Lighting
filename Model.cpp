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
    glmDraw(this->ptr, GLM_SMOOTH | GLM_MATERIAL);
}