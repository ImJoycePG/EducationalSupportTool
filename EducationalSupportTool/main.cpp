#include <iomanip>
#include "Libs.h"

#include "ctexture.h"
#include "timer.h"
#include "md2.h"

static float ypoz = 0;

int main_window;

GLMmodel* skybox = NULL;
GLMmodel* terrain = NULL;

CMD2Model ogro;
bool bAnimated = true;

Texture	treeScenaryTexture[2];


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

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);


	CTimer::GetInstance()->Initialize();
	CTextureManager::GetInstance()->Initialize();

	loadScenaryTextures();

	ogro.LoadModel("C:/Users/junio/source/repos/EducationalSupportTool/EducationalSupportTool/models/ogro/Ogros.md2");
	ogro.LoadSkin("C:/Users/junio/source/repos/EducationalSupportTool/EducationalSupportTool/models/ogro/igdosh.pcx");
	ogro.SetAnim(RUN);
	ogro.ScaleModel(0.25);
}

void myGlutScenary() {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[0].texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glmDraw(skybox, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -4, 0);
	glScaled(50, 1, 50);
	glBindTexture(GL_TEXTURE_2D, treeScenaryTexture[1].texID);
	glmDraw(terrain, GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();
}

void myGlutDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CTimer::GetInstance()->Update();
	float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;
	std::cout << "\r   fps = " << std::setprecision(4) << CTimer::GetInstance()->GetFps();

	gluLookAt(20, 2.0, 20.0, 0.0, 2.0, 0.0, 0.0f, 1.0f, 0.0f);

	myGlutScenary();

	ogro.DrawModel(bAnimated ? timesec : 0.0);

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
	//angApple += 5;
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

void myGlutKeyboard(unsigned char key, int x, int y) {
	/*
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
	*/
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
	//glutKeyboardFunc(myGlutKeyboard);
	//glutIdleFunc(myGlutUpdate);

	skybox = glmReadOBJ((char*)"models/skybox/skybox.obj");
	terrain = glmReadOBJ((char*)"models/terrain/terrain.obj");


	glutMainLoop();
	return 0;
}
