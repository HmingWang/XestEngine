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
	HINSTANCE m_hInstance;							   // 当前实例
	HWND      m_hWnd;                                  // 窗口句柄
	String    m_sTitle;				                   // 标题栏文本
	String    m_sWindowClass;                          // 主窗口类名
	MSG       m_msg;                                   // Windows消息
	HACCEL    m_hAccelTable;                           // 快捷键列表
	int       m_nCmdShow;                              // 窗口显示模式

	ATOM	  RegisterClass();
	BOOL	  InitInstance();

public:
	XFramework(HINSTANCE hInstance=NULL, int nCmdShow = SW_SHOWNORMAL, String title = "Demo", int width = 640, int height = 480);
	virtual ~XFramework();
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);  //消息处理函数
	INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
	
	//virtual bool Init(); //程序初始化
	virtual int  Run();  //程序主循环
	//virtual bool Exit(); //程序退出
	void SetInstance(HINSTANCE hInstance);
};




namespace
{
	//全局变量
	XFramework *g_theApp = nullptr;
	UINT	g_x4MsaaQuality;
}
