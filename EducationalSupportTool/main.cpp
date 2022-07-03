#include <iomanip>
#include "Libs.h"

#include "ctexture.h"
#include "timer.h"
#include "md2.h"

static float ypoz = 0;

int main_window;


//Cords Personaje Principal

float PersonaTorsoX = 0;
float PersonaTorsoY = -3;
float PersonaTorsoZ = 0;

float PersonaTorsoAngle = 0;

float PersonaCabezaX = 0;
float PersonaCabezaY = 0;
float PersonaCabezaZ = 0;

float PersonaBrazoX = 0;
float PersonaBrazoY = 0;
float PersonaBrazoZ = 0;

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
	GLMmodel* personBrazo = NULL;
	GLMmodel* personMuslos = NULL;
	GLMmodel* personPiernaIzq = NULL;
	GLMmodel* personPieIzq = NULL;
	GLMmodel* personPiernaDer = NULL;
	GLMmodel* personPieDer = NULL;
GLMmodel* tree = NULL;
	

//Modelo MD2 - Animation
/*
CMD2Model ogro;
bool bAnimated = true;
*/
//Textura GLM - OBJ
Texture	treeScenaryTexture[2];
Texture	treePersontexture[1];
Texture treeTreeSceneTexture[1];

bool loadScenaryTextures(){
	int i;
	if (LoadTGA(&treeScenaryTexture[0], (char*)"models/skybox/skyTextures.tga") &&
		LoadTGA(&treeScenaryTexture[1], (char*)"models/terrain/terrain.tga"))	{
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
	if (LoadTGA(&treePersontexture[0], (char*)"models/boys/personaje.tga")) {
		for (i = 0; i < 1; i++) {
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
			if (treeTreeSceneTexture[i].imageData){
				free(treeTreeSceneTexture[i].imageData);
			}
		}
		return true;
	}else{
		return false;
	}
}

void init(void){
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
	//////////////////////

	//Carga de model-Skin-Animation-Scale - MD2
	/*
	ogro.LoadModel("C:/Users/junio/source/repos/EducationalSupportTool/EducationalSupportTool/models/ogro/Ogros.md2");
	ogro.LoadSkin("C:/Users/junio/source/repos/EducationalSupportTool/EducationalSupportTool/models/ogro/igdosh.pcx");
	ogro.SetAnim(RUN);
	ogro.ScaleModel(0.25);
	*/
	//////////////////////
}

void myGlutScenary() {
	glPushMatrix();
	glTranslatef(SkyBoxX, SkyBoxY, SkyBoxZ);
	glScalef(2, 2, 2);
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
	glScaled(380, 1, 380);
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[1].texID);
	glmDraw(terrain, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutPerson() {
	//Torso
	glPushMatrix();
	glTranslatef(PersonaTorsoX, PersonaTorsoY, PersonaTorsoZ);
	//glScalef(2, 2, 2);
	glRotated(PersonaTorsoAngle, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
	glmDraw(personCuerpo, GLM_SMOOTH | GLM_TEXTURE);

		//Cabeza
		glPushMatrix();
		glTranslatef(PersonaCabezaX, PersonaCabezaY, PersonaCabezaZ);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
		glmDraw(personCabeza, GLM_SMOOTH | GLM_TEXTURE);
		glPopMatrix();

		//Brazo
		glPushMatrix();
		glTranslatef(PersonaBrazoX, PersonaBrazoY, PersonaBrazoZ);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
		glmDraw(personBrazo, GLM_SMOOTH | GLM_TEXTURE);
		glPopMatrix();
	
		//Muslos
		glPushMatrix();
		glTranslatef(PersonaMuslosX, PersonaMuslosY, PersonaMuslosZ);
		glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
		glmDraw(personMuslos, GLM_SMOOTH | GLM_TEXTURE);
			//Pierna Izquierda
			glPushMatrix();
			glTranslatef(PersonaPiernaIzqX, PersonaPiernaIzqY, PersonaPiernaIzqZ);
			glRotatef(PersonaPiernaIzqAngle, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
			glmDraw(personPiernaIzq, GLM_SMOOTH | GLM_TEXTURE);

				//Pie Izquierda
				glPushMatrix();
				glTranslatef(PersonaPieIzqX, PersonaPieIzqY, PersonaPieIzqZ);
				glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
				glmDraw(personPieIzq, GLM_SMOOTH | GLM_TEXTURE);
				glPopMatrix();
			glPopMatrix();

			//Pierna Derecha
			glPushMatrix();
			glTranslatef(PersonaPiernaDerX, PersonaPiernaDerY, PersonaPiernaDerZ);
			glRotatef(PersonaPiernaDerAngle, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
			glmDraw(personPiernaDer, GLM_SMOOTH | GLM_TEXTURE);

				//Pie Derecha
				glPushMatrix();
				glTranslatef(PersonaPieDerX, PersonaPieDerY, PersonaPieDerZ);
				glBindTexture(GL_TEXTURE_2D, treePersontexture[0].texID);
				glmDraw(personPieDer, GLM_SMOOTH | GLM_TEXTURE);
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();
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
	glTranslatef(36, -3, 38);
	glBindTexture(GL_TEXTURE_2D, treeTreeSceneTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CTimer::GetInstance()->Update();
	float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;

	gluLookAt(CameraX, CameraY, CameraZ, CameraCenterX, CameraCenterY, CameraCenterZ, CameraUpX, CameraUpY, CameraUpZ);

	myGlutScenary();
	myGlutTrees();
	myGlutPerson();

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
	SkyBoxAngel += 0.2;
	
	/*
	if (abs(CentaurPosX - ApplePosX_1) + abs(CentaurPosY - ApplePosY_1) < 0.95) {
		ApplePosY_1 = 100;
	}

	if (abs(CentaurPosX - ApplePosX_2) + abs(CentaurPosY - ApplePosY_2) < 0.95) {
		ApplePosY_2 = 100;
	}
	if (abs(CentaurPosX - ApplePosX_3) + abs(CentaurPosY - ApplePosY_3) < 0.95) {
		ApplePosY_3 = 100;
	}
	if (abs(CentaurPosX - ApplePosX_4) + abs(CentaurPosY - ApplePosY_4) < 0.95) {
		ApplePosY_4 = 100;
	}
	if (abs(CentaurPosX - ApplePosX_5) + abs(CentaurPosY - ApplePosY_5) < 0.95) {
		ApplePosY_5 = 100;
	}
	if (abs(CentaurPosX - ApplePosX_6) + abs(CentaurPosY - ApplePosY_6) < 0.95) {
		ApplePosY_6 = 100;
	}
	*/
	glutPostRedisplay();
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

		PersonaTorsoX -= 1;
		PersonaTorsoAngle = -90;
		CameraX -= 1;
		CameraCenterX -= 1;
		break;
	}	
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);

	main_window = glutCreateWindow("EducationalSupportTool - Projecto Final");

	glewInit();
	init();

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
	personBrazo = glmReadOBJ((char*)"models/boys/Brazo.obj");
	personMuslos = glmReadOBJ((char*)"models/boys/Part1.obj");
	personPiernaIzq = glmReadOBJ((char*)"models/boys/piernaiz.obj");
	personPieIzq = glmReadOBJ((char*)"models/boys/pieiz.obj");
	personPiernaDer = glmReadOBJ((char*)"models/boys/Piernader.obj");
	personPieDer = glmReadOBJ((char*)"models/boys/pieder.obj");
	//person = glmReadOBJ((char*)"models/boys/DavidBoy.obj");
	//////////////////////


	glutMainLoop();
	return 0;
}
