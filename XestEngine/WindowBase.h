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
	HINSTANCE m_hInstance;							   // 当前实例
	HWND      m_hWnd;                                  // 窗口句柄
	String    m_sTitle;				                   // 标题栏文本
	String    m_sWindowClass;                          // 主窗口类名
	MSG       m_msg;                                   // Windows消息
	HACCEL    m_hAccelTable;                           // 快捷键列表
	int       m_nCmdShow;                              // 窗口显示模式

	ATOM	  RegisterClass();  //注册窗口                      
	bool	  InitInstance();   //初始化窗口



	int			m_clientWidth;		//窗口大小
	int			m_clientHeight;
	bool		m_isMinimized;		//是否最小化
	bool		m_isMaximized;		//是否最大化
	bool		m_isPaused;			//是否暂停运行
	bool		m_isResizing;		//当鼠标正在改变窗口尺寸时


public:
	WindowBase(HINSTANCE hInstance=NULL, int nCmdShow = SW_SHOWNORMAL, String title = "Demo", int width = 640, int height = 480);
	virtual ~WindowBase();

	HINSTANCE	GetInstance()	const				{ return m_hInstance; }
	HWND		GetWindow()		const				{ return m_hWnd; }
	void		SetWindowTitle(String title)	{ SetWindowText(m_hWnd, title.c_str()); }
	String		GetWindowTitle()	            { return m_sTitle; }

	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);  //消息处理函数
	INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

	void SetInstance(HINSTANCE hInstance);
	
	virtual bool Init();       //程序初始化
	virtual int  Run() final;  //程序主循环 禁止重写
	virtual void Render();        //帧渲染 子类重写   
	virtual void Exit();       //程序退出
	virtual void Update();     //每帧更新

                
};




namespace
{
	//全局变量
	WindowBase *g_theApp = nullptr;
	UINT	g_x4MsaaQuality;
}
