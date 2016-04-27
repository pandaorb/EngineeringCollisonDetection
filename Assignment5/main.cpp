/*
* This is assignment 5 for COMP 5400. It is a 3D engineering campus populated 
* with 3D students and viewed with perspective projection. The student with 
* the backpack may be controlled with keyboard input:
*		UP		moves student forward
*		RIGHT	rotates student clockwise
*		LEFT	rotates student counter-clockwise
* 
* Clicking the right mouse button will spin the world about the y-axis.
*
* Keystrokes will move the camera as follows:
*		X		moves camera in positive x direction
*		x		moves camera in negative x direction
*		Y		moves camera in positive y direction
*		y		moves camera in negative y direction
*		Z		moves camera in positive Z direction
*		z		moves camera in negative z direction
*																				   ()()
* Collision Avoidance not really working. Although I'm sure my logic is flawless.  (o_o)
* (Mostly located in Polygon.cpp, but some intersection checking occurs in		 //(   )\\
*  animation.cpp as well.) Maintains a list of existing polygons and calculates	    //\\
*  their areas of intersection then compares these values to where the student
*  is standing.
*
* Automatic tour path will move camera to east campus and pan west. 
* After reaching west campus it will begin to pan east again.
*		T		activates tour
*		t		stops tour
*
* Camera is the source of a spotlight which points towards the original position
* of the main student.
*/

#include "stdafx.h"
#include <GL/glut.h>
#include "initialize.h"
#include "student.h"
#include "buildings.h"
#include "animation.h"

int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv);
	viewInit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutSpecialFunc(keyboard);
	lightInit();
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	programInit();
	glutMainLoop();
	return 0;
}