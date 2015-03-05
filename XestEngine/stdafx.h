// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
//关闭特定警告
#pragma warning( disable : 4005)

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
#include <sdkddkver.h> //windows 版本宏定义

//#define _WIN32_WINNT _WIN32_WINNT_WIN8  //定义windows版本

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件
//C++ 头文件
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

//DirectX 头文件()
#include <d3d11_2.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <DirectXColors.h>

//DirectX 库文件
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "D3DCompiler.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

#if _WIN32_WINNT <_WIN32_WINNT_WIN8  //win7 使用库文件和头文件
#include <d3dx11.h>
#include <xnamath.h>
#pragma comment( lib, "d3dx11d.lib" )
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "d3dx9d.lib" )
#endif

//设定String类型
#define String std::string

//常用命名空间变量
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::set;
using std::map;
using namespace DirectX;

//定义SafeRelease
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