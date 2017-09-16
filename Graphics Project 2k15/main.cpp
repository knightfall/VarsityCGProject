


#include <iostream>
#include <stdlib.h>


#include <gl/glut.h>
#include <gl\GLU.h>


#include "imageloader.h"

using namespace std;
int light = 1;
GLuint _textureId; //The id of the texture
GLuint _newid;
GLuint _trafficbrick;
GLUquadric *quad;
GLuint _redlight;
GLuint _greenlight;
GLuint _sidewindow;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	case 'g':
	case 'G':
		light = 1;
		break;

	case 'r':
	case 'R':
		light = 0;
		break;
	}	
}


//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);
	Image* image = loadBMP("bricks.bmp");
	_textureId = loadTexture(image);
	delete image;
	Image* image1 = loadBMP("building.bmp");
	_newid = loadTexture(image1);
	delete image1;
	Image* image2 = loadBMP("trafficbrick.bmp");
	_trafficbrick = loadTexture(image2);
	delete image2;
	Image* image3 = loadBMP("greenlight.bmp");
	_greenlight = loadTexture(image3);
	delete image3;
	Image* image4 = loadBMP("redlight.bmp");
	_redlight = loadTexture(image4);
	delete image4;
	Image* image5 = loadBMP("window.bmp");
	_sidewindow = loadTexture(image5);
	delete image5;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}



float i = 00.0f;

static void	drawBox(GLfloat size, GLenum type, GLuint params)
{
	static GLfloat n[6][3] =
	{
		{ -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, -1.0, 0.0 },
		{ 0.0, 0.0, 1.0 },
		{ 0.0, 0.0, -1.0 }
	};
	static GLint faces[6][4] =
	{
		{ 0, 1, 2, 3 },
		{ 3, 2, 6, 7 },
		{ 7, 6, 5, 4 },
		{ 4, 5, 1, 0 },
		{ 5, 6, 2, 1 },
		{ 7, 4, 0, 3 }
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, params);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0.0f, 01.0f);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(01.0f, 0.0f);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void glustSolidCube(GLdouble size, GLuint param)
{
	drawBox(size, GL_QUADS, param);
}





void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 00.0f, -10.0f);

	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 1.7f, 1.7f, 1.7f, 1.8f };
	GLfloat directedLightPos[] = { -04.0f, 15.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Road

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-8.0f, -2.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(8.0f, -2.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(8.0f, -2.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-8.0f, -2.5f, -2.5f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, _newid);
	
	//Horizontalbox

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-10.0f, -2.5f, -2.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-10.0f, 2.5f, -2.5f);
	glTexCoord2f(1, 1);
	glVertex3f(10.0f, 2.5f, -2.5f);
	glTexCoord2f(1, 0);
	glVertex3f(10.0f, -2.5f, -2.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	
	glEnd();

		 //car
	glColor3f(00.0, 00.40, 01.0);
	glBegin(GL_POLYGON);
	
	glVertex3f(-10.0f+i,-2.4f,2.0f);
	glVertex3f(-10.0f+i,-1.5f,2.0f);
	glVertex3f(-9.4f + i, -1.4f, 2.0f);
	glVertex3f(-8.5f + i, -.80f, 2.0f);
	glVertex3f(-6.0f+i, -0.80f, 2.0f);
	glVertex3f(-5.0f+i, -1.4f, 2.0f);
	glVertex3f(-4.0f + i, -1.6f, 2.0f);
	glVertex3f(-4.0f + i, -2.4f, 2.0f);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-8.5 + i, -1.5,2.1);
	glTexCoord2f(0, 01);
	glVertex3f(-7.6 + i, -1.5, 2.1);
	glTexCoord2f(1, 1);
	glVertex3f(-7.6 + i, -.85, 2.1);
	glTexCoord2f(1, 0);
	glVertex3f(-8.5 + i, -.85, 2.1);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-7.3 + i, -1.5, 2.1);
	glTexCoord2f(0, 01);
	glVertex3f(-6.3 + i, -1.5, 2.1);
	glTexCoord2f(1, 1);
	glVertex3f(-6.3 + i, -.85, 2.1);
	glTexCoord2f(1, 0);
	glVertex3f(-7.3 + i, -.85, 2.1);
	glEnd();

	//traffic
	glTranslatef(4.0f, -2.3f, 2.2f);
	glColor3f(01.0, 01.0, 01.0);
	
	glustSolidCube(.4,_trafficbrick);
	glTranslatef(0.0f, .2f, 0.0f);

	
	glColor3f(0.0, 00.0, 01.0);

	
	glPushMatrix();
	glRotatef(180,0,1,1);
	
	gluCylinder(quad, 0.1f, 0.1f, 1.5, 100, 100);
	glPopMatrix();
	
	glTranslatef(.4f, 2.45, -.8);

	glEnable(GL_TEXTURE_2D);
	if (light == 1)
	{
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _greenlight);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _redlight);
	}
	//Bottom

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);

	//Front

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-.5f, -1.0f, .2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(.5f, -1.0f, .2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(.5f, 1.0f, .2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-.5f, 1.0f, .2f);

	//Right

	glVertex3f(.5f, -1.0f, -.2f);
	
	glVertex3f(.5f, 1.0f, -.2f);
	
	glVertex3f(.5f, 1.0f, .2f);
	
	glVertex3f(.5f, -1.0f, .2f);

	//Back

	glVertex3f(-.5f, -1.0f, -.2f);
	
	glVertex3f(-.5f, 1.0f, -.2f);
	
	glVertex3f(.5f, 1.0f, -.2f);
	
	glVertex3f(.5f, -1.0f, -.2f);

	//Left
	
	glVertex3f(-.5f, -1.0f, -.2f);
	
	glVertex3f(-.5f, -1.0f, .2f);
	
	glVertex3f(-.5f, 1.0f, .2f);
	
	glVertex3f(-.5f, 1.0f, -.2f);

	glEnd();
	

	glutSwapBuffers();
}	


#define SPEED 0.05 

void idle()
{		  
	
	if (light == 0 && i>7.8f &&i<8.9f) 
	{
		i = i;		
	}
	

	else

	{

		i += SPEED / 20;
	
		
	}
	if (i>18.0f)
		i = 0.0;
	

	glutPostRedisplay();

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1360, 768);

	glutCreateWindow("Computer Graphics Project");
	initRendering();

	glutDisplayFunc(drawScene);
	glutIdleFunc(idle);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}









