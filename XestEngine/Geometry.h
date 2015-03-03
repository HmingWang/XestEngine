#pragma once

#include "stdafx.h"

//����һ��ͨ�õĶ���ṹ��λ�á����ߡ����ߡ���������
struct Vertex
{
	Vertex(){}
	Vertex(const XMFLOAT3 _pos, XMFLOAT3 _normal = { 0,0,0 }, XMFLOAT3 _tangent = { 0,0,0}, XMFLOAT2 _tex = {0,0}) :
		pos(_pos), normal(_normal), tangent(_tangent), tex(_tex){}

	XMFLOAT3	pos;
	XMFLOAT3	normal;
	XMFLOAT3	tangent;
	XMFLOAT2	tex;
};

//��������ṹ�����㼯��+��������
struct MeshData
{
	vector<Vertex>	vertices;
	vector<UINT>	indices;
};

//����һ�������壺ָ����(X����)����(Y����)����(Z����)
void CreateBox(float width, float height, float depth, MeshData &mesh);
//����һ��������ӣ�ָ���ܿ��(X����)���ܸ߶�(Z����); m��nΪ���߷����ϵĸ�������
void CreateGrid(float width, float height, UINT m, UINT n, MeshData &mesh);
//����һ��Բ��(�����ϡ���������)��ָ���϶˰뾶(topRadius)���¶˰뾶(bottomRadius)���߶�(height)��
//sllice��stack
void CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
//���ֳɵ�Բ������Ͽ�
void AddCylinderTopCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
//���ֳɵ�Բ������¿�
void AddCylinderBottomCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
//����һ�����壺ָ���뾶(radius)��slice��stack
void CreateSphere(float radius, int slice, int stack, MeshData &mesh);