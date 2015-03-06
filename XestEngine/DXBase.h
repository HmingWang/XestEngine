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
	ID3D11Device*           m_pd3dDevice          = nullptr;                   //D3D11�豸
	ID3D11DeviceContext*    m_pImmediateContext   = nullptr;                   //�豸������
	IDXGISwapChain*         m_pSwapChain          = nullptr;                   //������
	ID3D11RenderTargetView* m_pRenderTargetView   = nullptr;                   //��Ⱦ������ͼ
	ID3D11Texture2D*        m_pDepthStencil       = nullptr;                   //��Ȼ�������
	ID3D11DepthStencilView* m_pDepthStencilView   = nullptr;                   //��Ȼ�����ͼ
	ID3D11VertexShader*     m_pVertexShader       = nullptr;                   //������ɫ��
	ID3D11PixelShader*      m_pPixelShader        = nullptr;                   //������ɫ��
	ID3D11ComputeShader*    m_pComputeShader      = nullptr;                   //����Shader
	ID3D11InputLayout*      m_pVertexLayout       = nullptr;                   //���㲼��
	ID3D11Buffer*           m_pVertexBuffer       = nullptr;                   //���㻺��
	ID3D11Buffer*           m_pIndexBuffer        = nullptr;                   //��������
	ID3D11Buffer*           m_pConstantBuffer     = nullptr;                   //��������

	XMMATRIX                m_World;              //����任����
	XMMATRIX                m_View;               //�ӽǱ任����
	XMMATRIX                m_Projection;         //͸�Ӿ���

	MeshData m_grid, m_box, m_sphere, m_cylinder;
	UINT m_gridVStart, m_boxVStart, m_sphereVStart, m_cylinderVStart;
	UINT m_gridIStart, m_boxIStart, m_sphereIStart, m_cylinderIStart;

	Timer m_timer;
	HRESULT InitDevice();                  //��ʼ��D3D
	HRESULT CompileShaderFromFile(         LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT CompileComputeShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, //����Shader windows8.1
		_In_ ID3D11Device* device, _Outptr_ ID3DBlob** blob);
	HRESULT CreateVertexShader();
	HRESULT CreatePixelShader();
	HRESULT BuildShader();
	HRESULT BuildInputLayout();
	HRESULT BuildBuffers();



public:
	DXBase();
	virtual ~DXBase();


	virtual bool Init()   override;       //�����ʼ��
	virtual void Render() override;       //֡��Ⱦ ������д   
	virtual void Exit()   override;       //�����˳�
	void CleanupDevice();
	void CalculateFPS();  //����֡��
	
	// IDeviceNotify  �豸��ʧ����
	//virtual void OnDeviceLost();
	//virtual void OnDeviceRestored();
};


//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex //����ṹ
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};


struct ConstantBuffer   //Shader����
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};