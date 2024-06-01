#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <Windows.h>
#include <functional>

class Renderer
{
public:
    Renderer();
    ~Renderer();

public:
    HRESULT Initialize(HWND hwnd);
    void Cleanup();
    void Render(std::function<void()> renderCallback);

public:
    ID3D11DeviceContext *GetDeviceContext() { return g_pImmediateContext; }
    IDXGISwapChain *GetSwapChain() { return g_pSwapChain; }

private:
    HRESULT InitDevice(HWND hwnd);

    D3D_DRIVER_TYPE g_driverType;
    D3D_FEATURE_LEVEL g_featureLevel;
    ID3D11Device *g_pd3dDevice;
    ID3D11DeviceContext *g_pImmediateContext;
    IDXGISwapChain *g_pSwapChain;
    ID3D11RenderTargetView *g_pRenderTargetView;
    ID3D11Buffer *g_pVertexBuffer;
    ID3D11InputLayout *g_pVertexLayout;
    ID3D11VertexShader *g_pVertexShader;
    ID3D11PixelShader *g_pPixelShader;

    // Vertex structure
    struct SimpleVertex
    {
        DirectX::XMFLOAT3 Pos;
    };

    const char *g_strVS;
    const char *g_strPS;
};
