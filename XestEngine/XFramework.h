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
	virtual bool Init(); //�����ʼ��
	virtual void Run();  //������ѭ��
	virtual bool Exit(); //�����˳�
};