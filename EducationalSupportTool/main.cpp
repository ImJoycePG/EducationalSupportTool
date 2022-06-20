#include "Libs.h"

/*//////////////////////////////////

Faltaria:
 - Interfaces
   - Diferentes personajes para seleccionar
   - Animaciones para el personaje
 - Mecanicas
   - Mouse
   - Niveles
   - Misiones
   - Efectos de sonido

 Github: https://github.com/ImJoycePG/EducationalSupportTool

//////////////////////////////////*/

static float ypoz = 0;

int main_window;
int angApple = 0;


GLMmodel* skybox = NULL;
GLMmodel * terrain = NULL;
GLMmodel* tree = NULL;

GLMmodel * centaur = NULL;
GLMmodel * apple1 = NULL;

GLuint	texture;
Texture	treeScenaryTexture[2];
Texture	treeCentaurTexture[1];
Texture	treeAppleTexture[1];
Texture	treeTreeTexture[1];

GLfloat CentaurPosX = -2;
GLfloat CentaurPosY = -0.8;
GLfloat CentaurAng = 90;

GLfloat ApplePosX_1 = -1.0f;
GLfloat ApplePosY_1 = -0.2f;

GLfloat ApplePosX_2 = -0.4f;
GLfloat ApplePosY_2 = -0.2f;

GLfloat ApplePosX_3 = 0.2;
GLfloat ApplePosY_3 = -0.2f;

GLfloat ApplePosX_4 = 0.8;
GLfloat ApplePosY_4 = -0.2f;

GLfloat ApplePosX_5 = 1.4f;
GLfloat ApplePosY_5 = -0.2f;

GLfloat ApplePosX_6 = 2.0f;
GLfloat ApplePosY_6 = -0.2f;


bool loadScenaryTextures()
{
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

bool loadCentaurTexture()
{
	int i;
	if (LoadTGA(&treeCentaurTexture[0], (char*)"models/Centaur/CentaurWarriorSkinBrown.tga")) {
		for (i = 0; i < 2; i++) {
			glGenTextures(1, &treeCentaurTexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeCentaurTexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeCentaurTexture[i].bpp / 8, treeCentaurTexture[i].width,
				treeCentaurTexture[i].height, 0, treeCentaurTexture[i].type, GL_UNSIGNED_BYTE,
				treeCentaurTexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeCentaurTexture[i].imageData)
			{
				free(treeCentaurTexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool loadAppleTexture()
{
	int i;
	if (LoadTGA(&treeAppleTexture[0], (char*)"models/Apple/Apple.tga")) {
		for (i = 0; i < 1; i++) {
			glGenTextures(1, &treeAppleTexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeAppleTexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeAppleTexture[i].bpp / 8, treeAppleTexture[i].width,
				treeAppleTexture[i].height, 0, treeAppleTexture[i].type, GL_UNSIGNED_BYTE,
				treeAppleTexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeAppleTexture[i].imageData)
			{
				free(treeAppleTexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool loadTreeTexture(){
	int i;
	if (LoadTGA(&treeTreeTexture[0], (char*)"models/tree/orcmale_Body.tga")) {
		for (i = 0; i < 1; i++) {
			glGenTextures(1, &treeTreeTexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeTreeTexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeTreeTexture[i].bpp / 8, treeTreeTexture[i].width,
				treeTreeTexture[i].height, 0, treeTreeTexture[i].type, GL_UNSIGNED_BYTE,
				treeTreeTexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeTreeTexture[i].imageData)
			{
				free(treeTreeTexture[i].imageData);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	loadScenaryTextures();
	loadTreeTexture();
	loadCentaurTexture();
	loadAppleTexture();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void myGlutScenary() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[0].texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glmDraw(skybox, GLM_SMOOTH | GLM_TEXTURE);

	glTranslatef(0, -1, 0);
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[1].texID);
	glmDraw(terrain, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutCentaur() {
	glPushMatrix();
	glTranslatef(CentaurPosX, CentaurPosY, 0.4);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(CentaurAng, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treeCentaurTexture[0].texID);
	glmDraw(centaur, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

}

void myGlutApples() {
	glPushMatrix();
	glTranslatef(ApplePosX_1, ApplePosY_1, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(ApplePosX_2, ApplePosY_2, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ApplePosX_3, ApplePosY_3, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ApplePosX_4, ApplePosY_4, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ApplePosX_5, ApplePosY_5, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ApplePosX_6, ApplePosX_6, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutTree() {
	glPushMatrix();
	glTranslatef(-8, -1.8, -10);
	glScalef(0.3, 0.3, 0.3);
	glBindTexture(GL_TEXTURE_2D, treeTreeTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, -1.8, -10);
	glScalef(0.3, 0.3, 0.3);
	glBindTexture(GL_TEXTURE_2D, treeTreeTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0, -1.8, -10);
	glScalef(0.3, 0.3, 0.3);
	glBindTexture(GL_TEXTURE_2D, treeTreeTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -1.8, -10);
	glScalef(0.3, 0.3, 0.3);
	glBindTexture(GL_TEXTURE_2D, treeTreeTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, -2, -10);
	glScalef(0.3, 0.3, 0.3);
	glBindTexture(GL_TEXTURE_2D, treeTreeTexture[0].texID);
	glmDraw(tree, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

	myGlutScenary();
	myGlutTree();
	myGlutCentaur();
	
	myGlutApples();

	glutSwapBuffers();
}

void myGlutReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
}

void myGlutUpdate() {
	angApple += 5;

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
	
	glutPostRedisplay();
}

void myGlutKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd': 
		CentaurPosX += 0.018;
		CentaurAng = 90;
		break;
	case 'a':
		CentaurPosX -= 0.018;
		CentaurAng = -90;
		break;


	case 'r':
		CentaurPosX = -2;
		CentaurAng = 90;
		ApplePosX_1 = -1.0f;
		ApplePosY_1 = -0.2f;

		ApplePosX_2 = -0.4f;
		ApplePosY_2 = -0.2f;

		ApplePosX_3 = 0.2;
		ApplePosY_3 = -0.2f;

		ApplePosX_4 = 0.8;
		ApplePosY_4 = -0.2f;

		ApplePosX_5 = 1.4f;
		ApplePosY_5 = -0.2f;

		ApplePosX_6 = 2.0f;
		ApplePosY_6 = -0.2f;
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);

	main_window = glutCreateWindow("EducationalSupportTool - Projecto Final - Progress: 70%");

	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);
	glutKeyboardFunc(myGlutKeyboard);
	glutIdleFunc(myGlutUpdate);

	glewInit();
	init();

	skybox = glmReadOBJ((char*)"models/skybox/skybox.obj");
	terrain = glmReadOBJ((char*)"models/terrain/terrain.obj");
	tree = glmReadOBJ((char*)"models/tree/tree.obj");
	centaur = glmReadOBJ((char*)"models/centaur/centaurwarrior.obj");
	apple1 = glmReadOBJ((char*)"models/Apple/Apple.obj");


	glutMainLoop();
	return 0;
}
