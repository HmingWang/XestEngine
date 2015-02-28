//================================================
//Windows base framework 
//
//================================================
#pragma once

#include "stdafx.h"
#include "resource.h"

class XFramework
{
private:
	HINSTANCE m_hInstance;							   // ��ǰʵ��
	HWND      m_hWnd;                                  // ���ھ��
	String    m_sTitle;				                   // �������ı�
	String    m_sWindowClass;                          // ����������
	MSG       m_msg;                                   // Windows��Ϣ
	HACCEL    m_hAccelTable;                           // ��ݼ��б�
	int       m_nCmdShow;                              // ������ʾģʽ

	ATOM	  RegisterClass();
	BOOL	  InitInstance();

public:
	XFramework(HINSTANCE hInstance=NULL, int nCmdShow = SW_SHOWNORMAL, String title = "Demo", int width = 640, int height = 480);
	virtual ~XFramework();
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);  //��Ϣ������
	INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
	
	//virtual bool Init(); //�����ʼ��
	virtual int  Run();  //������ѭ��
	//virtual bool Exit(); //�����˳�
	void SetInstance(HINSTANCE hInstance);
};




namespace
{
	//ȫ�ֱ���
	XFramework *g_theApp = nullptr;
	UINT	g_x4MsaaQuality;
}
