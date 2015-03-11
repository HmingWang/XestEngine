#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "stdafx.h"
//平行光
struct DirLight
{
	XMFLOAT4	ambient;	//环境光
	XMFLOAT4	diffuse;	//漫反射光
	XMFLOAT4	specular;	//高光

	XMFLOAT3	dir;		//方向
	float	unused;		//“4D向量”对齐用
};
//点光源
struct PointLight
{
	XMFLOAT4	ambient;	//环境光
	XMFLOAT4	diffuse;	//漫反射光
	XMFLOAT4	specular;	//高光

	XMFLOAT3	pos;		//光源位置
	float	range;		//光源照射范围

	XMFLOAT3	att;		//光强衰减系数
	float	unused;		//"4D向量"对齐用
};
//聚光灯
struct SpotLight
{
	XMFLOAT4	ambient;	//环境光
	XMFLOAT4	diffuse;	//漫反射光
	XMFLOAT4	specular;	//高光

	XMFLOAT3	dir;		//方向
	float	range;		//照射范围

	XMFLOAT3	pos;		//位置
	float	spot;		//聚光强度系数

	XMFLOAT3	att;		//误差系数
	float	theta;		//最大发散角度
};



#endif
