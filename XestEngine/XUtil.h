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
	const XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	const XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	const XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	const XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	const XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	const XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	const XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	const XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	const XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
};