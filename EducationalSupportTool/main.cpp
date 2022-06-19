#include "Libs.h"

static float ypoz = 0, zpoz = 0;

GLMmodel* skybox = NULL;
GLMmodel * terrain = NULL;

GLuint	texture;
Texture	treeTextureAr[5];

bool LoadTreeTextures()
{
	int i;
	if (LoadTGA(&treeTextureAr[0], (char*)"models/skybox/cielotextura.tga") &&
		LoadTGA(&treeTextureAr[1], (char*)"models/terrain/terrain.tga"))	{
		for (i = 0; i < 5; i++) {
			glGenTextures(1, &treeTextureAr[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeTextureAr[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeTextureAr[i].bpp / 8, treeTextureAr[i].width, treeTextureAr[i].height, 0, treeTextureAr[i].type, GL_UNSIGNED_BYTE, treeTextureAr[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeTextureAr[i].imageData)
			{
				free(treeTextureAr[i].imageData);
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
	LoadTreeTextures();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void graficar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glmDraw(skybox, GLM_SMOOTH | GLM_TEXTURE);

	glRotatef(ypoz, 0, 1, 0);
	glTranslatef(0, -1, 0);
	glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
	glmDraw(terrain, GLM_SMOOTH | GLM_TEXTURE);

	glutSwapBuffers();
}

void redimensionar(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("EducationalSupportTool - Projecto Final");
	glewInit();
	init();


	skybox = glmReadOBJ((char*)"models/skybox/cielo01.obj");
	terrain = glmReadOBJ((char*)"models/terrain/terrain.obj");

	glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
	glutMainLoop();
	return 0;
}
