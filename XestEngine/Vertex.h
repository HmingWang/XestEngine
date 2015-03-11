#pragma once
#include "stdafx.h"
class Vertex
{
public:
	Vertex();
	Vertex(const XMFLOAT3 _pos, XMFLOAT3 _normal = { 0,0,0 }, XMFLOAT3 _tangent = { 0,0,0}, XMFLOAT2 _tex = {0,0}) :
		pos(_pos), normal(_normal), tangent(_tangent), tex(_tex){}
	~Vertex();

	XMFLOAT3	pos;
	XMFLOAT3	normal;
	XMFLOAT3	tangent;
	XMFLOAT2	tex;
private:
	XMFLOAT3	m_Position; //位置坐标
	XMFLOAT3	m_Normal;//法线
	XMFLOAT3	m_Tangent;//切线
	XMFLOAT2	m_TexCoord;//纹理坐标
	XMFLOAT4    m_Color;//颜色
};

