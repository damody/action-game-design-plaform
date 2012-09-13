
// Standard Header For Most Programs
#include <windows.h>   
// The GL Header
#include <gl/gl.h>     
// The GL Utility Toolkit (Glut)
#include <gl/glut.h>
// Angle For The Triangle
float	g_triangle_rotation;
// Speed For Rotation
float	g_rotation_speed;
// Offset For X
float	g_offset_x;
// Offset For Y
float	g_offset_y;
// Create Some Everyday Functions
bool InitGL ()
{
	// Enable Smooth Shading
	glShadeModel(GL_SMOOTH);
	// Black Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	// Depth Buffer Setup
	glClearDepth(1.0f);
	// Enables Depth Testing
	glEnable(GL_DEPTH_TEST);
	// The Type Of Depth Testing To Do	
	glDepthFunc(GL_LEQUAL);
	return TRUE;
}

void display ( void )   // Create The Display Function
{
	// Clear Screen And Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();		// Reset The Current Modelview Matrix
	glPushMatrix();
	// Move Left 1.5 Units And Into The Screen 6.0
	glTranslatef(g_offset_x, g_offset_y, 0.0f);
	// Rotate The Triangle On The Y axis
	glRotatef(g_triangle_rotation,0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);		// Drawing Using Triangles
	glColor3f(1.0f,0.0f,0.0f);	// Red
	glVertex3f( 0.0f, 0.6f, 0.0f);	// Top Of Triangle (Front)
	glColor3f(0.0f,1.0f,0.0f);	// Green
	glVertex3f(-0.6f,-0.6f, 0.6f);	// Left Of Triangle (Front)
	glColor3f(0.0f,0.0f,1.0f);	// Blue
	glVertex3f( 0.6f,-0.6f, 0.6f);	// Right Of Triangle (Front)
	glColor3f(1.0f,0.0f,0.0f);	// Red
	glVertex3f( 0.0f, 0.6f, 0.0f);	// Top Of Triangle (Right)
	glColor3f(0.0f,0.0f,1.0f);	// Blue
	glVertex3f( 0.6f,-0.6f, 0.6f);	// Left Of Triangle (Right)
	glColor3f(0.0f,1.0f,0.0f);	// Green
	glVertex3f( 0.6f,-0.6f, -0.6f);	// Right Of Triangle (Right)
	glColor3f(1.0f,0.0f,0.0f);	// Red
	glVertex3f( 0.0f, 0.6f, 0.0f);	// Top Of Triangle (Back)
	glColor3f(0.0f,1.0f,0.0f);	// Green
	glVertex3f( 0.6f,-0.6f, -0.6f);	// Left Of Triangle (Back)
	glColor3f(0.0f,0.0f,1.0f);	// Blue
	glVertex3f(-0.6f,-0.6f, -0.6f);	// Right Of Triangle (Back)
	glColor3f(1.0f,0.0f,0.0f);	// Red
	glVertex3f( 0.0f, 0.6f, 0.0f);	// Top Of Triangle (Left)
	glColor3f(0.0f,0.0f,1.0f);	// Blue
	glVertex3f(-0.6f,-0.6f,-0.6f);	// Left Of Triangle (Left)
	glColor3f(0.0f,1.0f,0.0f);	// Green
	glVertex3f(-0.6f,-0.6f, 0.6f);	// Right Of Triangle (Left)
	glEnd();			// Finished Drawing The Triangle
	glPopMatrix();
	// Increase The Rotation Variable For The Triangle ( NEW )
	g_triangle_rotation+=g_rotation_speed;
	// Swap The Buffers To Not Be Left With A Clear Screen
	glutSwapBuffers();
}

// Create The Reshape Function (the viewport)
void ReSizeGLScene( int width , int height )
{
	if (height==0)    // Prevent A Divide By Zero By
	{
		height=1; // Making Height Equal One
	}
	// Reset The Current Viewport
	glViewport(0,0,width,height);
	// Select The Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset The Projection Matrix
	glLoadIdentity();
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glTranslatef(0, 0, -4.0f);
	// Select The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glOrtho(-1,1,-1,1,-1,1);
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) 
	{
	case 27: // When Escape Is Pressed...
		exit(0);   // Exit The Program
		break;
	case 43: // '+'
		g_rotation_speed+=0.01;
		break;
	case 45: // '-'
		g_rotation_speed-=0.01;
		break;
	default:        // Now Wrap It Up
		break;
	}
}

// Create Special Function (required for arrow keys)
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys ) 
	{
	case GLUT_KEY_UP:
		g_offset_y += 0.05;
		break;
	case GLUT_KEY_DOWN: 
		g_offset_y -= 0.05;
		break;
	case GLUT_KEY_LEFT:
		g_offset_x -= 0.05;
		break;
	case GLUT_KEY_RIGHT: 
		g_offset_x += 0.05;
		break;
	}
}

// Create Main Function For Bringing It All Together
void main( int argc, char** argv )
{
	// init global variable
	g_rotation_speed = 0.02f;
	g_triangle_rotation = 0;
	g_offset_x = 0;
	g_offset_y = 0;
	glutInit( &argc, argv );
	// Display Mode
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(500, 500);
	// Window Title (argv[0] for current directory as title)
	glutCreateWindow( "NeHe's OpenGL Framework" ); 
	//glutFullScreen( );          // Put Into Full Screen
	// Go Into A 500 By 500 Window
	//glutReshapeWindow ( 500, 500 );
	InitGL();
	// Matching Earlier Functions To Their Counterparts
	glutDisplayFunc(display);
	glutReshapeFunc(ReSizeGLScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(display);
	// Initialize The Main Loop
	glutMainLoop();
}

