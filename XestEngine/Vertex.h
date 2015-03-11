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
	XMFLOAT3	m_Position; //λ������
	XMFLOAT3	m_Normal;//����
	XMFLOAT3	m_Tangent;//����
	XMFLOAT2	m_TexCoord;//��������
	XMFLOAT4    m_Color;//��ɫ
};

