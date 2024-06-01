#include "Renderer.h"
#include <DirectXMath.h>

Renderer::Renderer()
    : g_driverType(D3D_DRIVER_TYPE_NULL), g_featureLevel(D3D_FEATURE_LEVEL_11_0),
      g_pd3dDevice(nullptr), g_pImmediateContext(nullptr), g_pSwapChain(nullptr),
      g_pRenderTargetView(nullptr), g_pVertexBuffer(nullptr), g_pVertexLayout(nullptr),
      g_pVertexShader(nullptr), g_pPixelShader(nullptr),
      g_strVS(
          "struct VS_INPUT                                     \n"
          "{                                                   \n"
          "    float4 Pos : POSITION;                          \n"
          "};                                                  \n"
          "struct PS_INPUT                                     \n"
          "{                                                   \n"
          "    float4 Pos : SV_POSITION;                       \n"
          "};                                                  \n"
          "PS_INPUT VS(VS_INPUT input)                         \n"
          "{                                                   \n"
          "    PS_INPUT output = (PS_INPUT)0;                  \n"
          "    output.Pos = input.Pos;                         \n"
          "    return output;                                  \n"
          "}"),
      g_strPS(
          "float4 PS(float4 Pos : SV_POSITION) : SV_TARGET     \n"
          "{                                                   \n"
          "    return float4(1.0f, 0.0f, 0.0f, 1.0f);          \n"
          "}")
{
}

Renderer::~Renderer()
{
    Cleanup();
}

HRESULT Renderer::Initialize(HWND hwnd)
{
    return InitDevice(hwnd);
}

void Renderer::Cleanup()
{
    if (g_pImmediateContext)
        g_pImmediateContext->ClearState();
    if (g_pVertexBuffer)
        g_pVertexBuffer->Release();
    if (g_pVertexLayout)
        g_pVertexLayout->Release();
    if (g_pVertexShader)
        g_pVertexShader->Release();
    if (g_pPixelShader)
        g_pPixelShader->Release();
    if (g_pRenderTargetView)
        g_pRenderTargetView->Release();
    if (g_pSwapChain)
        g_pSwapChain->Release();
    if (g_pImmediateContext)
        g_pImmediateContext->Release();
    if (g_pd3dDevice)
        g_pd3dDevice->Release();
}

HRESULT Renderer::InitDevice(HWND hwnd)
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(hwnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    // this is very important, if you don't set this flag, you will not be able to create a swap chain
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
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
            D3D_FEATURE_LEVEL_11_1,
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
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                           D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D *pBackBuffer = NULL;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
    if (FAILED(hr))
        return hr;

    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);

    // vertex shader
    ID3DBlob *pVSBlob = NULL;
    hr = D3DCompile(g_strVS, strlen(g_strVS) + 1, "VS", NULL, NULL, "VS", "vs_4_0", 0, 0, &pVSBlob, NULL);
    if (FAILED(hr))
    {
        MessageBox(NULL, L"The FX file cannot be compiled. Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create vertex shader
    hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

    // pixel shader
    ID3DBlob *pPSBlob = NULL;
    hr = D3DCompile(g_strPS, strlen(g_strPS) + 1, "PS", NULL, NULL, "PS", "ps_4_0", 0, 0, &pPSBlob, NULL);
    if (FAILED(hr))
    {
        MessageBox(NULL, L"The FX file cannot be compiled. Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Create vertex buffer
    SimpleVertex vertices[] =
        {
            {DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f)},
            {DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f)},
            {DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f)},
        };
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 3;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = vertices;
    hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
    if (FAILED(hr))
        return hr;

    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    // Set primitive topology
    g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return S_OK;
}

void Renderer::Render(std::function<void()> renderCallback)
{
    float clearColor[] = {0.0f, 0.2f, 0.4f, 1.0f};
    g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);

    // Render the triangle
    g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
    g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
    g_pImmediateContext->Draw(3, 0);

    renderCallback();

    g_pSwapChain->Present(0, 0);
}
