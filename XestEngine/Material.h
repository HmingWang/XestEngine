#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "stdafx.h"

struct Material
{
	XMFLOAT4	ambient;
	XMFLOAT4	diffuse;
	XMFLOAT4	specular;	//��4��Ԫ��Ϊ���ʵľ��淴��ϵ��
};
#endif