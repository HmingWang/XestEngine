#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "stdafx.h"
//ƽ�й�
struct DirLight
{
	XMFLOAT4	ambient;	//������
	XMFLOAT4	diffuse;	//�������
	XMFLOAT4	specular;	//�߹�

	XMFLOAT3	dir;		//����
	float	unused;		//��4D������������
};
//���Դ
struct PointLight
{
	XMFLOAT4	ambient;	//������
	XMFLOAT4	diffuse;	//�������
	XMFLOAT4	specular;	//�߹�

	XMFLOAT3	pos;		//��Դλ��
	float	range;		//��Դ���䷶Χ

	XMFLOAT3	att;		//��ǿ˥��ϵ��
	float	unused;		//"4D����"������
};
//�۹��
struct SpotLight
{
	XMFLOAT4	ambient;	//������
	XMFLOAT4	diffuse;	//�������
	XMFLOAT4	specular;	//�߹�

	XMFLOAT3	dir;		//����
	float	range;		//���䷶Χ

	XMFLOAT3	pos;		//λ��
	float	spot;		//�۹�ǿ��ϵ��

	XMFLOAT3	att;		//���ϵ��
	float	theta;		//���ɢ�Ƕ�
};



#endif
