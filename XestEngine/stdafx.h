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
#include <sdkddkver.h> //windows �汾�궨��

//#define _WIN32_WINNT _WIN32_WINNT_WIN8  //����windows�汾

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
//C++ ͷ�ļ�
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

//DirectX ͷ�ļ�()
#include <d3d11_2.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <DirectXColors.h>

//DirectX ���ļ�
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "D3DCompiler.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

#if _WIN32_WINNT <_WIN32_WINNT_WIN8  //win7 ʹ�ÿ��ļ���ͷ�ļ�
#include <d3dx11.h>
#include <xnamath.h>
#pragma comment( lib, "d3dx11d.lib" )
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "d3dx9d.lib" )
#endif

//�趨String����
#define String std::string

//���������ռ����
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::set;
using std::map;
using namespace DirectX;

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