#pragma once
#include "stdafx.h"
#include "Geometry.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
private:
	XMFLOAT4 m_Position;//世界坐标
	XMFLOAT4 m_Rotation;//旋转坐标
	XMFLOAT4 m_Scale;   //缩放

	vector<Vertex> m_Vertices; //顶点集合
	vector<UINT>   m_Indices;  //索引集合
};

