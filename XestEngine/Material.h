#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "stdafx.h"

struct Material
{
	XMFLOAT4	ambient;
	XMFLOAT4	diffuse;
	XMFLOAT4	specular;	//第4个元素为材质的镜面反射系数
};
#endif