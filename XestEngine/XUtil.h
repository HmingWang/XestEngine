#pragma once
//==========================
//������
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
			// �ڴ��������öϵ㣬�Բ��� Win32 API ����
			throw std::exception("aaaaa");
		}
	}

}
using namespace XUtil;