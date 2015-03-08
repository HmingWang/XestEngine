#pragma once
//==========================
//工具类
//==========================
#include "stdafx.h"
#include <exception>

namespace XUtil
{
	void Trace(String s);

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// 在此行中设置断点，以捕获 Win32 API 错误。
			throw std::exception("aaaaa");
		}
	}

}
using namespace XUtil;