//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librería

#include "Model.h"

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
    cwc::glShaderManager SM;
    cwc::glShader* shader;
    cwc::glShader* shader1; //Para Textura: variable para abrir los shader de textura
    GLuint ProgramObject;
    clock_t time0, time1;
    float timer010;  // timer counting 0->1->0
    bool bUp;        // flag if counting up or down.
    GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
    GLuint texid, texRocket; //*** Para Textura: variable que almacena el identificador de textura

    Model* player;      /*Puntero para referirse al modelo que actualmente se puede mover*/
    Model* objs[5];     /* Objetos en posiciones del arreglo
                        [0] = astronauta
                        [1] = casco
                        [2] = cohete
                        [3] = grua //Dibujado anteriormente
                        [4] = arbol*/

    float vMovCam;      // Velocida de movimiento de la camara
    float posCam[3];    /*Valores de ejes en el posCam[]
                        [0] -> X
                        [1] -> Y
                        [2] -> Z*/

    bool movCam[6];     /*Valores de lados de ejes en el movCam[]
                        [0] -> X izquierda
                        [1] -> X derecha
                        [2] -> Y arriba
                        [3] -> Y abajo
                        [4] -> Z adentro
                        [5] -> Z afuera*/

public:
	myWindow(){}

    //*** Para movimiento de camara: aqui adiciono un movimientos para cada tecla
    void moverCamara() {
        //*** Para camara: Movimiento X
        if (movCam[0]) {
            posCam[0] = posCam[0] + (0.1 * vMovCam);
        }
        if (movCam[1]) {
            posCam[0] = posCam[0] - (0.1 * vMovCam);
        }

        //*** Para camara: Movimiento Y
        if (movCam[2]) {
            posCam[1] = posCam[1] + (0.1 * vMovCam);
        }
        if (movCam[3]) {
            posCam[1] = posCam[1] - (0.1 * vMovCam);
        }

        //*** Para camara: Movimiento Z
        if (movCam[4]) {
            posCam[2] = posCam[2] + (0.1 * vMovCam);
        }
        if (movCam[5]) {
            posCam[2] = posCam[2] - (0.1*vMovCam);
        }
        glTranslatef(posCam[0], posCam[1], posCam[2]);
    }

	//*** Para Textura: aqui adiciono un método que abre la textura en JPG
	void initialize_textures(void)
	{
        glGenTextures(1, &texRocket);
        glBindTexture(GL_TEXTURE_2D, texRocket);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // Cargando textura del cohete
        FIBITMAP* bitmapRocket = FreeImage_Load(
            FreeImage_GetFileType("./Mallas/rocket/rocket.jpg", 0),
            "./Mallas/rocket/rocket.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura
        FIBITMAP* pImageRocket = FreeImage_ConvertTo32Bits(bitmapRocket);
        int nWidthRocket = FreeImage_GetWidth(pImageRocket);
        int nHeightRocket = FreeImage_GetHeight(pImageRocket);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidthRocket, nHeightRocket,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImageRocket));


        FreeImage_Unload(pImageRocket);

		glEnable(GL_TEXTURE_2D);
	}


	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      glPushMatrix();
	  //glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);

      if (shader) shader->begin();
          moverCamara();
          glPushMatrix();

              glPushMatrix();
                objs[0]->move();
                  
                  glTranslatef(0, -1, 3);
                  glRotatef(180, 0, 1, 0);
                  glScalef(0.6, 0.6, 0.6);
                  objs[0]->draw(GLM_SMOOTH | GLM_MATERIAL);
              glPopMatrix();

              glPushMatrix();
                objs[1]->move();

                  glTranslatef(1.5, -1.5, 3);
                  glScalef(1, 1, 1);
                  objs[1]->draw(GLM_SMOOTH | GLM_MATERIAL);
              glPopMatrix();

              /*glPushMatrix();
                objs[2]->move();

                  glTranslatef(3, 5, -3);
                  glScalef(7, 7, 7);
                  objs[2]->draw(GLM_SMOOTH | GLM_MATERIAL);
              glPopMatrix();*/

              glPushMatrix();
                objs[3]->move();

                  glTranslatef(0, 5, -3);
                  glScalef(7, 7, 7);
                  objs[3]->draw(GLM_SMOOTH | GLM_MATERIAL);
              glPopMatrix();

              glPushMatrix();
                objs[4]->move();

                  glTranslatef(-5, 0, -1);
                  objs[4]->draw(GLM_SMOOTH | GLM_MATERIAL);
              glPopMatrix();

		  glPopMatrix();

      if (shader) shader->end();

	  //*** Para Textura: llamado al shader para objetos texturizados
	  if (shader1) shader1->begin();

          glPushMatrix();
              objs[2]->move();

              glTranslatef(3, 5, -3);
              glScalef(7, 7, 7);
              glBindTexture(GL_TEXTURE_2D, texRocket);
              objs[2]->draw(GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
          glPopMatrix();

	  if (shader1) shader1->end();


      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.1f, 0.5f, 0.5f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

	 //*** Para Textura: abre los shaders para texturas
		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

	  //Abrir mallas

      objs[0] = new Model("./Mallas/astronaut/astronaut.obj");
      objs[1] = new Model("./Mallas/casco/casco.obj");
      objs[2] = new Model("./Mallas/rocket/rocket1.obj");
      objs[3] = new Model("./Mallas/grua/grua.obj");
      objs[4] = new Model("./Mallas/tree/tree.obj");

      //*** Para player: Se establece el modelo del astronauta como jugador inicial.
      player = objs[0];
 
	  //*** Para Textura: abrir archivo de textura
	  initialize_textures();
      DemoLight();

      //*** Para camara: posicionamiento-movimiento
      vMovCam = 1.0;                        // Velocidad inicial de la camara
      posCam[0] = posCam[1]= posCam[2] = 0; // Posicion inicial de la camara
      movCam[0] = movCam[1] = false;        // Movimientos en X
      movCam[2] = movCam[3] = false;        // Movimientos en Y
      movCam[4] = movCam[5] = false;        // Movimientos en Z
	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(120,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		}

        //*** Para camara:
        // Movimiento en X
        if (cAscii == 'a')
            movCam[0] = true;
        else if (cAscii == 'd')
            movCam[1] = true;
        // Movimiento en Y
        if (cAscii == 'w')
            movCam[3] = true;
        else if (cAscii == 's')
            movCam[2] = true;
        // Movimiento en Z
        if (cAscii == 'q')
            movCam[4] = true;
        else if (cAscii == 'e')
            movCam[5] = true;

        //*** Para player:
        // Movimiento en X
        if (cAscii == 'j')
            player->mov[0] = true;
        else if (cAscii == 'l')
            player->mov[1] = true;
        // Movimiento en Y
        if (cAscii == 'k')
            player->mov[3] = true;
        else if (cAscii == 'i')
            player->mov[2] = true;
        // Movimiento en Z
        if (cAscii == 'u')
            player->mov[4] = true;
        else if (cAscii == 'o')
            player->mov[5] = true;
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      //*** Para camara:
      // Movimiento en X
      if (cAscii == 'a')
          movCam[0] = false;
      else if (cAscii == 'd')
          movCam[1] = false;
      // Movimiento en Y
      if (cAscii == 'w')
          movCam[3] = false;
      else if (cAscii == 's')
          movCam[2] = false;
      // Movimiento en Z
      if (cAscii == 'q')
          movCam[4] = false;
      else if (cAscii == 'e')
          movCam[5] = false;

      //*** Para player:
      // Movimiento en X
      if (cAscii == 'j')
          player->mov[0] = false;
      else if (cAscii == 'l')
          player->mov[1] = false;
      // Movimiento en Y
      if (cAscii == 'k')
          player->mov[3] = false;
      else if (cAscii == 'i')
          player->mov[2] = false;
      // Movimiento en Z
      if (cAscii == 'u')
          player->mov[4] = false;
      else if (cAscii == 'o')
          player->mov[5] = false;

      /*if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();*/
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     /*glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);*/

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

