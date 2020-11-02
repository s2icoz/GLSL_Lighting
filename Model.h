#include "glm.h"

class Model {
protected:
    float vMov;         // Velocidad inicial del modelo
	float pos[3];		/*Valores de ejes en la posicion del modelo
                        [0] -> X
                        [1] -> Y
                        [2] -> Z*/
public:
	bool mov[6];        /*Valores de lados de ejes en el modelo
                        [0] -> X izquierda
                        [1] -> X derecha
                        [2] -> Y arriba
                        [3] -> Y abajo
                        [4] -> Z adentro
                        [5] -> Z afuera*/
    GLMmodel* ptr;
	Model(char[23]);

	void draw(int);
    void move();
};