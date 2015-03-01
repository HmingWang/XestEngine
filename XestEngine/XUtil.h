#pragma once
//==========================
//π§æﬂ¿‡
//==========================
#include "stdafx.h"
#include "WindowBase.h"


namespace XUtil
{

	void Trace(String s)
	{
	#if defined(DEBUG) || defined(_DEBUG)
		cout << s << endl;
	#endif
	}

}

using namespace XUtil;