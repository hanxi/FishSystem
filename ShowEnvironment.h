//ShowEnvironment.h

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "Environment.h"
#include "Fish.h"
/*****************************************
�ࣺ��ʾͼ��
���ܣ�������Ⱥ��λ���ڴ�������ʾ��
������ShowEnvironment
*****************************************/
class ShowEnvironment
{
private:
	Environment environment;//ָ��һ����̬����
	HGE *hge;//ָ����ʾ�������	
	HTEXTURE predator_tex;//��ʳ��ȺͼƬ��
	hgeAnimation *predator_ani;//���������
	HTEXTURE prey_tex;//����ʳ��ȺͼƬ��
	hgeAnimation *prey_ani;//���������
	HTEXTURE bg_tex;
	hgeSprite* bgspr;
	double dt;
	int win_width;
	int win_height;
	int bg_width;
	int bg_height;
	
public:
	ShowEnvironment(HGE *in_hge, int in_win_width, int in_win_height,
		char *pic_bg_name,
		char *pic_predator_name, int n_predator_frames, double predator_FPS,
		char *pic_prey_name, int n_prey_frames, double prey_FPS)
		:hge(in_hge),win_width(in_win_width),win_height(in_win_height)
	{
		set_bg(pic_bg_name);
		//���ò�ʳ��ͼƬ
		predator_tex = hge->Texture_Load(pic_predator_name);//HTEXTURE
		//��������
		int w = hge->Texture_GetWidth(predator_tex,true)/n_predator_frames;
		int h = hge->Texture_GetHeight(predator_tex,true);
		predator_ani=new hgeAnimation(predator_tex,n_predator_frames,predator_FPS,0,0,w,h);//hgeAnimation
		predator_ani->SetHotSpot(predator_ani->GetWidth()/2.0,predator_ani->GetHeight()/2.0);
		predator_ani->Play();
		//���ñ���ʳ��ͼƬ
		prey_tex = hge->Texture_Load(pic_prey_name);//HTEXTURE
		//��������
		w = hge->Texture_GetWidth(prey_tex,true)/n_prey_frames;
		h = hge->Texture_GetHeight(prey_tex,true);
		prey_ani=new hgeAnimation(prey_tex,n_prey_frames,prey_FPS,0,0,w,h);//hgeAnimation
		prey_ani->SetHotSpot(prey_ani->GetWidth()/2.0,prey_ani->GetHeight()/2.0);
		prey_ani->Play();
	}
	void set_bg(char *pic_BG_name)
	{
		bg_tex=hge->Texture_Load(pic_BG_name);		
		bg_width = hge->Texture_GetWidth(bg_tex,true);
		bg_height = hge->Texture_GetHeight(bg_tex,true);
		bgspr=new hgeSprite(bg_tex,0,0,bg_width,bg_height);
		bgspr->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_ZWRITE);
		bgspr->SetColor(0xFF000000,0);
		bgspr->SetColor(0xFF000000,1);
		bgspr->SetColor(0xFF000040,2);
		bgspr->SetColor(0xFF000040,3);
	}
	~ShowEnvironment()
	{
		delete bgspr;
		delete predator_ani;
		delete prey_ani;
		hge->Texture_Free(bg_tex);
		hge->Texture_Free(predator_tex);			
		hge->Texture_Free(prey_tex);
	}
	void Frame_Environment(double in_dt);//���»���
	void Render_Environment();//��ʾ����
	void showFish(const vector<double>& body_size, const vector<Point>& position, hgeAnimation* fish_ani);
};
