#include "stdafx.h"
#include <GL/glut.h>

int viewInit(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0); //This is top left in windows
	glutCreateWindow("COMP-5400 Assignment 5");
	return 0;
}

int lightInit(void)
{
	/* set up ambient, diffuse, and specular components for light 1 (spotlight) */
	GLfloat light_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position1[] = { -5.5, 0.0, 0.0, 1.0 };
	GLfloat light_direction1[] = { 0.0, 1.0, 0.0 };	
	GLfloat light_ambient1[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	/* define material proerties for front face of all polygons */

	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.0, 0.0, 0.5, 0.5 };
	GLfloat mat_shininess = { 2.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT);

	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	return 0;
}

int programInit(void)
{
	/* set background color to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	/* set buildings to brick red */
	glColor3f((203.0 / 255.0), (65.0 / 255.0), (84.0 / 255.0));

	/* set up camera */
	glMatrixMode(GL_PROJECTION);

	//http://stackoverflow.com/questions/628796/what-does-glloadidentity-do-in-opengl
	glLoadIdentity();

	/* sets perspective projection parameters */
	gluPerspective(90.0, 1.0, 5.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	return 0;
}