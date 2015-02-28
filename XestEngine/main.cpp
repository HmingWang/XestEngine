#include "stdafx.h"
#include "XestApp.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO:  在此放置代码。
	XestApp xestApp;
	g_theApp = &xestApp;
	g_theApp->SetInstance(hInstance);
	return g_theApp->Run();
}