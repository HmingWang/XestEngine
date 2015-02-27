//================================================
//Windows base framework 
//
//================================================
#pragma once

#include "stdafx.h"
#include "resource.h"
#define MAX_LOADSTRING 100

class XFramework
{
public:
	virtual bool Init(); //程序初始化
	virtual void Run();  //程序主循环
	virtual bool Exit(); //程序退出
};