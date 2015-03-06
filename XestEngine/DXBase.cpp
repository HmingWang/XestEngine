#include "DXBase.h"
#include "XUtil.h"
#include "Geometry.h"


DXBase::DXBase()
{
}


DXBase::~DXBase()
{
}

//--------------------------------------------------------------------------------------
//D3D�豸��ʼ��
//--------------------------------------------------------------------------------------
HRESULT DXBase::InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(this->GetWindow(), &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = this->GetWindow();  //������ھ��
	sd.SampleDesc.Count = 1;   //���ز�������ݵȼ�
	sd.SampleDesc.Quality = 0; //���ز��������Ʒ��
	sd.Windowed = TRUE;        //���ڻ�

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture //������Ȼ�������
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_pd3dDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	//�󶨵���Ⱦ����
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView,nullptr);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width  = static_cast<FLOAT>(width);   //�ӿڿ�ȣ�һ����󻺳���һ�£��Ա���ͼ�񲻱���  
	vp.Height = static_cast<FLOAT>(height); //�߶ȣ�ͬ��  
	vp.MinDepth = 0.0f; // ��С���ֵ��0.0f
	vp.MaxDepth = 1.0f; // ������ֵ��1.0f
	vp.TopLeftX = 0; //���Ͻ�X����
	vp.TopLeftY = 0; //���Ͻ�Y����
	m_pImmediateContext->RSSetViewports(1, &vp);

	// Initialize the world matrix
	m_World = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_View = XMMatrixLookAtLH(Eye, At, Up);

	// Initialize the projection matrix
	m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f);

	return S_OK;
}

//--------------------------------------------------------------------------------------
//��Ⱦ������
//--------------------------------------------------------------------------------------
void DXBase::Render()
{
	CalculateFPS();
	//// Update our time
	//static float t = 0.0f;
	//if (m_driverType == D3D_DRIVER_TYPE_REFERENCE)
	//{
	//	t += (float)XM_PI * 0.0125f;
	//}
	//else
	//{
	//	static DWORD dwTimeStart = 0;
	//	DWORD dwTimeCur = GetTickCount();
	//	if (dwTimeStart == 0)
	//		dwTimeStart = dwTimeCur;
	//	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	//}

	//// 1st Cube: Rotate around the origin
	//XMMATRIX m_World1 = XMMatrixRotationY(t);

	//// 2nd Cube:  Rotate around origin
	//XMMATRIX mSpin = XMMatrixRotationZ(-t);
	//XMMATRIX mOrbit = XMMatrixRotationY(-t * 2.0f);
	//XMMATRIX mTranslate = XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
	//XMMATRIX mScale = XMMatrixScaling(0.3f, 0.3f, 0.3f);

	//XMMATRIX m_World2 = mScale * mSpin * mTranslate * mOrbit;

	////
	//// Clear the back buffer
	////
	//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red, green, blue, alpha
	//m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

	////
	//// Clear the depth buffer to 1.0 (max depth)
	////
	//m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	////
	//// Update variables for the first cube
	////
	//ConstantBuffer cb1;
	//cb1.mWorld = XMMatrixTranspose(m_World1);
	//cb1.mView = XMMatrixTranspose(m_View);
	//cb1.mProjection = XMMatrixTranspose(m_Projection);
	//m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb1, 0, 0);

	////
	//// Render the first cube
	////
	//m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	//m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	//m_pImmediateContext->DrawIndexed(36, 0, 0);

	////
	//// Update variables for the second cube
	////
	//ConstantBuffer cb2;
	//cb2.mWorld = XMMatrixTranspose(m_World2);
	//cb2.mView = XMMatrixTranspose(m_View);
	//cb2.mProjection = XMMatrixTranspose(m_Projection);
	//m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb2, 0, 0);

	////
	//// Render the second cube
	////
	//m_pImmediateContext->DrawIndexed(36, 0, 0);

	////
	//// Present our back buffer to our front buffer
	////
	//m_pSwapChain->Present(0, 0);

	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red, green, blue, alpha
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);


	/*UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);*/
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

	//����Ϊ���߿򡱻���ģʽ
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.DepthClipEnable = true;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;		//WireFrame
	rsDesc.FrontCounterClockwise = false;
	ID3D11RasterizerState *rsState(NULL);
	m_pd3dDevice->CreateRasterizerState(&rsDesc, &rsState);
	m_pImmediateContext->RSSetState(rsState);

	//XMMATRIX view = m_View;
	//XMMATRIX proj = m_Projection;

	m_World = XMMatrixRotationY(XM_PI*0.0125);
	ConstantBuffer cb1;
	cb1.mWorld = XMMatrixTranspose(m_World);
	cb1.mView = XMMatrixTranspose(m_View);
	cb1.mProjection = XMMatrixTranspose(m_Projection);
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb1, 0, 0);

	m_pImmediateContext->DrawIndexed(m_box.indices.size(), 0, 0);
	m_pSwapChain->Present(0, 0);

	//ID3DX11EffectTechnique *tech = m_fx->GetTechniqueByName("BasicColor");
	//D3DX11_TECHNIQUE_DESC techDesc;
	//tech->GetDesc(&techDesc);

	//ע����ƺ�����DrawIndexed������ʹ��
	//�������еļ����嶥��/����ȫ��������һ�����嶥��/������������
	//�����Ҫ�ṩ��Ӧ������Ķ��㡢������ʼ�㣬�Լ�����������

	//��������
	//XMMATRIX world= m_World;
	//m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&(world*view*proj)));
	//for (UINT i = 0; i < techDesc.Passes; ++i)
	//{
	//	tech->GetPassByIndex(i)->Apply(0, m_deviceContext);
	//	//								������������	   ������ʼ��	������ʼ��
	//	m_deviceContext->DrawIndexed(m_grid.indices.size(), m_gridIStart, m_gridVStart);
	//}
	////����������
	//world = XMLoadFloat4x4(&m_boxWorld);
	//m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&(world*view*proj)));
	//for (UINT i = 0; i < techDesc.Passes; ++i)
	//{
	//	tech->GetPassByIndex(i)->Apply(0, m_deviceContext);
	//	//								������������	   ������ʼ��	������ʼ��
	//	m_deviceContext->DrawIndexed(m_box.indices.size(), m_boxIStart, m_boxVStart);
	//}
	////���Ƶ�5����λ�����ģ�
	//world = XMLoadFloat4x4(&m_sphereWorld[4]);
	//m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&(world*view*proj)));
	//for (UINT i = 0; i < techDesc.Passes; ++i)
	//{
	//	tech->GetPassByIndex(i)->Apply(0, m_deviceContext);
	//	//								������������	   	������ʼ��		������ʼ��
	//	m_deviceContext->DrawIndexed(m_sphere.indices.size(), m_sphereIStart, m_sphereVStart);
	//}
	////����4��Բ����4����
	//for (UINT i = 0; i < 4; ++i)
	//{
	//	world = XMLoadFloat4x4(&m_cylinderWorld[i]);
	//	m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&(world*view*proj)));
	//	for (UINT j = 0; j < techDesc.Passes; ++j)
	//	{
	//		tech->GetPassByIndex(j)->Apply(0, m_deviceContext);
	//		//									������������	   	������ʼ��			������ʼ��
	//		m_deviceContext->DrawIndexed(m_cylinder.indices.size(), m_cylinderIStart, m_cylinderVStart);
	//	}

	//	world = XMLoadFloat4x4(&m_sphereWorld[i]);
	//	m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&(world*view*proj)));
	//	for (UINT j = 0; j < techDesc.Passes; ++j)
	//	{
	//		tech->GetPassByIndex(j)->Apply(0, m_deviceContext);
	//		//									������������	   ������ʼ��	������ʼ��
	//		m_deviceContext->DrawIndexed(m_sphere.indices.size(), m_sphereIStart, m_sphereVStart);
	//	}
	//}

	//m_swapChain->Present(0, 0);
	//return true;
}

//--------------------------------------------------------------------------------------
//��ʼ��������
//--------------------------------------------------------------------------------------
bool DXBase::Init()
{
	Trace("Init");
	if (FAILED(InitDevice()))
		return false;

	if (FAILED(BuildShader()))
		return false;

	if (FAILED(BuildBuffers()))
		return false;

	m_timer.Reset();
	return true;
}

//--------------------------------------------------------------------------------------
//ϵͳ�˳�������
//--------------------------------------------------------------------------------------
void DXBase::Exit()
{
	Trace("Exit");
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();
}

//--------------------------------------------------------------------------------------
// ����Shader ʹ��D3DCompileFromFile
//--------------------------------------------------------------------------------------
HRESULT DXBase::CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
//#if _WIN32_WINNT <=_WIN32_WINNT_WIN8
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(szFileName, NULL, NULL,
		szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();
//#endif
	return S_OK;

}

//--------------------------------------------------------------------------------------
// ����ÿ��֡��
//--------------------------------------------------------------------------------------
void DXBase::CalculateFPS()
{
	//Trace("CalculateFPS");
	m_timer.Tick(); //���¼�ʱ��
	static float begin = m_timer.TotalTime();
	static int frameCounter = 0;
	if (m_timer.TotalTime() - begin >= 1.f)
	{
		std::ostringstream text;
		text << "      FPS: " << frameCounter << "    FrameTime: " << 1000.f / frameCounter << L"ms";
		SetWindowTitle(GetWindowTitle() + text.str());
		Trace(text.str());
		begin = m_timer.TotalTime();
		frameCounter = 0;
	}
	++frameCounter;
}

//--------------------------------------------------------------------------------------
// ���ɶ�����ɫ��
//--------------------------------------------------------------------------------------
HRESULT DXBase::CreateVertexShader()
{
	Trace("CreateVertexShader");
	HRESULT hr = S_OK;
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile(L"VertexShader.hlsl", "main", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			"����VertexShader����", "Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = m_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}
	//-------------------------------------------------------------------------------------------------------
	// Define the input layout    //InputLayoutԪ������
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = m_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &m_pVertexLayout);
	pVSBlob->Release();


	// Set the input layout
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);

	return hr;
}

//--------------------------------------------------------------------------------------
// ����������ɫ��
//--------------------------------------------------------------------------------------
HRESULT DXBase::CreatePixelShader()
{
	Trace("CreatePixelShader");
	HRESULT hr;
	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(L"PixelShader.hlsl", "main", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			"����PixelShader����", "Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = m_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader);
	pPSBlob->Release();

	return hr;
}

//--------------------------------------------------------------------------------------
// ����Shader
//--------------------------------------------------------------------------------------
HRESULT DXBase::BuildShader()
{
	HRESULT hr;
	//����Shader
	//1.Vertex Shader
	hr = CreateVertexShader();
	if (FAILED(hr))
		return hr;
	//2.Pixel Shader
	hr = CreatePixelShader();
	if (FAILED(hr))
		return hr;
	return S_OK;
}

//--------------------------------------------------------------------------------------
// ����InputLayout
//--------------------------------------------------------------------------------------
HRESULT DXBase::BuildInputLayout()
{
	return S_OK;
}

//--------------------------------------------------------------------------------------
// ����Compute Shader
//--------------------------------------------------------------------------------------
HRESULT DXBase::CompileComputeShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ ID3D11Device* device, _Outptr_ ID3DBlob** blob)
{
	if (!srcFile || !entryPoint || !device || !blob)
		return E_INVALIDARG;

	*blob = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	// We generally prefer to use the higher CS shader profile when possible as CS 5.0 is better performance on 11-class hardware
	LPCSTR profile = (device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";

	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(srcFile, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint, profile,
		flags, 0, &shaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			Trace((char*)errorBlob->GetBufferPointer());  //��ӡShader���������Ϣ
			errorBlob->Release();
		}

		if (shaderBlob)
			shaderBlob->Release();

		return hr;
	}

	*blob = shaderBlob;

	return hr;
}

//--------------------------------------------------------------------------------------
// ���ɶ��㻺�塢��������
//--------------------------------------------------------------------------------------
HRESULT DXBase::BuildBuffers()
{
	HRESULT hr;

	//RECT rc;
	//GetClientRect(GetWindow(), &rc);
	//UINT width = rc.right - rc.left;
	//UINT height = rc.bottom - rc.top;
	////-----------------------------------------------------------------------------------
	////�������㻺��
	//SimpleVertex vertices[] =
	//{
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	//};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	//ZeroMemory(&InitData, sizeof(InitData));
	//InitData.pSysMem = vertices;
	//hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	//if (FAILED(hr))
	//	return hr;

	////���ö��㻺��
	//UINT stride = sizeof(SimpleVertex);
	//UINT offset = 0;
	//m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	////-----------------------------------------------------------------------------------
	////������������
	//WORD indices[] =
	//{
	//	3, 1, 0,
	//	2, 1, 3,

	//	0, 5, 4,
	//	1, 5, 0,

	//	3, 4, 7,
	//	0, 4, 3,

	//	1, 6, 5,
	//	2, 6, 1,

	//	2, 7, 6,
	//	3, 7, 2,

	//	6, 4, 5,
	//	7, 4, 6,
	//};
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//InitData.pSysMem = indices;
	//hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
	//if (FAILED(hr))
	//	return hr;

	//�趨��������
	//m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//�趨ͼԪ����
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//-----------------------------------------------------------------------------------
	//������������
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = m_pd3dDevice->CreateBuffer(&bd, NULL, &m_pConstantBuffer);
	if (FAILED(hr))
		return hr;



	CreateBox(2, 1.5f, 2, m_box);


	UINT totalVerts = m_box.vertices.size();
	UINT totalIndices = m_box.indices.size();

	vector<SimpleVertex> vertices(totalVerts);

	for (UINT i = 0; i < m_box.vertices.size(); ++i)
	{
		vertices[m_boxVStart + i].pos = m_box.vertices[i].pos;
		vertices[m_boxVStart + i].color = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	}
	

	D3D11_BUFFER_DESC vbDesc = { 0 };
	vbDesc.ByteWidth = totalVerts * sizeof(SimpleVertex);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;
	vbDesc.StructureByteStride = 0;
	vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA vbData;
	vbData.pSysMem = &vertices[0];
	vbData.SysMemPitch = 0;
	vbData.SysMemSlicePitch = 0;

	if (FAILED(m_pd3dDevice->CreateBuffer(&vbDesc, &vbData, &m_pVertexBuffer)))
	{
		MessageBox(NULL, "CreateVertexBuffer failed!", "Error", MB_OK);
		return false;
	}

	vector<UINT> indices(totalIndices);

	for (UINT i = 0; i < m_box.indices.size(); ++i)
	{
		indices[m_boxIStart + i] = m_box.indices[i];
	}


	D3D11_BUFFER_DESC ibDesc = { 0 };
	ibDesc.ByteWidth = totalIndices * sizeof(UINT);
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;
	ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA ibData;
	ibData.pSysMem = &indices[0];
	ibData.SysMemPitch = 0;
	ibData.SysMemSlicePitch = 0;

	if (FAILED(m_pd3dDevice->CreateBuffer(&ibDesc, &ibData, &m_pIndexBuffer)))
	{
		MessageBox(NULL, "CreateIndexBuffer failed!", "Error", MB_OK);
		return false;
	}

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	return true;

	return S_OK;
}