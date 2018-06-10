#include <stdio.h>    
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <freeglut.h>
#include <glut.h>  
#include "visuals.h"   

bool one = false;
static float tx = 0.0;
static float day = 0.0;
static float moon = 0.0;
static float year = 0.0;
static float worldX = 15.0;
static float worldY = 0.0;
static float scaleFactor = 0.6;
static bool animate = false;
static float first = 1;
static float second = 1;
point stars[500];



int globalW, globalH;

using namespace std;



void Render()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
														 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(0, 0, -100); //
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	GLUquadricObj *quadric; //
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);

	glScalef(scaleFactor, scaleFactor, scaleFactor);

	glRotatef(worldX, 1, 0, 0);
	glRotatef(worldY, 0, 1, 0);//

	glDisable(GL_LIGHTING);

	glPushMatrix(); // mat troi
	glColor3f(0.8, 0.498039, 0.196078);
	gluSphere(quadric, 15, 36, 18);
	glColor3f(1, 1, 0);
	glEnable(GL_BLEND);
	glBlendFunc(first, second);
	gluSphere(quadric, 20, 36, 18);
	glDisable(GL_BLEND);
	glPopMatrix(); //

	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0,0.0,0.0,1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_amb);

	glPushMatrix(); // trai dat
	glRotatef(year, 0, 1.0, 0);
	
	glTranslatef(80.0, 0.0, 0);
	glRotatef(day, 0, 1.0, 0.0);
	glColor3f(0, 0, 1);
	gluSphere(quadric, 10, 36, 18);
	

	glPushMatrix();// mat trang
	glRotatef(moon, 0, 1.0, 0);
	glTranslatef(20.0, 0.0, 0.0);
	
	glColor3f(1, 1, 1);
	gluSphere(quadric, 3, 36, 18);
	glPopMatrix();

	DrawStars();


	glutSwapBuffers();             
}

//-----------------------------------------------------------

void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	globalH = h;
	globalW = w;

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 1000.0);
}

void Idle()  // chu ky quay cua hanh tinh
{
	if (animate)
		
	{
		
		moon += 13.0;
		if (moon >= 360)
		{
			moon = 0;
		}

		day += 360.0;
		if (day >= 360)
		{
			day = 0;
		}

		year += 1.0;
		if (year >= 360)
		{
			year = 0;
		}
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': exit(0);
		break;
	case 'w': if (animate) worldX -= 1.0f;
		break;
	case 's': if (animate) worldX += 1.0f;
		break;
	case 'a': if (animate) worldY -= 1.0f;
		break;
	case 'd': if (animate)  worldY += 1.0f;
		break;
	case ' ': animate = !animate;;
		break;
	default: break;
	}
	glutPostRedisplay();

}

void MouseWheel(int button, int dir, int x, int y)
{
	if (animate) {
		if (dir > 0) {
			scaleFactor += 0.01;
			glutPostRedisplay();
		}
		else {
			if (scaleFactor > 0.08) {
				scaleFactor -= 0.01;
				glutPostRedisplay();
			}
		}
	}
}


void Setup()  // TOUCH IT !! 
{

	//get random cordinates for the stars
	for (int i = 0; i < 500; i++)
		RandomCoordinates(&stars[i]);
	srand(time(0));
	//Parameter handling
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RandomCoordinates(point *star)
{

	int lowest = -1000, highest = 1000;
	int range = (highest - lowest) + 1;
	star->x = lowest + int(range*rand() / (RAND_MAX + 1.0));
	star->y = lowest + int(range*rand() / (RAND_MAX + 1.0));
	star->z = lowest + int(range*rand() / (RAND_MAX + 1.0));

}

void DrawStars()
{
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	for (int i = 0; i < 500; i++) {
		glPushMatrix();
		glTranslatef(stars[i].x, stars[i].y, stars[i].z);
		glColor3f(1, 1, 1);
		gluSphere(quadric, 1, 36, 18);
		glPopMatrix();
	}
}