#include "Arbolito.h"

Arbolito::Arbolito() {};

void Arbolito::DibujarArbolito(float x, float y, float z) {
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(x, y, z-1);
		glutSolidCylinder(0.4, 1.4, 20, 20);
		glTranslatef(0, 0, 1.4);
		glutSolidTorus(0.5, 0.3, 20, 20);
	glPopMatrix();
}

void Arbolito::DibujarArbolitoRoble(float x, float y, float z) {
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(x, y, z);
		glutSolidCylinder(0.4, 2.2, 20, 20);
		glTranslatef(0, 0, 1.7);
		glutSolidTorus(0.55, 0.4, 20, 20);
		glTranslatef(0, 0, 0.8);
		glutSolidTorus(0.50, 0.4, 20, 20);
		glTranslatef(0, 0, 0.5);
		glutSolidCone(0.8, 0.9, 20, 20);
	glPopMatrix();
}