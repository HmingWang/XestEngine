#pragma once
#include "WindowBase.h"
#include "Timer.h"
#include "Geometry.h"


class DXBase :
	public WindowBase
{
private:
	D3D_DRIVER_TYPE         m_driverType          = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel        = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice          = nullptr;                   //D3D11设备
	ID3D11DeviceContext*    m_pImmediateContext   = nullptr;                   //设备上下文
	IDXGISwapChain*         m_pSwapChain          = nullptr;                   //交换链
	ID3D11RenderTargetView* m_pRenderTargetView   = nullptr;                   //渲染对象视图
	ID3D11Texture2D*        m_pDepthStencil       = nullptr;                   //深度缓冲纹理
	ID3D11DepthStencilView* m_pDepthStencilView   = nullptr;                   //深度缓冲视图
	ID3D11VertexShader*     m_pVertexShader       = nullptr;                   //顶点着色器
	ID3D11PixelShader*      m_pPixelShader        = nullptr;                   //像素着色器
	ID3D11ComputeShader*    m_pComputeShader      = nullptr;                   //计算Shader
	ID3D11InputLayout*      m_pVertexLayout       = nullptr;                   //顶点布局
	ID3D11Buffer*           m_pVertexBuffer       = nullptr;                   //顶点缓存
	ID3D11Buffer*           m_pIndexBuffer        = nullptr;                   //索引缓存
	ID3D11Buffer*           m_pConstantBuffer     = nullptr;                   //常量缓存

	XMMATRIX                m_World;              //世界变换矩阵
	XMMATRIX                m_View;               //视角变换矩阵
	XMMATRIX                m_Projection;         //透视矩阵

	MeshData m_grid, m_box, m_sphere, m_cylinder;
	UINT m_gridVStart, m_boxVStart, m_sphereVStart, m_cylinderVStart;
	UINT m_gridIStart, m_boxIStart, m_sphereIStart, m_cylinderIStart;

	Timer m_timer;
	HRESULT InitDevice();                  //初始化D3D
	HRESULT CompileShaderFromFile(         LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT CompileComputeShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, //编译Shader windows8.1
		_In_ ID3D11Device* device, _Outptr_ ID3DBlob** blob);
	HRESULT CreateVertexShader();
	HRESULT CreatePixelShader();
	HRESULT BuildShader();
	HRESULT BuildInputLayout();
	HRESULT BuildBuffers();



public:
	DXBase();
	virtual ~DXBase();


	virtual bool Init()   override;       //程序初始化
	virtual void Render() override;       //帧渲染 子类重写   
	virtual void Exit()   override;       //程序退出
	void CleanupDevice();
	void CalculateFPS();  //计算帧数
	
	// IDeviceNotify  设备丢失处理
	//virtual void OnDeviceLost();
	//virtual void OnDeviceRestored();
};


//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex //顶点结构
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};


struct ConstantBuffer   //Shader常量
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};