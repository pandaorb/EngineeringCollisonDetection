#include "stdafx.h"
#include <GL/glut.h>
#include "student.h"
#include <stdlib.h>
#include "animation.h"
#include <math.h>
#include "buildings.h"
#include "people.h"
#include "Polygon.h"

static GLfloat theta[] = { 0.0, 0.0, 0.0 };
static GLint axis = 1;
static GLfloat studentLocation[] = { -5.5, 0.0, 0.0 };
static GLfloat studentDirection = 0.0;
static GLfloat viewer[] = { 0.0, 15.0, 5.0 };
static GLfloat light_position[] = { -5.5, 0.0, 0.0, 1.0 };
enum setting { SPOT, EXTRA, BOTH, NONE };
static setting lightSetting = SPOT;

//use masterPoly.existingPolygons to get existing polygons
Polygon masterPoly = Polygon();


/*
* Acts as main display function.
* @args void
* @return void
*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	drawPeople();
	
	glColor3f((145.0 / 255.0), (10.0 / 255.0), (10.0 / 255.0));
	drawCampus();

	walkForward();
	drawStudent();
	glPopMatrix();
	
	glutPostRedisplay();

	glFlush();
	glutSwapBuffers();
}

/*
* Dr. Chang's spinCube function which rotates
* the model.
* @args void
* @return void
*/
void spinModel(void)
{
	/* Idle callback, spin 2 degrees about selected axis */

	theta[axis] += 0.5;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	glutPostRedisplay();
}

/*
* Mouse callback function,
* this listens for a mouse click and then spins the
* model clockwise about the y-axis.
* @args		btn - mouse button clicked
*			state - state of button
x - location of mouse on x-axis
y - location of mouse on y-axis
* @return void
*/
void mouse(int btn, int state, int x, int y)
{

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		axis = 1;
		glutIdleFunc(spinModel);
	}
	if (state == GLUT_UP)
	{
		glutIdleFunc(NULL);
	}
}

/*
 * Callback handles user input through keyboard for moving.
 * @param	key		non-askii key being pressed
 * @param	width	width of window during press
 * @param	height	height of window during press
 * @return	void	
 */
void keyboard(int key, int width, int height)
{
	GLfloat motion = 0.5;
	GLfloat rotation = 5.0;
	GLfloat newStudentDirection = studentDirection;
	switch (key)
	{
	case GLUT_KEY_UP:
		setMovement(motion);
		break;
	case GLUT_KEY_RIGHT:
		newStudentDirection -= 5.0;
		studentDirection = (newStudentDirection <= 0.0) ? newStudentDirection + 360.0 : newStudentDirection;
		break;
	case GLUT_KEY_LEFT:
		newStudentDirection += 5.0;
		studentDirection = (newStudentDirection >= 360.0) ? newStudentDirection - 360.0 : newStudentDirection;
		break;
	default:
		break;
	}
}

/*
 * Sets new location based on direction that student is 
 * currently facing.
 * @param	motion		the increment for moving
 * @return	void
 */
void setMovement(GLfloat motion)
{
	if (studentDirection >= 315 || studentDirection < 45)
	{
		//facing mostly downwards, move down
		studentLocation[2] += motion;
		light_position[2] = studentLocation[2];
	}
	else if (studentDirection >= 45 && studentDirection < 135)
	{
		//facing mostly right, move right
		studentLocation[0] += motion;
		light_position[0] = studentLocation[0];
	}
	else if (studentDirection >= 135 && studentDirection < 215)
	{
		//facing mostly left, move left
		studentLocation[2] -= motion;
		light_position[2] = studentLocation[2];
	}
	else if (studentDirection >= 225 && studentDirection < 315)
	{
		studentLocation[0] -= motion;
		light_position[0] = studentLocation[0];
	}
}

/*
* Causes student to walk in direction he is facing.
* @args		void
* @return	void
*/
void walkForward(void)
{
	glPushMatrix();
	if (!isIntersectingObjects()) // only walk if not intersecting
	{
		glTranslatef(studentLocation[0], studentLocation[1], studentLocation[2]);
		glRotatef(studentDirection, 0.0, 1.0, 0.0);
	}
}

/*
 * Checks to see if student is intersecting with anything
 * while walking
 * @args	void
 * @returns	true	student is intersecting
 * @returns false	student is not intersecting
 */
bool isIntersectingObjects(void)
{
	for (int i = 0; i < masterPoly.existingPolygons.size(); i++)
	{
		if (masterPoly.existingPolygons[i].isIntersecting(studentLocation))
			return true;
	}
	return false;
}

/*
 * Handles callback function for ASCII key press.
 * Changes viewer position based on input.
 * @param	key		ASCII code for key
 * @param	x		x-coordinate of mouse
 * @param	y		y-coordinate of mouse
 */
void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
		
		case 'x':
			viewer[0] -= 1.0;
			break;
		case 'X':
			viewer[0] += 1.0;
			break;
		case 'y':
			viewer[1] -= 1.0;
			break;
		case 'Y':
			viewer[1] += 1.0;
			break;
		case 'z':
			viewer[2] -= 1.0;
			break;
		case 'Z':
			viewer[2] += 1.0;
			break;
		case 'L':
			setLights();
			break;
		case '+':
			// Should increase brightness
			// Nothing appears to make any visible difference
			break;
		case '-':
			// Should decrease brightness
			// Nothing appears to make any visible difference
			break;
		case 'T':
			viewer[0] = 15.0;
			viewer[1] = 5.0;
			viewer[2] = 5.0;
			glutIdleFunc(beginTour);
			break;
		case 't':
			glutIdleFunc(NULL);
			viewer[0] = 0.0;
			viewer[1] = 15.0;
			viewer[2] = 5.0;
			break;
		default:
			break;
	}
}

float moveIncrement = 0.2;
void beginTour()
{
	// If you hit max value, go other direction
	if (viewer[0] <= -18.0)
	{
		moveIncrement = 0.1;
	}
	else if (viewer[0] >= 15.0)
	{
		moveIncrement = -0.1;
	}
	viewer[0] += moveIncrement;
	glutPostRedisplay();
}


void setLights(void)
{
	switch (lightSetting)
	{
		case SPOT:
			lightSetting = EXTRA;
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			break;
		case EXTRA:
			lightSetting = BOTH;
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			break;
		case BOTH:
			lightSetting = NONE;
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			break;
		case NONE:
			lightSetting = SPOT;
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			break;
		default:
			break;
	}
}

/*
* myReshape example from book ensures that
* the model is scaled to the window.
* @args		w - width of the window
*			h - height of window
* @return void
*/
void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, 2.0, 20.0);
	else
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}