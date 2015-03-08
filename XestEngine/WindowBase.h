//================================================
//X base framework 
//
//================================================
#pragma once

#include "stdafx.h"
#include "resource.h"

class WindowBase
{
private:
	HINSTANCE m_hInstance;							   // ��ǰʵ��
	HWND      m_hWnd;                                  // ���ھ��
	String    m_sTitle;				                   // �������ı�
	String    m_sWindowClass;                          // ����������
	MSG       m_msg;                                   // Windows��Ϣ
	HACCEL    m_hAccelTable;                           // ��ݼ��б�
	int       m_nCmdShow;                              // ������ʾģʽ

	ATOM	  RegisterClass();  //ע�ᴰ��                      
	bool	  InitInstance();   //��ʼ������



	int			m_clientWidth;		//���ڴ�С
	int			m_clientHeight;
	bool		m_isMinimized;		//�Ƿ���С��
	bool		m_isMaximized;		//�Ƿ����
	bool		m_isPaused;			//�Ƿ���ͣ����
	bool		m_isResizing;		//��������ڸı䴰�ڳߴ�ʱ


public:
	WindowBase(HINSTANCE hInstance=NULL, int nCmdShow = SW_SHOWNORMAL, String title = "Demo", int width = 640, int height = 480);
	virtual ~WindowBase();

	HINSTANCE	GetInstance()	const				{ return m_hInstance; }
	HWND		GetWindow()		const				{ return m_hWnd; }
	void		SetWindowTitle(String title)	{ SetWindowText(m_hWnd, title.c_str()); }
	String		GetWindowTitle()	            { return m_sTitle; }

	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);  //��Ϣ������
	INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

	void SetInstance(HINSTANCE hInstance);
	
	virtual bool Init();       //�����ʼ��
	virtual int  Run() final;  //������ѭ�� ��ֹ��д
	virtual void Render();        //֡��Ⱦ ������д   
	virtual void Exit();       //�����˳�
	virtual void Update();     //ÿ֡����

                
};




namespace
{
	//ȫ�ֱ���
	WindowBase *g_theApp = nullptr;
	UINT	g_x4MsaaQuality;
}
