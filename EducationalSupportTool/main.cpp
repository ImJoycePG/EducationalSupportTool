

#include <iomanip>
#include "Libs.h"

#include "GL/glui.h"

#include "ctexture.h"
#include "timer.h"
#include "md2.h"

static float ypoz = 0;

int main_window;
int genID = 1;

//Cords Personaje Principal

float PersonaTorsoX = 0;
float PersonaTorsoY = -3;
float PersonaTorsoZ = 0;

float PersonaTorsoAngle = 0;

float PersonaCabezaX = 0;
float PersonaCabezaY = 0;
float PersonaCabezaZ = 0;

float PersonaBrazoIzqX = 0;
float PersonaBrazoIzqY = 0;
float PersonaBrazoIzqZ = 0;

float PersonaBrazoDerX = 0;
float PersonaBrazoDerY = 0;
float PersonaBrazoDerZ = 0;

float PersonaMuslosX = 0;
float PersonaMuslosY = 0;
float PersonaMuslosZ = 0;

float PersonaPiernaIzqX = 0;
float PersonaPiernaIzqY = 0;
float PersonaPiernaIzqZ = 0;

float PersonaPiernaDerX = 0;
float PersonaPiernaDerY = 0;
float PersonaPiernaDerZ = 0;

float PersonaPieIzqX = 0;
float PersonaPieIzqY = 0;
float PersonaPieIzqZ = 0;

float PersonaPieDerX = 0;
float PersonaPieDerY = 0;
float PersonaPieDerZ = 0;

float PersonaPiernaIzqAngle = 0;
float PersonaPiernaIzqLimit = 20;

float PersonaPiernaDerAngle = 0;
float PersonaPiernaDerLimit = -20;

float PersonaBrazoIzqAngle = 0;
float PersonaBrazoIzqLimit = 20;

float PersonaBrazoDerAngle = 0;
float PersonaBrazoDerLimit = -20;

//Coords Among US
float AmongUsX = 8;
float AmongUsY = -3;
float AmongUsZ = 7;

//Coords Fall Guys
float FallGuysX = -16;
float FallGuysY = -3;
float FallGuysZ = 22;


//Cords Camara
int CameraX = 0;
int CameraY = 2; //6
int CameraZ = -10;
int CameraCenterX = 0;
int CameraCenterY = 0; //4
int CameraCenterZ = 0;
int CameraUpX = 0;
int CameraUpY = 1;
int CameraUpZ = 0;
//Cords SkyBox
float SkyBoxX = 0;
float SkyBoxY = 0;
float SkyBoxZ = 0;
float SkyBoxAngel = 90;


//Modelo GLM - OBJ
GLMmodel* skybox = NULL;
GLMmodel* terrain = NULL;
//Persona - Partes
GLMmodel* personCuerpo = NULL;
GLMmodel* personCabeza = NULL;
GLMmodel* personBrazoIzq = NULL;
GLMmodel* personBrazoDer = NULL;
GLMmodel* personAnteBrazoIzq = NULL;
GLMmodel* personAnteBrazoDer = NULL;
GLMmodel* personBrazoManoIzq = NULL;
GLMmodel* personBrazoManoDer = NULL;
GLMmodel* personMuslos = NULL;
GLMmodel* personPiernaIzq = NULL;
GLMmodel* personPieIzq = NULL;
GLMmodel* personPiernaDer = NULL;
GLMmodel* personPieDer = NULL;
//AMONG GUS -PARTES
GLMmodel* amongCuerpo = NULL;
GLMmodel* amongTorso = NULL;
GLMmodel* amongPiernaIz = NULL;
GLMmodel* amongPiernaDe = NULL;
//FALL GUYS
GLMmodel* fallguys = NULL;
GLMmodel* tree = NULL;

Texture	treeScenaryTexture[2];
Texture	treePersontexture[2];
Texture	treeAmongtexture[1];
Texture	treeFallGuystexture[1];
Texture treeTreeSceneTexture[1];

//Variable GLUI
GLUI* glui;
GLUI* gluiCongrulation;
GLUI* gluiFail;
GLUI* gluiSumaLvL1;
GLUI* gluiRestaLvL1;
GLUI_Panel* obj_panel;

bool loadScenaryTextures() {
	int i;
	if (LoadTGA(&treeScenaryTexture[0], (char*)"models/skybox/skyTextures.tga") &&
		LoadTGA(&treeScenaryTexture[1], (char*)"models/terrain/terrain.tga")) {
		for (i = 0; i < 2; i++) {
			glGenTextures(1, &treeScenaryTexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeScenaryTexture[i].bpp / 8, treeScenaryTexture[i].width,
				treeScenaryTexture[i].height, 0, treeScenaryTexture[i].type, GL_UNSIGNED_BYTE,
				treeScenaryTexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeScenaryTexture[i].imageData)
			{
				free(treeScenaryTexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool loadPersonTextures() {
	int i;
	if (LoadTGA(&treePersontexture[0], (char*)"models/boys/personaje.tga") && 
		LoadTGA(&treePersontexture[1], (char*)"models/boys/DIDITEXTURE.tga")) {
		for (i = 0; i < 3; i++) {
			glGenTextures(1, &treePersontexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treePersontexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treePersontexture[i].bpp / 8, treePersontexture[i].width,
				treePersontexture[i].height, 0, treePersontexture[i].type, GL_UNSIGNED_BYTE,
				treePersontexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treePersontexture[i].imageData)
			{
				free(treePersontexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool loadAmongTextures() {
	int i;
	if (LoadTGA(&treeAmongtexture[0], (char*)"models/among us/amongD.tga")) {
		for (i = 0; i < 1; i++) {
			glGenTextures(1, &treeAmongtexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeAmongtexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeAmongtexture[i].bpp / 8, treeAmongtexture[i].width,
				treeAmongtexture[i].height, 0, treeAmongtexture[i].type, GL_UNSIGNED_BYTE,
				treeAmongtexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeAmongtexture[i].imageData)
			{
				free(treeAmongtexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool loadFallGuysTextures() {
	int i;
	if (LoadTGA(&treeFallGuystexture[0], (char*)"models/fallguys/targaD.tga")) {
		for (i = 0; i < 1; i++) {
			glGenTextures(1, &treeFallGuystexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeFallGuystexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeFallGuystexture[i].bpp / 8, treeFallGuystexture[i].width,
				treeFallGuystexture[i].height, 0, treeFallGuystexture[i].type, GL_UNSIGNED_BYTE,
				treeFallGuystexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeFallGuystexture[i].imageData)
			{
				free(treeFallGuystexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool loadTreeTextures() {
	int i;
	if (LoadTGA(&treeTreeSceneTexture[0], (char*)"models/tree/Tree.tga")) {
		for (i = 0; i < 1; i++) {
			glGenTextures(1, &treeTreeSceneTexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeTreeSceneTexture[i].bpp / 8, treeTreeSceneTexture[i].width,
				treeTreeSceneTexture[i].height, 0, treeTreeSceneTexture[i].type, GL_UNSIGNED_BYTE,
				treeTreeSceneTexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeTreeSceneTexture[i].imageData) {
				free(treeTreeSceneTexture[i].imageData);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);


	CTimer::GetInstance()->Initialize();
	CTextureManager::GetInstance()->Initialize();

	//Carga de texturas
	loadScenaryTextures();
	loadTreeTextures();
	loadPersonTextures();
	loadAmongTextures();
	loadFallGuysTextures();
}
void myGlutScenary() {
	glPushMatrix();
	glTranslatef(SkyBoxX, SkyBoxY, SkyBoxZ);
	//glScalef(2, 2, 2);
	glRotatef(SkyBoxAngel, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[0].texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glmDraw(skybox, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -4, 0);
	glScaled(150, 1, 150);
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[1].texID);
	glmDraw(terrain, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}
void myGlutPerson() {
	//Torso
	glPushMatrix();
	glTranslatef(PersonaTorsoX, PersonaTorsoY, PersonaTorsoZ);
	glRotatef(PersonaTorsoAngle, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
	glmDraw(personCuerpo, GLM_SMOOTH | GLM_TEXTURE);

		//Cabeza
		glPushMatrix();
		glTranslatef(PersonaCabezaX, PersonaCabezaY, PersonaCabezaZ);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
		glmDraw(personCabeza, GLM_SMOOTH | GLM_TEXTURE);
		glPopMatrix();

		//Brazo Izquierda
		glPushMatrix();
		glTranslatef(PersonaBrazoIzqX, PersonaBrazoIzqY, PersonaBrazoIzqZ);
		glRotatef(PersonaBrazoIzqAngle, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
		glmDraw(personBrazoIzq, GLM_SMOOTH | GLM_TEXTURE);

			//Brazo Izq - AnteBrazo
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
			glmDraw(personAnteBrazoIzq, GLM_SMOOTH | GLM_TEXTURE);
	
				//Brazo Izq - Mano
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
				glmDraw(personBrazoManoIzq, GLM_SMOOTH | GLM_TEXTURE);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		//Brazo Derecho
		glPushMatrix();
		glTranslatef(PersonaBrazoDerX, PersonaBrazoDerY, PersonaBrazoDerZ);
		glRotatef(PersonaBrazoIzqAngle, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
		glmDraw(personBrazoDer, GLM_SMOOTH | GLM_TEXTURE);

		//Brazo Derecho - AnteBrazo
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
			glmDraw(personAnteBrazoDer, GLM_SMOOTH | GLM_TEXTURE);

		//Brazo Derecho - Mano
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
				glmDraw(personBrazoManoDer, GLM_SMOOTH | GLM_TEXTURE);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		//Muslos
		glPushMatrix();
		glTranslatef(PersonaMuslosX, PersonaMuslosY, PersonaMuslosZ);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
		glmDraw(personMuslos, GLM_SMOOTH | GLM_TEXTURE);
			//Pierna Izquierda
			glPushMatrix();
			glTranslatef(PersonaPiernaIzqX, PersonaPiernaIzqY, PersonaPiernaIzqZ);
			glRotatef(PersonaPiernaIzqAngle, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
			glmDraw(personPiernaIzq, GLM_SMOOTH | GLM_TEXTURE);

				//Pie Izquierda
				glPushMatrix();
				glTranslatef(PersonaPieIzqX, PersonaPieIzqY, PersonaPieIzqZ);
				glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
				glmDraw(personPieIzq, GLM_SMOOTH | GLM_TEXTURE);
				glPopMatrix();
			glPopMatrix();

			//Pierna Derecha
			glPushMatrix();
			glTranslatef(PersonaPiernaDerX, PersonaPiernaDerY, PersonaPiernaDerZ);
			glRotatef(PersonaPiernaDerAngle, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
			glmDraw(personPiernaDer, GLM_SMOOTH | GLM_TEXTURE);

				//Pie Derecha
				glPushMatrix();
				glTranslatef(PersonaPieDerX, PersonaPieDerY, PersonaPieDerZ);
				glBindTexture(GL_TEXTURE_2D, treePersontexture[genID].texID);
				glmDraw(personPieDer, GLM_SMOOTH | GLM_TEXTURE);
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
}
void myGlutAmong() {
	//Torso
	glPushMatrix();
	glTranslatef(AmongUsX, AmongUsY, AmongUsZ);
	glScalef(0.2, 0.2, 0.2);
	glRotated(180, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treeAmongtexture[0].texID);
	glmDraw(amongTorso, GLM_SMOOTH | GLM_TEXTURE);

		//Cuerpo
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, treeAmongtexture[0].texID);
		glmDraw(amongCuerpo, GLM_SMOOTH | GLM_TEXTURE);
		glPopMatrix();


		//Pierna Izquierda
		glPushMatrix();
		//glRotatef(PersonaPiernaIzqAngle, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, treeAmongtexture[0].texID);
		glmDraw(amongPiernaIz, GLM_SMOOTH | GLM_TEXTURE);

			//Pie Derecha
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, treeAmongtexture[0].texID);
			glmDraw(amongPiernaDe, GLM_SMOOTH | GLM_TEXTURE);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}
void myGlutFallGuys() {

	glPushMatrix();

	glTranslatef(FallGuysX, FallGuysY, FallGuysZ);
	//glScalef(0.15, 0.15, 0.15);
	glRotated(180, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treeFallGuystexture[0].texID);
	glmDraw(fallguys, GLM_SMOOTH | GLM_TEXTURE);

	glPopMatrix();
}
void myGlutTrees() {

	glPushMatrix();
	glTranslatef(8, -3, 8);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, -3, 24);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, -3, 48);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-36, -3, 38);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-42, -3, 76);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-84, -3, 152);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -3, 40);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, -3, 85);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();


}
void myGlutDisplay(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CTimer::GetInstance()->Update();
	float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;

	gluLookAt(CameraX, CameraY, CameraZ, CameraCenterX, CameraCenterY, CameraCenterZ, CameraUpX, CameraUpY, CameraUpZ);

	myGlutScenary();
	myGlutTrees();
	myGlutPerson();
	myGlutAmong();
	myGlutFallGuys();

	//Void DrawModel - MD2
	/*
	ogro.DrawModel(bAnimated ? timesec : 0.0);
	*/
	//////////////////////

	glutSwapBuffers();
	glutPostRedisplay();
}
void myGlutReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void myGlutUpdate() {
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	SkyBoxAngel += 0.2;

	glutPostRedisplay();
}

void myControl_Button(int button) {
	if (button == 0) {
		gluiCongrulation->close();
	}
	if (button == 1) {
		gluiFail->close();
	}
	if (button == 2) {
		gluiFail->close();
	}
	if (button == 3) {
		gluiFail->close();
	}
}

void myControl_SumaLvL1(int control) {
	switch (control)
	{
	case 0:
		gluiSumaLvL1->close();
		gluiCongrulation = GLUI_Master.create_glui("Felicidades!", 0, 800, 500);
		gluiCongrulation->add_statictext(" ");
		gluiCongrulation->add_statictext("Felicidades, acabas de resolver bien la suma, sigue así!");
		gluiCongrulation->add_statictext(" ");
		gluiCongrulation->add_button("Aceptar", 0, myControl_Button);

		gluiCongrulation->set_main_gfx_window(main_window);
		break;

	case 1:
		gluiSumaLvL1->close();
		gluiFail = GLUI_Master.create_glui("Muy mal", 0, 800, 500);
		gluiFail->add_statictext(" ");
		gluiFail->add_statictext("Respuesta incorrecta, vuelve a intentarlo.");
		gluiFail->add_statictext(" ");
		gluiFail->add_button("Aceptar", 1, myControl_Button);

		gluiFail->set_main_gfx_window(main_window);
		break;

	case 2:
		gluiSumaLvL1->close();
		gluiFail = GLUI_Master.create_glui("Muy mal", 0, 800, 500);
		gluiFail->add_statictext(" ");
		gluiFail->add_statictext("Respuesta incorrecta, vuelve a intentarlo.");
		gluiFail->add_statictext(" ");
		gluiFail->add_button("Aceptar", 2, myControl_Button);

		gluiFail->set_main_gfx_window(main_window);
		break;
	case 3:
		gluiSumaLvL1->close();
		gluiFail = GLUI_Master.create_glui("Muy mal", 0, 800, 500);
		gluiFail->add_statictext(" ");
		gluiFail->add_statictext("Respuesta incorrecta, vuelve a intentarlo.");
		gluiFail->add_statictext(" ");
		gluiFail->add_button("Aceptar", 3, myControl_Button);

		gluiFail->set_main_gfx_window(main_window);
		break;
	}
}

void myControl_RestaLvL1(int control) {
	switch (control)
	{
	case 0:
		gluiRestaLvL1->close();
		gluiCongrulation = GLUI_Master.create_glui("Felicidades!", 0, 800, 500);
		gluiCongrulation->add_statictext(" ");
		gluiCongrulation->add_statictext("Felicidades, acabas de resolver bien la resta, sigue así!");
		gluiCongrulation->add_statictext(" ");
		gluiCongrulation->add_button("Aceptar", 0, myControl_Button);
		gluiCongrulation->set_main_gfx_window(main_window);
		break;

	case 1:
		gluiRestaLvL1->close();
		gluiFail = GLUI_Master.create_glui("Muy mal", 0, 800, 500);
		gluiFail->add_statictext(" ");
		gluiFail->add_statictext("Respuesta incorrecta, vuelve a intentarlo.");
		gluiFail->add_statictext(" ");
		gluiFail->add_button("Aceptar", 1, myControl_Button);

		gluiFail->set_main_gfx_window(main_window);
		break;

	case 2:
		gluiRestaLvL1->close();
		gluiFail = GLUI_Master.create_glui("Muy mal", 0, 800, 500);
		gluiFail->add_statictext(" ");
		gluiFail->add_statictext("Respuesta incorrecta, vuelve a intentarlo.");
		gluiFail->add_statictext(" ");
		gluiFail->add_button("Aceptar", 2, myControl_Button);
		gluiFail->set_main_gfx_window(main_window);

	case 3:
		gluiRestaLvL1->close();
		gluiFail = GLUI_Master.create_glui("Muy mal", 0, 800, 500);
		gluiFail->add_statictext(" ");
		gluiFail->add_statictext("Respuesta incorrecta, vuelve a intentarlo.");
		gluiFail->add_statictext(" ");
		gluiFail->add_button("Aceptar", 3, myControl_Button);
		gluiFail->set_main_gfx_window(main_window);
		break;
	}
}


void myGlutKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (PersonaPiernaIzqAngle >= 20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		if (PersonaPiernaIzqAngle <= -20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		PersonaPiernaIzqAngle = PersonaPiernaIzqAngle + PersonaPiernaIzqLimit;
		PersonaPiernaDerAngle = PersonaPiernaDerAngle + PersonaPiernaDerLimit;

		if (abs(PersonaTorsoX - AmongUsX) + abs(PersonaTorsoY - AmongUsY) + abs(PersonaTorsoZ - AmongUsZ) < 3.0f) {

			gluiSumaLvL1 = GLUI_Master.create_glui("Mision: Suma", 0, 800, 400);
			gluiSumaLvL1->add_statictext("Bienvenid@ a la mision de SUMA. Debes seleccionar el boton");
			gluiSumaLvL1->add_statictext("que contiene la respuesta correcta sino perderás contra");
			gluiSumaLvL1->add_statictext("el villano mas temido, el Astronauta.");
			gluiSumaLvL1->add_statictext("");
			gluiSumaLvL1->add_separator();
			gluiSumaLvL1->add_statictext("Suma: 5 + 5");
			gluiSumaLvL1->add_button("10", 0, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("5", 1, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("2", 2, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("8", 3, myControl_SumaLvL1);
			
			
			gluiSumaLvL1->set_main_gfx_window(main_window);

			PersonaTorsoZ -= 1;
			PersonaTorsoAngle = 0;
			CameraZ -= 1;
			CameraCenterZ -= 1;
		}

		if (abs(PersonaTorsoX - FallGuysX) + abs(PersonaTorsoY - FallGuysY) + abs(PersonaTorsoZ - FallGuysZ) < 3.0f) {
			gluiRestaLvL1 = GLUI_Master.create_glui("Mision: Resta", 0, 800, 400);
			gluiRestaLvL1->add_statictext("Bienvenid@ a la mision de SUMA. Debes seleccionar el boton");
			gluiRestaLvL1->add_statictext("que contiene la respuesta correcta sino perderás contra");
			gluiRestaLvL1->add_statictext("el villano mas temido, el Muñeco de Goma.");
			gluiRestaLvL1->add_statictext("");
			gluiRestaLvL1->add_separator();
			gluiRestaLvL1->add_statictext("Resta: 8 - 4");
			gluiRestaLvL1->add_button("4", 0, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("7", 1, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("84", 2, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("48", 3, myControl_RestaLvL1);


			gluiRestaLvL1->set_main_gfx_window(main_window);
			
			
			PersonaTorsoZ -= 1;
			PersonaTorsoAngle = 0;
			CameraZ -= 1;
			CameraCenterZ -= 1;
		}

		PersonaTorsoZ += 1;
		PersonaTorsoAngle = 0;
		CameraZ += 1;
		CameraCenterZ += 1;

		break;
	case GLUT_KEY_DOWN:
		if (PersonaPiernaIzqAngle >= 20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;

		}
		if (PersonaPiernaIzqAngle <= -20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		PersonaPiernaIzqAngle = PersonaPiernaIzqAngle + PersonaPiernaIzqLimit;
		PersonaPiernaDerAngle = PersonaPiernaDerAngle + PersonaPiernaDerLimit;

		PersonaTorsoZ -= 1;
		PersonaTorsoAngle = 180;
		CameraZ -= 1;
		CameraCenterZ -= 1;
		break;
	case GLUT_KEY_LEFT:
		if (PersonaPiernaIzqAngle >= 20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		if (PersonaPiernaIzqAngle <= -20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		PersonaPiernaIzqAngle = PersonaPiernaIzqAngle + PersonaPiernaIzqLimit;
		PersonaPiernaDerAngle = PersonaPiernaDerAngle + PersonaPiernaDerLimit;

		if (abs(PersonaTorsoX - AmongUsX) + abs(PersonaTorsoY - AmongUsY) + abs(PersonaTorsoZ - AmongUsZ) < 3.0f) {
			
			gluiSumaLvL1 = GLUI_Master.create_glui("Mision: Suma", 0, 800, 400);
			gluiSumaLvL1->add_statictext("Bienvenid@ a la mision de SUMA. Debes seleccionar el boton");
			gluiSumaLvL1->add_statictext("que contiene la respuesta correcta sino perderás contra");
			gluiSumaLvL1->add_statictext("el villano mas temido, el Astronauta.");
			gluiSumaLvL1->add_statictext("");
			gluiSumaLvL1->add_separator();
			gluiSumaLvL1->add_statictext("Suma: 5 + 5");
			gluiSumaLvL1->add_button("10", 0, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("5", 1, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("2", 2, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("8", 3, myControl_SumaLvL1);


			gluiSumaLvL1->set_main_gfx_window(main_window);
			
			PersonaTorsoX -= 1;
			PersonaTorsoAngle = 90;
			CameraX -= 1;
			CameraCenterX -= 1;
		}

		if (abs(PersonaTorsoX - FallGuysX) + abs(PersonaTorsoY - FallGuysY) + abs(PersonaTorsoZ - FallGuysZ) < 3.0f) {
			gluiRestaLvL1 = GLUI_Master.create_glui("Mision: Resta", 0, 800, 400);
			gluiRestaLvL1->add_statictext("Bienvenid@ a la mision de SUMA. Debes seleccionar el boton");
			gluiRestaLvL1->add_statictext("que contiene la respuesta correcta sino perderás contra");
			gluiRestaLvL1->add_statictext("el villano mas temido, el Muñeco de Goma.");
			gluiRestaLvL1->add_statictext("");
			gluiRestaLvL1->add_separator();
			gluiRestaLvL1->add_statictext("Resta: 8 - 4");
			gluiRestaLvL1->add_button("4", 0, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("7", 1, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("84", 2, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("48", 3, myControl_RestaLvL1);


			gluiRestaLvL1->set_main_gfx_window(main_window);
			
			
			PersonaTorsoX -= 1;
			PersonaTorsoAngle = 90;
			CameraX -= 1;
			CameraCenterX -= 1;
		}

		PersonaTorsoX += 1;
		PersonaTorsoAngle = 90;
		CameraX += 1;
		CameraCenterX += 1;
		break;
	case GLUT_KEY_RIGHT:
		if (PersonaPiernaIzqAngle >= 20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		if (PersonaPiernaIzqAngle <= -20) {
			PersonaPiernaIzqLimit = PersonaPiernaIzqLimit * -1;
			PersonaPiernaDerLimit = PersonaPiernaDerLimit * -1;
		}
		PersonaPiernaIzqAngle = PersonaPiernaIzqAngle + PersonaPiernaIzqLimit;
		PersonaPiernaDerAngle = PersonaPiernaDerAngle + PersonaPiernaDerLimit;

		if (abs(PersonaTorsoX - AmongUsX) + abs(PersonaTorsoY - AmongUsY) + abs(PersonaTorsoZ - AmongUsZ) < 3.0f) {
			gluiSumaLvL1 = GLUI_Master.create_glui("Mision: Suma", 0, 800, 400);
			gluiSumaLvL1->add_statictext("Bienvenid@ a la mision de SUMA. Debes seleccionar el boton");
			gluiSumaLvL1->add_statictext("que contiene la respuesta correcta sino perderás contra");
			gluiSumaLvL1->add_statictext("el villano mas temido, el Astronauta.");
			gluiSumaLvL1->add_statictext("");
			gluiSumaLvL1->add_separator();
			gluiSumaLvL1->add_statictext("Suma: 5 + 5");
			gluiSumaLvL1->add_button("10", 0, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("5", 1, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("2", 2, myControl_SumaLvL1);
			gluiSumaLvL1->add_button("8", 3, myControl_SumaLvL1);


			gluiSumaLvL1->set_main_gfx_window(main_window);
			
			
			PersonaTorsoX += 1;
			PersonaTorsoAngle = -90;
			CameraX += 1;
			CameraCenterX += 1;
		}

		if (abs(PersonaTorsoX - FallGuysX) + abs(PersonaTorsoY - FallGuysY) + abs(PersonaTorsoZ - FallGuysZ) < 3.0f) {
			
			gluiRestaLvL1 = GLUI_Master.create_glui("Mision: Resta", 0, 800, 400);
			gluiRestaLvL1->add_statictext("Bienvenid@ a la mision de SUMA. Debes seleccionar el boton");
			gluiRestaLvL1->add_statictext("que contiene la respuesta correcta sino perderás contra");
			gluiRestaLvL1->add_statictext("el villano mas temido, el Muñeco de Goma.");
			gluiRestaLvL1->add_statictext("");
			gluiRestaLvL1->add_separator();
			gluiRestaLvL1->add_statictext("Resta: 8 - 4");
			gluiRestaLvL1->add_button("4", 0, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("7", 1, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("84", 2, myControl_RestaLvL1);
			gluiRestaLvL1->add_button("48", 3, myControl_RestaLvL1);


			gluiRestaLvL1->set_main_gfx_window(main_window);
			
			PersonaTorsoX += 1;
			PersonaTorsoAngle = -90;
			CameraX += 1;
			CameraCenterX += 1;
		}

		PersonaTorsoX -= 1;
		PersonaTorsoAngle = -90;
		CameraX -= 1;
		CameraCenterX -= 1;
		break;
	}
}

void myControl_CB(int control) {
	if (control == 0) {
		genID = 0;
	}
	if (control == 1) {
		genID = 1;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);

	main_window = glutCreateWindow("EducationalSupportTool - Projecto Final");

	glewInit();
	init();

	glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);
	glui->add_statictext("¡Bienvenido Alumn@!");
	glui->add_statictext("Esto es una herramienta de soporte");
	glui->add_statictext("para alumnos de inicial.");
	glui->add_statictext(" ");
	glui->add_separator();
	glui->add_statictext("Elige tu genero:");
	GLUI_Panel* skins = new GLUI_Panel(glui, "", 1);
	obj_panel = new GLUI_Panel(skins, "Elige tu disfraz:");
	glui->add_button_to_panel(skins, "-> Alumno <-", 0, myControl_CB);
	glui->add_button_to_panel(skins, "-> Alumna <-", 1, myControl_CB);
	glui->add_separator();


	glui->set_main_gfx_window(main_window);
	GLUI_Master.set_glutIdleFunc(myGlutUpdate);

	glutReshapeFunc(myGlutReshape);
	glutDisplayFunc(myGlutDisplay);
	glutSpecialFunc(myGlutKeyboard);
	glutIdleFunc(myGlutUpdate);

	//Carga de modelo OBJ
	skybox = glmReadOBJ((char*)"models/skybox/skybox.obj");
	terrain = glmReadOBJ((char*)"models/terrain/terrain.obj");
	tree = glmReadOBJ((char*)"models/tree/tree.obj");
	personCuerpo = glmReadOBJ((char*)"models/boys/Torso.obj");
	personCabeza = glmReadOBJ((char*)"models/boys/Cabeza.obj");
	personBrazoIzq = glmReadOBJ((char*)"models/boys/brazoniniz.obj");
	personAnteBrazoIzq = glmReadOBJ((char*)"models/boys/antebrazoniniz.obj");
	personBrazoManoIzq = glmReadOBJ((char*)"models/boys/manoniniz.obj");
	personBrazoDer = glmReadOBJ((char*)"models/boys/brazode.obj");
	personAnteBrazoDer = glmReadOBJ((char*)"models/boys/antebrazode.obj");
	personBrazoManoDer = glmReadOBJ((char*)"models/boys/manode.obj");
	personMuslos = glmReadOBJ((char*)"models/boys/Part1.obj");
	personPiernaIzq = glmReadOBJ((char*)"models/boys/piernaiz.obj");
	personPieIzq = glmReadOBJ((char*)"models/boys/pieiz.obj");
	personPiernaDer = glmReadOBJ((char*)"models/boys/Piernader.obj");
	personPieDer = glmReadOBJ((char*)"models/boys/pieder.obj");
	amongTorso = glmReadOBJ((char*)"models/among us/Torso.obj");
	amongCuerpo = glmReadOBJ((char*)"models/among us/ParteSup.obj");
	amongPiernaDe = glmReadOBJ((char*)"models/among us/PiernaDe.obj");
	amongPiernaIz = glmReadOBJ((char*)"models/among us/PiernaIz.obj");
	fallguys = glmReadOBJ((char*)"models/fallguys/FallGuysD.obj");
	//////////////////////



	glutMainLoop();
	return 0;
}
