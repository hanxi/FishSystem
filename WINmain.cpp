//WINmain.cpp

#include "WINmain.h"
#include <math.h>


bool FrameFunc()
{
	// Get the time elapsed since last call of FrameFunc().
	// This will help us to synchronize on different
	// machines and video modes.
	double dt=hge->Timer_GetDelta();
	// Process keys
	switch(hge->Input_GetKey())
	{
		case HGEK_ESCAPE:	return true;
	}
	
	////////////////////////////////////////////////////////
	//������Ⱥ��λ��
	showEnvironment->Frame_Environment(dt);

	// Continue execution
	return false;
}

// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	// Begin rendering quads.
	// This function must be called
	// before any actual rendering.
	hge->Gfx_BeginScene();

	//��ʾ����
	showEnvironment->Render_Environment();

	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//���ڴ�С
	int win_width=800,win_height=600;
	// Get HGE interface
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "test.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "��Ⱥ��̬ϵͳ");

	// Set up video mode
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, win_width);
	hge->System_SetState(HGE_SCREENHEIGHT, win_height);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_HIDEMOUSE, false);

	if(hge->System_Initiate())
	{
		/////////////////////////////////////////////////////////
		char *pic_predator_name = "С����.jpg";
		char *pic_prey_name = "С��ͷ��.jpg";
		char *pic_BG_name = "bg2.jpg";
		int n_predator_frames = 10;
		int n_prey_frames = 10;
		double predator_FPS = 2;
		double prey_FPS = 2;

		showEnvironment = new ShowEnvironment(hge,win_width,win_height,
			pic_BG_name,
			pic_predator_name,n_predator_frames,predator_FPS,
			pic_prey_name,n_prey_frames,prey_FPS);
		
		//����
		hge->System_Start();

	}

	//�����ر��˳�
	hge->System_Shutdown();
	hge->Release();
	return   0; 
}

