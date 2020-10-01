#include "NaveEspacial.h"

NaveEspacial::NaveEspacial() {};

void NaveEspacial::DibujarNave(float x, float y, float z) {
	float naveH = 1.4;
	glPushMatrix();
		glTranslatef(x, y, z+naveH);
		glutSolidCone(0.4, 0.4, 20, 20);
		glTranslatef(0, 0, -naveH);
		glutSolidCylinder(0.4, naveH, 20, 20);
	glPopMatrix();
}