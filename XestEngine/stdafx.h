// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
//�ر��ض�����
#pragma warning( disable : 4005)

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
//C++ ͷ�ļ�
#include <iostream>
#include <string>

//DirectX ͷ�ļ�
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
//DirectX ���ļ�
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11d.lib" )
#pragma comment( lib, "D3DCompiler.lib" )
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dx9d.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )


//�趨String����
#define String std::string

//���������ռ����
using std::cout;
using std::cin;
using std::endl;

//����SafeRelease
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
   if(x != NULL)        \
         {                    \
      x->Release();     \
      x = NULL;         \
         }
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(x) \
   if(x != NULL)             \
         {                         \
      delete[] x;            \
      x = NULL;              \
         }
#endif
#define SafeRelease SAFE_RELEASE