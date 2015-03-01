#pragma once
#include "WindowBase.h"
class DXBase :
	public WindowBase
{
private:
	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = NULL;                          //D3D11�豸
	ID3D11DeviceContext*    m_pImmediateContext = NULL;                   //�豸������
	IDXGISwapChain*         m_pSwapChain = NULL;                          //������
	ID3D11RenderTargetView* m_pRenderTargetView = NULL;                   //��Ⱦ������ͼ

	HRESULT InitDevice();        //��ʼ��D3D

public:
	DXBase();
	virtual ~DXBase();

	virtual bool Init()   override;       //�����ʼ��
	virtual void Render() override;       //֡��Ⱦ ������д   
	virtual void Exit()   override;       //�����˳�
	void CleanupDevice();
	void CalculateFPS();  //����֡��
	
	// IDeviceNotify  �豸��ʧ����
	virtual void OnDeviceLost();
	virtual void OnDeviceRestored();
};

