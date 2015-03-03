#include "DXBase.h"
#include "XUtil.h"
#include "Geometry.h"


DXBase::DXBase()
{
}


DXBase::~DXBase()
{
}


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
	sd.OutputWindow = this->GetWindow();  //输出窗口句柄
	sd.SampleDesc.Count = 4;   //多重采样抗锯齿等级
	sd.SampleDesc.Quality = 0; //多重采样抗锯齿品质
	sd.Windowed = TRUE;        //窗口化

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

	//绑定到渲染管线
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width  = static_cast<FLOAT>(width);   //视口宽度，一般与后缓冲区一致，以保持图像不变形  
	vp.Height = static_cast<FLOAT>(height); //高度，同上  
	vp.MinDepth = 0.0f; // 最小深度值：0.0f
	vp.MaxDepth = 1.0f; // 最大深度值：1.0f
	vp.TopLeftX = 0; //左上角X坐标
	vp.TopLeftY = 0; //左上角Y坐标
	m_pImmediateContext->RSSetViewports(1, &vp);

	return S_OK;
}

void DXBase::Render()
{
	CalculateFPS();
	// Update our time
	static float t = 0.0f;
	if (m_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	////
	//// Animate the cube
	////
	//m_World = XMMatrixRotationY(t);

	////
	//// Clear the back buffer
	////
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);

	////
	//// Update variables
	////
	//ConstantBuffer cb;
	//cb.mWorld = XMMatrixTranspose(m_World);
	//cb.mView = XMMatrixTranspose(m_View);
	//cb.mProjection = XMMatrixTranspose(m_Projection);
	//m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	//
	// Renders a triangle
	//
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	//m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pImmediateContext->Draw(3, 0);        // 36 vertices needed for 12 triangles in a triangle list

	//
	// Present our back buffer to our front buffer
	//
	m_pSwapChain->Present(0, 0);
}

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
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT DXBase::CompileShaderFromFile(CHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
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
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

void DXBase::CalculateFPS()
{
	//Trace("CalculateFPS");
	m_timer.Tick(); //更新计时器
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
// Create Vertex Shader
//--------------------------------------------------------------------------------------
HRESULT DXBase::CreateVertexShader()
{
	Trace("CreateVertexShader");
	HRESULT hr = S_OK;
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile("VertexShader.hlsl", "main", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
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
	// Define the input layout    //InputLayout元素描述
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

HRESULT DXBase::CreatePixelShader()
{
	Trace("CreatePixelShader");
	HRESULT hr;
	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile("PixelShader.hlsl", "main", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = m_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader);
	pPSBlob->Release();

	return hr;
}

HRESULT DXBase::BuildShader()
{
	HRESULT hr;
	//编译Shader
	//1.Vertex Shader
	hr = CreatePixelShader();
	if (FAILED(hr))
		return hr;
	//2.Pixel Shader
	hr = CreateVertexShader();
	if (FAILED(hr))
		return hr;
	return S_OK;
}

HRESULT DXBase::BuildInputLayout()
{
	return S_OK;
}

HRESULT DXBase::BuildBuffers()
{
	HRESULT hr;
	Vertex vertices[] = {
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f) },
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	// Set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
}
