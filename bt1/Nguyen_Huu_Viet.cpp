#include <math.h>
//#include <GL\glew.h>
//#include<GL\freeglut.h>
#include <GL/glut.h>

#define pi 3.14159265359
#define K_MAT_RED     0
#define K_MAT_GREEN   1
#define K_MAT_BLUE    2
#define K_MAT_YELLOW  3
#define K_MAT_PINK    4

const int screenwidth = 1000;
const int screenheight = 800;

GLint hinh_sun;
GLint hinh_moon;
GLint hinh_ea;

GLfloat day = 0.0;
GLfloat moon = 0.0;
GLfloat year = 0.0;



void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4])
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void SetMaterialColor(const int& type)
{
	GLfloat ambien[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diff_use[] = {0.0, 0.0, 0.0, 1.0};
	switch(type)
	{
	case K_MAT_RED:
	{
	ambien[0] = 1.0f;
	diff_use[0] = 1.0f;
	}
	break;
	case K_MAT_GREEN:
	{
	ambien[1] = 1.0f;
	diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_BLUE:
	{
	ambien[2] = 1.0f;
	diff_use[2] = 1.0f;
	}
	break;
	case K_MAT_YELLOW:
	{
	ambien[0] = 1.0f;
	ambien[1] = 1.0f;
	diff_use[0] = 1.0f;
	diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_PINK:
	{
	ambien[0] = 1.0f;
	ambien[2] = 1.0f;
	diff_use[0] = 1.0f;
	diff_use[1] = 1.0f;
	}
	break;
	default:
	{
	ambien[0] = 1.0f;
	ambien[1] = 1.0f;
	ambien[2] = 1.0f;
	diff_use[0] = 1.0f;
	diff_use[1] = 1.0f;
	diff_use[2] = 1.0f;
	}
	break;
	}
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambien);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

GLuint Cau(const float& radius)
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	glutSolidSphere(radius, 64, 64);
	glEndList();
	
	return dp_list;
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5.0,5.0,15.0,0.0,0.0,0.0,0.0,1.0,0.0);
	
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glCallList(hinh_sun);
	glPopMatrix();	
	glEnable(GL_LIGHTING);
	
	GLfloat light_position[] = { 0.0, 0.0, 0.0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
		
	glPushMatrix();
	glRotatef(year, 0.0, 1.0, 0.0);
	SetMaterialColor(K_MAT_BLUE);
	glTranslatef(8.0,0.0,0.0);
	glRotatef(day, 0.0, 1.0, 0.0);
	glCallList(hinh_ea);


	glPushMatrix();
	glRotatef(moon, 0.0, 1.0, 0.0);
	glTranslatef(2.0,0.0,0.0);
	GLfloat ambien[] ={0.7, 0.7, 0.7, 1.0f};
	GLfloat diff_use[] = {1.0, 1.0, 1.0f};
	SetMaterialColor(ambien, diff_use);	
	glCallList(hinh_moon);
	glPopMatrix();
	glPushMatrix();
	
	Sleep(83);
	moon += 13.0;
	if(moon >= 360 )
	{
		moon = 0;
	}
	
	day += 360.0;
	if(day >= 360 )
	{
		day = 0;
	}
	
	year += 1.0;
	if(year>= 360 )
	{
		year = 0;
	}
	
	glFlush();
	
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, w / (float)h, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);


} 

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	
	
	

	
	/*
	GLfloat light[] = {1.0, 1.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light);
	GLfloat ambient [] = {1.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diff_use [] = {1.0, 1.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	
	GLfloat shininess = 50.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
	*/
	hinh_sun = Cau(2.0);
	hinh_ea = Cau(1.0);
	hinh_moon = Cau(0.2);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenwidth, screenheight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Opengl");
	
	init();
	glClearColor(0, 0, 0, 0);
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	
	glutMainLoop();
	return 0;
}
