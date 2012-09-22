
// Standard Header For Most Programs
#include <windows.h>   
// The GL Header
#include <gl/gl.h>
#include <gl/glu.h>
#include <time.h>
#include "Tbox.h"
#include "Timer.h"
#include "ptrManager.h"
GameTimer g_Timer;
float g_LastTime = 100.0;
float g_LastTime2;
Polygon2D g_Polygon2D;
Tbox* g_Tbox;
Tboxs g_Tboxs;
int g_fps;
int g_size=1;
bool g_enable = true;
bool g_DrawTbox = true;
ptrManager<Tbox*, GetPolygonFromTbox> TboxPtrManager;
// Angle For The Triangle
float	g_triangle_rotation;
// Speed For Rotation
float	g_rotation_speed;
// Offset For X
float	g_offset_x;
// Offset For Y
float	g_offset_y;
// Private GDI Device Context
HDC	g_hDC=NULL;
// Permanent Rendering Context
HGLRC	g_hRC=NULL;
// Holds Our Window Handle
HWND	g_hWnd=NULL;
// Holds The Instance Of The Application
HINSTANCE	g_hInstance;
// Array Used For The Keyboard Routine
bool	g_bKeys[256];
// Window Active Flag Set To TRUE By Default
bool	g_bActive=TRUE;
// Declaration For WndProc
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void InitGL()
{
	srand(time(NULL));
	g_Timer.reset();
	g_Timer.start();
	g_Tbox = new Tbox(Vector3(0.0, 0.0, 0.0));
	g_rotation_speed = 0;
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

	std::cout << "Key R: Reset Polygon" << std::endl;
	std::cout << "Key Q: Stop/Start Draw" << std::endl;
	std::cout << "Key Space: Create Tbox Stop/Start" << std::endl;
	std::cout << "Key +: Create Tbox Rate Up" << std::endl;
	std::cout << "Key -: Create Tbox Rate Down" << std::endl;
}
int cc = 0;
void Update()
{
	g_fps++;
	g_Timer.tick();
	if( g_LastTime > 0.2 && g_enable)
	{
		for(int i = 0; i < g_size; i++)
		{
			g_Tboxs.push_back(new Tbox());
			TboxPtrManager.AddPtr(g_Tboxs.back());
		}
		g_LastTime = 0;
	}else
		g_LastTime += g_Timer.getDeltaTime();
	if( g_LastTime2 > 3.0)
	{
		std::cout <<"AddCount:"<<g_size*5<<"\tUpdateCount:" <<g_fps<< "\tboxCount:"<<g_Tboxs.size() <<"\tCollisionCount:"<<cc << std::endl;
		g_LastTime2 = 0;
		g_fps = 0;
	}else
		g_LastTime2 += g_Timer.getDeltaTime();
	//std::cout << g_Timer.getGameTime() << std::endl;
// 	if (g_bKeys[VK_UP])	g_Tbox->m_Direction.y += 0.01;
// 	if (g_bKeys[VK_DOWN])	g_Tbox->m_Direction.y -= 0.01;
// 	if (g_bKeys[VK_LEFT])	g_Tbox->m_Direction.x -= 0.01;
// 	if (g_bKeys[VK_RIGHT])	g_Tbox->m_Direction.x += 0.01;
	if (g_bKeys[VK_SPACE])  g_enable=!g_enable;
	if (g_bKeys[VK_ADD])	g_size++;
	if (g_bKeys[VK_SUBTRACT])	g_size--;
	if (g_bKeys['R'])	g_Tbox->RandomReset();
	if (g_bKeys['Q'])	g_DrawTbox = !g_DrawTbox;

	g_Tbox->Update(g_Timer.getDeltaTime());
	g_Tbox->m_Color = Vector3(0.0, 0.0, 1.0);
	for(std::vector<Tbox*>::iterator it = g_Tboxs.begin();
		it != g_Tboxs.end(); ++it)
	{
		(*it)->Update(g_Timer.getDeltaTime());
	}
	TboxPtrManager.PrepareForCollision();
	Tboxs t_Tboxs = TboxPtrManager.GetCollision(g_Tbox, GetPolygonFromTbox());
	cc = t_Tboxs.size();
	for(std::vector<Tbox*>::iterator it = t_Tboxs.begin();
		it != t_Tboxs.end(); ++it)
	{
		(*it)->OnCollisionEnter();
	}
	memset(g_bKeys, 0, sizeof(g_bKeys));
}
inline void myfunc(Vector2 vec2)
{
	glVertex3f(vec2.x, vec2.y, 0.0f);
}
void DrawTbox(Tbox* tb)
{
	glPushMatrix();
	//glTranslatef(tb->m_Position.x, tb->m_Position.y, 0.0f);
	//glRotatef(tb->m_Direction.angleBetween(Vector3()).valueDegrees(), 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_POLYGON);
	glColor3f(tb->m_Color.x, tb->m_Color.y, tb->m_Color.z);
	std::for_each(tb->m_Polygon2D.Points().begin(), tb->m_Polygon2D.Points().end(), myfunc);
	glEnd();
	
	glPopMatrix();
}
void DrawAABB(Tbox* tb)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(tb->m_Polygon2D.AABB().m_Max.x, tb->m_Polygon2D.AABB().m_Max.y, 0.0f);
	glVertex3f(tb->m_Polygon2D.AABB().m_Min.x, tb->m_Polygon2D.AABB().m_Max.y, 0.0f);
	glVertex3f(tb->m_Polygon2D.AABB().m_Min.x, tb->m_Polygon2D.AABB().m_Min.y, 0.0f);
	glVertex3f(tb->m_Polygon2D.AABB().m_Max.x, tb->m_Polygon2D.AABB().m_Min.y, 0.0f);
	glEnd();
}
void DrawGLScene()   // Create The Display Function
{
	if(g_DrawTbox){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Clear Screen And Depth Buffer
	DrawAABB(g_Tbox);
	for(std::vector<Tbox*>::iterator it = g_Tboxs.begin();
		it != g_Tboxs.end(); ++it)
	{
		DrawAABB(*it);
	}
	DrawTbox(g_Tbox);
	for(std::vector<Tbox*>::iterator it = g_Tboxs.begin();
		it != g_Tboxs.end(); ++it)
	{
		DrawTbox(*it);
	}
	}
	// Increase The Rotation Variable For The Triangle ( NEW )
	g_triangle_rotation+=g_rotation_speed;
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
}

void KillGLWindow()							
{
	if (g_hRC)							
	{
		if (!wglMakeCurrent(NULL,NULL))				
		{
			MessageBox(NULL,"Release Of DC And RC Failed.",
				"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(g_hRC))						
		{
			MessageBox(NULL,"Release Rendering Context Failed.",
				"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		g_hRC=NULL;						
	}
	if (g_hDC && !ReleaseDC(g_hWnd,g_hDC))				
	{
		MessageBox(NULL,"Release Device Context Failed.",
			"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hDC=NULL;					
	}
	if (g_hWnd && !DestroyWindow(g_hWnd))			
	{
		MessageBox(NULL,"Could Not Release hWnd.",
			"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hWnd=NULL;						
	}
	if (!UnregisterClass("OpenGL",g_hInstance))			
	{
		MessageBox(NULL,"Could Not Unregister Class.",
			"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hInstance=NULL;					
	}
}


/*	This Code Creates Our OpenGL Window.  Parameters Are:			*
*	title			- Title To Appear At The Top Of The Window	*
*	width			- Width Of The GL Window Mode			*
*	height			- Height Of The GL Window Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits)
{
	GLuint	PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;			// Windows Class Structure
	DWORD	dwExStyle;			// Window Extended Style
	DWORD	dwStyle;			// Window Style
	RECT		WindowRect;		// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;		// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;			// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height


	g_hInstance		= GetModuleHandle(NULL);		// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;			// WndProc Handles Messages
	wc.cbClsExtra		= 0;					// No Extra Window Data
	wc.cbWndExtra		= 0;					// No Extra Window Data
	wc.hInstance		= g_hInstance;				// Set The Instance
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);		// Load The Default Icon
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);		// Load The Arrow Pointer
	wc.hbrBackground	= NULL;					// No Background Required For GL
	wc.lpszMenuName		= NULL;					// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";				// Set The Class Name

	if (!RegisterClass(&wc))		// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											
	}

	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;		// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;				// Windows Style


	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(g_hWnd=CreateWindowEx(	dwExStyle, // Extended Style For The Window
		"OpenGL",		// Class Name
		title,			// Window Title
		dwStyle |		// Defined Window Style
		WS_CLIPSIBLINGS |	// Required Window Style
		WS_CLIPCHILDREN,	// Required Window Style
		0, 0,			// Window Position
		WindowRect.right-WindowRect.left,	// Calculate Window Width
		WindowRect.bottom-WindowRect.top,	// Calculate Window Height
		NULL,			// No Parent Window
		NULL,			// No Menu
		g_hInstance,		// Instance
		NULL)))			// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();				
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;					
	}

	static	PIXELFORMATDESCRIPTOR pfd=	// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
		1,			// Version Number
		PFD_DRAW_TO_WINDOW |	// Format Must Support Window
		PFD_SUPPORT_OPENGL |	// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		bits,			// Select Our Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored
		0,			// No Alpha Buffer
		0,			// Shift Bit Ignored
		0,			// No Accumulation Buffer
		0, 0, 0, 0,		// Accumulation Bits Ignored
		16,			// 16Bit Z-Buffer (Depth Buffer)  
		0,			// No Stencil Buffer
		0,			// No Auxiliary Buffer
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,			// Reserved
		0, 0, 0			// Layer Masks Ignored
	};

	if (!(g_hDC=GetDC(g_hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	// Did Windows Find A Matching Pixel Format?
	if (!(PixelFormat=ChoosePixelFormat(g_hDC,&pfd)))	
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	// Are We Able To Set The Pixel Format?
	if(!SetPixelFormat(g_hDC,PixelFormat,&pfd))		
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	// Are We Able To Get A Rendering Context?
	if (!(g_hRC=wglCreateContext(g_hDC)))				
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	// Try To Activate The Rendering Context
	if(!wglMakeCurrent(g_hDC,g_hRC))					
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	// Show The Window
	ShowWindow(g_hWnd,SW_SHOW);						
	// Slightly Higher Priority
	SetForegroundWindow(g_hWnd);						
	// Sets Keyboard Focus To The Window
	SetFocus(g_hWnd);								
	// Set Up Our Perspective GL Screen
	ReSizeGLScene(width, height);					
	// Initialize Our Newly Created GL Window
	InitGL();
	// Success
	return TRUE;									
}


LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
			 UINT	uMsg,			// Message For This Window
			 WPARAM	wParam,			// Additional Message Information
			 LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									
	{
	case WM_ACTIVATE:	
		if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam)))
			g_bActive=TRUE;						
		else
			g_bActive=FALSE;						
		return 0;
	case WM_SYSCOMMAND:	
		switch (wParam)					
		{
		case SC_SCREENSAVE:				
		case SC_MONITORPOWER:				
			return 0;				
		}
		break;
	case WM_CLOSE:		
		PostQuitMessage(0);				
		return 0;
	case WM_KEYDOWN:	
		g_bKeys[wParam] = TRUE;				
		return 0;
	case WM_KEYUP:		
		g_bKeys[wParam] = FALSE;				
		return 0;
	case WM_SIZE:		
		ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
		return 0;
	}
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

// Create Main Function For Bringing It All Together
int main ( int argc, char** argv )
{
	// init global variable
	g_rotation_speed = 0.02f;
	g_triangle_rotation = 0;
	g_offset_x = 0;
	g_offset_y = 0;
	MSG	msg;						
	BOOL	done=FALSE;					
	// Create Our OpenGL Window
	if (!CreateGLWindow("Windows SDK",640,480,32))
	{
		return 0;					
	}
	while(!done)						
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)		
			{
				done=TRUE;			
			}
			else					
			{
				TranslateMessage(&msg);		
				DispatchMessage(&msg);		
			}
		}
		else	

		{
			if (g_bKeys[VK_ESCAPE])
			{
				done=TRUE;			
			}
			else					
			{
				Update();
				DrawGLScene();
				SwapBuffers(g_hDC);		
			}
		}
	}
	KillGLWindow();						
	return (msg.wParam);					
}

