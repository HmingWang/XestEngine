#include "XFramework.h"

//Windows���ڹ���
// ����Ӧ�ó������ڵ㡣
//
#include "stdafx.h"


//Ӧ�ó�����Ϣ��������ͨ������ȫ�ֶ���ĳ�Ա����ʵ��
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
	//��ʼ��ȫ�ֶ���ָ�룩
	//g_theApp = this;

	//��Debugģʽ�£����Ǵ򿪿���̨����ʾһЩ���õ���Ϣ
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

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance())
	{
		return FALSE;
	}

	m_hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_XEST_ENGINE));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL XFramework::InitInstance()
{
	//HWND hWnd;

	//m_hInstance = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��: 
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
		// TODO:  �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
