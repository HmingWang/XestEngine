#pragma once
//==========================
//������
//==========================
#include "stdafx.h"

namespace XUtil
{
	void Trace(String s);
}
using namespace XUtil;

namespace Colors
{
	//���弸����������ɫֵ�������ڳ�����ʹ��
	const XMFLOAT4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	const XMFLOAT4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	const XMFLOAT4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	const XMFLOAT4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	const XMFLOAT4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	const XMFLOAT4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	const XMFLOAT4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	const XMFLOAT4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	const XMFLOAT4 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
};