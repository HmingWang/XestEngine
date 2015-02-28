#include "XFramework.h"

//Windows窗口过程
// 定义应用程序的入口点。
//
#include "stdafx.h"


//应用程序消息处理函数，通过调用全局对象的成员函数实现
LRESULT CALLBACK WinAppProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_theApp->WndProc(hwnd, uMsg, wParam, lParam);
}




XFramework::XFramework(HINSTANCE hInstance, int nCmdShow, String title, int width, int height) :
m_hInstance(hInstance),
m_nCmdShow(nCmdShow),
m_sTitle(title),
m_sWindowClass("XFW")
{
	//初始化全局对象（指针）
	//g_theApp = this;

	//在Debug模式下，我们打开控制台，显示一些有用的信息
#if defined(DEBUG) || defined(_DEBUG)
	FILE *f(NULL);
	if (AllocConsole())
	{
		freopen_s(&f, "CONOUT$", "w", stdout);
	}
#endif
}

int XFramework::Run()
{
	RegisterClass();

	// 执行应用程序初始化: 
	if (!InitInstance())
	{
		return FALSE;
	}

	m_hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_XEST_ENGINE));

	// 主消息循环: 
	while (GetMessage(&m_msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(m_msg.hwnd, m_hAccelTable, &m_msg))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
	}

	return (int)m_msg.wParam;
}

//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM XFramework::RegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WinAppProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wcex.lpszClassName = m_sWindowClass.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL XFramework::InitInstance()
{
	//HWND hWnd;

	//m_hInstance = hInstance; // 将实例句柄存储在全局变量中

	m_hWnd = CreateWindow(m_sWindowClass.c_str(), m_sTitle.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, m_hInstance, NULL);

	if (!m_hWnd)
	{
		return FALSE;
	}

	ShowWindow(m_hWnd, m_nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK XFramework::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, XFramework::About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK XFramework::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void XFramework::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

XFramework::~XFramework()
{

}
