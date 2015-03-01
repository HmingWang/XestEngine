#pragma once
#include "WindowBase.h"
class DXBase :
	public WindowBase
{
private:
	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = NULL;                          //D3D11设备
	ID3D11DeviceContext*    m_pImmediateContext = NULL;                   //设备上下文
	IDXGISwapChain*         m_pSwapChain = NULL;                          //交换链
	ID3D11RenderTargetView* m_pRenderTargetView = NULL;                   //渲染对象视图

	HRESULT InitDevice();        //初始化D3D

public:
	DXBase();
	virtual ~DXBase();

	virtual bool Init()   override;       //程序初始化
	virtual void Render() override;       //帧渲染 子类重写   
	virtual void Exit()   override;       //程序退出
	void CleanupDevice();
	void CalculateFPS();  //计算帧数
	
	// IDeviceNotify  设备丢失处理
	virtual void OnDeviceLost();
	virtual void OnDeviceRestored();
};

