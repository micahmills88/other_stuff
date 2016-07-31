// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <cmath>

#include <string>

using namespace std;

#define SLEEP 50 // sleep in miliseconds
#define PI 3.14159
#define F0 0.5
#define TS 0.125

/* Global variables */
char title[] = "Micah Mills - Final Project";
GLUquadric *quad;
GLfloat movement1 = 0.0f;
GLfloat movement2 = 0.0f;
GLfloat movement3 = 0.0f;
GLfloat ballPosition = 0.0f;
GLboolean kick1 = false;
GLboolean kick2 = false;
GLfloat ballVelocity = 0.0f;
GLfloat ballYvalue = 0.0f;
GLfloat ballZvalue = 0.0f;

// Window display size
GLsizei winWidth = 800, winHeight = 600;
//font for text
int font = (int)GLUT_BITMAP_8_BY_13;
const float lighting[3] = { 0.95f, 0.95f, 0.9f };

void drawBall()
{
	#define P 1.6180339889
	static GLfloat vertices[] = {
		-P      ,  2      , -(1 + 2 * P),
		-1      , -3 * P    ,  0      ,
		(2 + P)  , -2 * P    ,  1      ,
		0      ,  1      ,  3 * P    ,
		-1      , -(2 + P)  ,  2 * P    ,
		-3 * P    ,  0      ,  1      ,
		1      , -(2 + P)  ,  2 * P    ,
		-2 * P    ,  1      , -(2 + P)  ,
		1      ,  (2 + P)  , -2 * P    ,
		2      ,  (1 + 2 * P), -P      ,
		-(2 + P)  , -2 * P    ,  1      ,
		-(2 + P)  ,  2 * P    , -1      ,
		-1      , -(2 + P)  , -2 * P    ,
		-P      , -2      , -(1 + 2 * P),
		-(1 + 2 * P), -P      ,  2      ,
		(1 + 2 * P),  P      ,  2      ,
		-1      ,  3 * P    ,  0      ,
		(1 + 2 * P),  P      , -2      ,
		-2      ,  (1 + 2 * P),  P      ,
		-(1 + 2 * P), -P      , -2      ,
		3 * P    ,  0      ,  1      ,
		P      , -2      ,  (1 + 2 * P),
		(1 + 2 * P), -P      , -2      ,
		0      , -1      , -3 * P    ,
		0      , -1      ,  3 * P    ,
		1      ,  (2 + P)  ,  2 * P    ,
		-(1 + 2 * P),  P      , -2      ,
		-2      ,  (1 + 2 * P), -P      ,
		1      , -3 * P    ,  0      ,
		(1 + 2 * P), -P      ,  2      ,
		-2 * P    , -1      , -(2 + P)  ,
		2 * P    ,  1      ,  (2 + P)  ,
		P      ,  2      ,  (1 + 2 * P),
		(2 + P)  ,  2 * P    , -1      ,
		-(2 + P)  , -2 * P    , -1      ,
		P      , -2      , -(1 + 2 * P),
		2      , -(1 + 2 * P),  P      ,
		3 * P    ,  0      , -1      ,
		-2 * P    ,  1      ,  (2 + P)  ,
		-(1 + 2 * P),  P      ,  2      ,
		-P      , -2      ,  (1 + 2 * P),
		(2 + P)  , -2 * P    , -1      ,
		-1      ,  (2 + P)  ,  2 * P    ,
		-P      ,  2      ,  (1 + 2 * P),
		1      ,  3 * P    ,  0      ,
		-2 * P    , -1      ,  (2 + P)  ,
		P      ,  2      , -(1 + 2 * P),
		1      , -(2 + P)  , -2 * P    ,
		2 * P    ,  1      , -(2 + P)  ,
		2 * P    , -1      ,  (2 + P)  ,
		-1      ,  (2 + P)  , -2 * P    ,
		2      ,  (1 + 2 * P),  P      ,
		(2 + P)  ,  2 * P    ,  1      ,
		-2      , -(1 + 2 * P), -P      ,
		0      ,  1      , -3 * P    ,
		-3 * P    ,  0      , -1      ,
		2 * P    , -1      , -(2 + P)  ,
		2      , -(1 + 2 * P), -P      ,
		-2      , -(1 + 2 * P),  P      ,
		-(2 + P)  ,  2 * P    ,  1
	};

	static GLubyte pentagon[12][5] = {
		{ 13, 23, 35, 47, 12 },
		{ 18, 59, 11, 27, 16 },
		{ 19, 30, 7, 26, 55 },
		{ 21, 24, 40, 4, 6 },
		{ 43, 3, 32, 25, 42 },
		{ 44, 9, 33, 52, 51 },
		{ 46, 54, 0, 50, 8 },
		{ 48, 17, 37, 22, 56 },
		{ 49, 31, 15, 20, 29 },
		{ 5, 39, 38, 45, 14 },
		{ 53, 1, 58, 10, 34 },
		{ 57, 28, 36, 2, 41 }
	};

	static GLubyte hexagon[20][6] = {
		{ 10, 14, 45, 40, 4, 58 },
		{ 11, 26, 7, 0, 50, 27 },
		{ 18, 59, 39, 38, 43, 42 },
		{ 2, 36, 6, 21, 49, 29 },
		{ 20, 37, 22, 41, 2, 29 },
		{ 25, 51, 52, 15, 31, 32 },
		{ 26, 11, 59, 39, 5, 55 },
		{ 28, 1, 53, 12, 47, 57 },
		{ 28, 1, 58, 4, 6, 36 },
		{ 31, 32, 3, 24, 21, 49 },
		{ 34, 19, 30, 13, 12, 53 },
		{ 37, 17, 33, 52, 15, 20 },
		{ 41, 22, 56, 35, 47, 57 },
		{ 44, 9, 8, 50, 27, 16 },
		{ 45, 38, 43, 3, 24, 40 },
		{ 48, 46, 54, 23, 35, 56 },
		{ 5, 55, 19, 34, 10, 14 },
		{ 51, 25, 42, 18, 16, 44 },
		{ 7, 0, 54, 23, 13, 30 },
		{ 9, 8, 46, 48, 17, 33 }
	};

	// Reset Matrix and then translate and scale a Cube
	glTranslatef(ballPosition, 0.2f + ballYvalue, 3.0f - ballZvalue);
	glScalef(0.02f, 0.02f, 0.02f);
	glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(35.0f, 0.0f, 0.0f, 1.0f);
	//draw verteces, pentagons, and hexagons in black and white
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i<12; i++) {
		glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, pentagon[i]);
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i<20; i++) {
		glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, hexagon[i]);
	}
}

void launchBall()
{

	ballZvalue += ballVelocity;
	ballYvalue = fabs(5.0f*ballVelocity*sin(2*PI*F0*TS*ballZvalue)*exp(-1.0*TS*ballZvalue));
	if (ballZvalue >= 15.0f)
	{
		//reset
		kick1 = false;
		kick2 = false;
		ballPosition = 0.0f;
		ballVelocity = 0.0f;
		ballYvalue = 0.0f;
		ballZvalue = 0.0f;
	}
}

void moveRings()
{
	static GLfloat value1 = 0.03f;
	static GLfloat value2 = 0.04f;
	static GLfloat value3 = 0.05f;

	Sleep(SLEEP);
	if (movement1 >= 4.0f || movement1 <= -4.0f)
	{
		value1 = -value1;
	}
	movement1 += value1;


	if (movement2 >= 4.0f || movement2 <= -4.0f)
	{
		value2 = -value2;
	}
	movement2 += value2;

	if (movement3 >= 4.0f || movement3 <= -4.0f)
	{
		value3 = -value3;
	}
	movement3 += value3;

	if (kick1)
	{
		ballVelocity += 0.01f;
	}

	if (kick2)
	{
		launchBall();
	}
	glutPostRedisplay();
}


/* Initialize OpenGL Graphics */
void init() {
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);
	quad = gluNewQuadric();
	// Set background color to black 
	glClearColor(0.53f, 0.8f, 1.0f, 1.0f);
	// Maximize depth display
	glClearDepth(1.0f);
	// Enable depth testing for z-culling
	glEnable(GL_DEPTH_TEST);
	// Set the type of depth-test
	glDepthFunc(GL_LEQUAL);
	// Provide smooth shading
	glShadeModel(GL_SMOOTH);
	//move rings
	glutIdleFunc(moveRings);
}

void cleanup()
{
	gluDeleteQuadric(quad);
}

// convenience function for displaying strings
void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;

	glRasterPos3f(x, y, -7.0);

	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}

}

void displayDirections(void) {
	// Directions for car
	glColor3f(1.0f, 1.0f, 0.0f);
	renderBitmapString(-3.5f, 2.7f, (void *)font, "Game Day Challenge");
	renderBitmapString(-3.5f, 2.55f, (void *)font, "Use [a][d] keys to more left and right.");
	renderBitmapString(-3.5f, 2.4f, (void *)font, "Hold [space] to build up power.");
	renderBitmapString(-3.5f, 2.25f, (void *)font, "Release [space] to kick ball.");
	renderBitmapString(-3.5f, 2.1f, (void *)font, "Ball Power: ");

}

// Display Function
void displayfcn() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//print the menu
	displayDirections();

	//place camera
	gluLookAt(0.0f, 1.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();


	//add models
	//ball power
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	//glTranslatef(movement1, 1.0f, -7.0f);
	glRectf(-1.8f, 1.7f, -1.8f + ballVelocity, 1.6f);

	//ground
	glPushMatrix();
	glColor3f(0.5f, 0.6f, 0.1);
	glScalef(10.0f, 0.1f, 16.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	//drawGroundLines
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (float i = -7.0f; i <= 5.0f; i++)
	{
		glVertex3f(-4.0f, 0.1f, i);
		glVertex3f(4.0f, 0.1f, i);
	}
	glEnd();
	glPopMatrix();

	//draw rings
	glPushMatrix();
	glColor3f(4.0f, 0.84f, 0.0f); //gold
	glTranslatef(movement1, 1.0f, -7.0f);
	glutSolidTorus(0.03f, 0.3f, 16, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.75f, 0.75f, 0.75f); //silver
	glTranslatef(movement2, 1.0f, -3.0f);
	glutSolidTorus(0.03f, 0.3f, 16, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.545f, 0.411f, 0.078f); //bronze
	glTranslatef(movement3, 1.0f, 0.0f);
	glutSolidTorus(0.03f, 0.3f, 16, 32);
	glPopMatrix();

	//drawBall
	glPushMatrix();
	drawBall();
	glPopMatrix();

	glPopMatrix();
	// Double buffering
	glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		ballPosition -= 0.1f; //move ball left
		break;
	case 'd':
		ballPosition += 0.1f; // move ball right
		break;
	case ' ':
		kick1 = true; //start building power
		break;
	default:
		break;
	}
}

void keyUp(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		kick1 = false; //release the ball
		kick2 = true;
	}
}


// Windows redraw function
void winReshapeFcn(GLsizei width, GLsizei height) {
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport 
	// Allows for resizing without major display issues
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Enable perspective projection with fovy, aspect, zNear and zFar
	// This is the camera view and objects align with view frustum	
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	// Set the window's initial width & height
	glutInitWindowSize(winWidth, winHeight);
	// Position the window's initial top-left corner
	glutInitWindowPosition(50, 50);
	// Create window with the given title
	glutCreateWindow(title);
	// Display Function
	glutDisplayFunc(displayfcn);
	// Reshape function
	glutReshapeFunc(winReshapeFcn);
	// Initialize
	init();

	// Keyboard functions
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);


	// Process Loop
	glutMainLoop();
	cleanup();
}