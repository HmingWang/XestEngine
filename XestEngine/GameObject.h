#pragma once
#include "stdafx.h"
#include "Geometry.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
private:
	XMFLOAT4 m_Position;//��������
	XMFLOAT4 m_Rotation;//��ת����
	XMFLOAT4 m_Scale;   //����

	vector<Vertex> m_Vertices; //���㼯��
	vector<UINT>   m_Indices;  //��������
};

