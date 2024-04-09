#include "d3d11.h"
#include "../../window/window.h"

static Window* window = Window::GetSingleton();

D3D11* D3D11::GetSingleton()
{
	static D3D11 d3d11;
	return &d3d11;
}
bool D3D11::Create(UINT _Width, UINT _Height)
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 2;
    desc.BufferDesc.Width = _Width;
    desc.BufferDesc.Height = _Height;
    desc.BufferDesc.Format = format;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = window->GetHandle();
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;
    desc.SwapEffect = swapEffect;

    UINT flags = 0;
#if defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL,
                                             driverType,
                                             NULL,
                                             flags,
                                             NULL,
                                             NULL,
                                             D3D11_SDK_VERSION,
                                             &desc,
                                             swapChain.GetAddressOf(),
                                             device.GetAddressOf(),
                                             &featureLevel,
                                             deviceContext.GetAddressOf())))
    {
        printf("create swapchain failed\n");
        return false;
    }

    if (!CreateRenderTargetView())
        return false;

    if (!CreateDepthStencilView(_Width, _Height))
        return false;

    return true;
}
void D3D11::SetViewport(UINT _Width, UINT _Height)
{
    D3D11_VIEWPORT vp;
    vp.Width = (float)_Width;
    vp.Height = (float)_Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);
}
void D3D11::SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology)
{
    if (_PrimitiveTopology == PT_NONE)
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED);
    else if (_PrimitiveTopology == PT_POINTLIST)
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    else if (_PrimitiveTopology == PT_LINELIST)
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    else if (_PrimitiveTopology == PT_LINESTRIP)
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    else if (_PrimitiveTopology == PT_TRIANGLELIST)
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    else if (_PrimitiveTopology == PT_TRIANGLESTRIP)
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    else printf("primitive topology is wrong\n");
}
void D3D11::SetRenderTarget()
{
    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
}
void D3D11::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
    float clear_color[4] = { _R, _G, _B, _A };
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clear_color);
    deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}
bool D3D11::ResizeBuffer(UINT _Width, UINT _Height)
{
    deviceContext->OMSetRenderTargets(0, NULL, NULL);
    if (renderTargetView) renderTargetView->Release();
    if (depthStencilView) depthStencilView->Release();

    if (FAILED(swapChain->ResizeBuffers(0, _Width, _Height, format, 0)))
    {
        printf("resize buffers failed\n");
        return false;
    }

    if (!CreateRenderTargetView())
        return false;

    if (!CreateDepthStencilView(_Width, _Height))
        return false;

    return true;
}
void D3D11::Present(bool _Vsync)
{
    swapChain->Present(_Vsync ? 1 : 0, 0);
}
bool D3D11::CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels)
{
    if (!device)
    {
        printf("device is null\n");
        return false;
    }

    if (FAILED(device->CheckMultisampleQualityLevels(format, _SampleCount, _QualityLevels)))
    {
        printf("check multisample quality levels failed\n");
        return false;
    }

    return true;
}
void D3D11::Release()
{
    if (swapChain) swapChain->Release();
    if (device) device->Release();
    if (deviceContext) deviceContext->Release();
    if (renderTargetView) renderTargetView->Release();
    if (depthStencilView) depthStencilView->Release();
}
bool D3D11::CreateRenderTargetView()
{
    ID3D11Texture2D* texture = NULL;
    if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&texture)))
    {
        printf("get buffer failed\n");
        return false;
    }

    if (FAILED(device->CreateRenderTargetView(texture, NULL, renderTargetView.GetAddressOf())))
    {
        printf("create render target view failed\n");
        return false;
    }

    texture->Release();
    return true;
}
bool D3D11::CreateDepthStencilView(UINT _Width, UINT _Height)
{
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(D3D11_TEXTURE2D_DESC));
    descDepth.Width = _Width;
    descDepth.Height = _Height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;

    ID3D11Texture2D* texture = NULL;
    if (FAILED(device->CreateTexture2D(&descDepth, NULL, &texture)))
    {
        printf("create texture 2D failed\n");
        return false;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    if (FAILED(device->CreateDepthStencilView(texture, &descDSV, depthStencilView.GetAddressOf())))
    {
        printf("create depth stencil view failed\n");
        return false;
    }

    texture->Release();
    return true;
}