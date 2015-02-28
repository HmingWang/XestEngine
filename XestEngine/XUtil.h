#pragma once
//==========================
//π§æﬂ¿‡
//==========================
#include "stdafx.h"
class XUtil
{
private:
	XUtil() = default;
public:
	static XUtil& GetInstance();
	void Debug(String);
};

#define sUtil XUtil::GetInstance()
