#include "Libs.h"

/*//////////////////////////////////

Faltaria:
 - Interfaces
   - Diferentes personajes para seleccionar
   - Animaciones para el personaje
 - Mecanicas
 - M�s niveles

 Github: https://github.com/ImJoycePG/EducationalSupportTool

//////////////////////////////////*/

static float ypoz = 0;

int main_window;
int angApple = 0;


GLMmodel* skybox = NULL;
GLMmodel * terrain = NULL;

GLMmodel * centaur = NULL;
GLMmodel * apple1 = NULL;

GLuint	texture;
Texture	treeScenaryTexture[2];
Texture	treeCentaurTexture[1];
Texture	treeAppleTexture[1];


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

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	loadScenaryTextures();
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
	glTranslatef(-2, -0.8, 0.4);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, treeCentaurTexture[0].texID);
	glmDraw(centaur, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

}

void myGlutApples() {
	glPushMatrix();
	glTranslatef(appleX, appleY,0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.4, -0.2, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, -0.2, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, -0.2, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, -0.2, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -0.2, 0.4);
	glRotatef(angApple, 0, 1, 0);
	glScalef(0.002, 0.002, 0.002);
	glBindTexture(GL_TEXTURE_2D, treeAppleTexture[0].texID);
	glmDraw(apple1, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

	myGlutScenary();
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

void animationApple(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, animationApple, 0);

	angApple += 1;

	if (angApple > 360)
		angApple = angApple - 360;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);

	main_window = glutCreateWindow("EducationalSupportTool - Projecto Final");

	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);
	glutTimerFunc(0, animationApple, 0);

	glewInit();
	init();

	skybox = glmReadOBJ((char*)"models/skybox/skybox.obj");
	terrain = glmReadOBJ((char*)"models/terrain/terrain.obj");
	centaur = glmReadOBJ((char*)"models/centaur/centaurwarrior.obj");
	apple1 = glmReadOBJ((char*)"models/Apple/Apple.obj");


	glutMainLoop();
	return 0;
}
