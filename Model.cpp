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
    this->vMov = 1.0;
    this->pos[0] = this->pos[1] = this->pos[2] = 0;
    this->mov[0] = this->mov[1] = false;
    this->mov[2] = this->mov[3] = false;
    this->mov[4] = this->mov[5] = false;
}

void Model::draw(int draw_params) {
    GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
    GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
    GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
    GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
    GLfloat material_Se = 20.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

    glmDraw(this->ptr, draw_params);
}

void Model::move() {
    //*** Para modelo: Movimiento X
    if (mov[0]) {
        pos[0] = pos[0] - (0.1 * vMov);
    }
    if (mov[1]) {
        pos[0] = pos[0] + (0.1 * vMov);
    }

    //*** Para modelo: Movimiento Y
    if (mov[2]) {
        pos[1] = pos[1] + (0.1 * vMov);
    }
    if (mov[3]) {
        pos[1] = pos[1] - (0.1 * vMov);
    }

    //*** Para modelo: Movimiento Z
    if (mov[4]) {
        pos[2] = pos[2] - (0.1 * vMov);
    }
    if (mov[5]) {
        pos[2] = pos[2] + (0.1 * vMov);
    }
    glTranslatef(pos[0], pos[1], pos[2]);
}