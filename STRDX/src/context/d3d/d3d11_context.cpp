#include "d3d11_context.h"
#include "../../window/window.h"

static Window* window = Window::GetSingleton();

D3D11Context* D3D11Context::GetSingleton()
{
	static D3D11Context context;
	return &context;
}
bool D3D11Context::Create(UINT _Width, UINT _Height)
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 2;
    desc.BufferDesc.Width = _Width;
    desc.BufferDesc.Height = _Height;
    desc.BufferDesc.Format = D3D11_FORMAT;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = window->GetHandle();
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;
    desc.SwapEffect = D3D11_SWAP_EFFECT;

    UINT flags = 0;
#if defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel = D3D11_FEATURE_LEVEL;
    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL,
                                             D3D11_DRIVER_TYPE,
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
void D3D11Context::SetViewport(UINT _Width, UINT _Height)
{
    D3D11_VIEWPORT vp;
    ZeroMemory(&vp, sizeof(vp));
    vp.Width = (float)_Width;
    vp.Height = (float)_Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);
}
void D3D11Context::SetPrimitiveTopology(PrimitiveTopology _PrimitiveTopology)
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
void D3D11Context::SetRenderTarget()
{
    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
}
void D3D11Context::UnsetRenderTarget()
{
    deviceContext->OMSetRenderTargets(0, NULL, NULL);
}
void D3D11Context::ClearRenderTarget(float _R, float _G, float _B, float _A)
{
    float clear_color[4] = { _R, _G, _B, _A };
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clear_color);
    deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
bool D3D11Context::ResizeBuffer(UINT _Width, UINT _Height)
{
    UnsetRenderTarget();
    STRDXWRL_RESET(renderTargetView);
    STRDXWRL_RESET(depthStencilView);

    if (FAILED(swapChain->ResizeBuffers(0, _Width, _Height, D3D11_FORMAT, 0)))
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
void D3D11Context::Present(bool _Vsync)
{
    swapChain->Present(_Vsync ? 1 : 0, 0);
}
bool D3D11Context::CheckMultisampleQualityLevels(UINT _SampleCount, UINT* _QualityLevels)
{
    if (!device)
    {
        printf("device is null\n");
        return false;
    }

    if (FAILED(device->CheckMultisampleQualityLevels(D3D11_FORMAT, _SampleCount, _QualityLevels)))
    {
        printf("check multisample quality levels failed\n");
        return false;
    }

    return true;
}
void D3D11Context::Release()
{
    STRDXWRL_RESET(swapChain);
    STRDXWRL_RESET(device);
    STRDXWRL_RESET(deviceContext);
    STRDXWRL_RESET(renderTargetView);
    STRDXWRL_RESET(depthStencilView);

    delete this;
}
bool D3D11Context::CreateRenderTargetView()
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
bool D3D11Context::CreateDepthStencilView(UINT _Width, UINT _Height)
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
        printf("create texture failed\n");
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
bool D3D11Context::SetVertexConstantBuffer(D3D11ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
    if (!_ConstantBuffer)
    {
        printf("vertex constant buffer is null\n");
        return false;
    }

    deviceContext->VSSetConstantBuffers(_Slot, 1, _ConstantBuffer->Get().GetAddressOf());
    return true;
}
bool D3D11Context::SetPixelConstantBuffer(D3D11ConstantBuffer* _ConstantBuffer, UINT _Slot)
{
    if (!_ConstantBuffer)
    {
        printf("pixel constant buffer is null\n");
        return false;
    }

    deviceContext->PSSetConstantBuffers(_Slot, 1, _ConstantBuffer->Get().GetAddressOf());
    return true;
}
bool D3D11Context::SetVertexShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot)
{
    if (!_ShaderResource)
    {
        printf("vertex shader resource is null\n");
        return false;
    }

    deviceContext->VSSetShaderResources(_Slot, 1, &_ShaderResource);
    return true;
}
bool D3D11Context::SetPixelShaderResource(ID3D11ShaderResourceView* _ShaderResource, UINT _Slot)
{
    if (!_ShaderResource)
    {
        printf("pixel shader resource is null\n");
        return false;
    }

    deviceContext->PSSetShaderResources(_Slot, 1, &_ShaderResource);
    return true;
}
bool D3D11Context::SetVertexSampler(D3D11SamplerState* _SamplerState, UINT _Slot)
{
    if (!_SamplerState)
    {
        printf("vertex sampler state is null\n");
        return false;
    }

    deviceContext->VSSetSamplers(_Slot, 1, _SamplerState->Get().GetAddressOf());
    return true;
}
bool D3D11Context::SetPixelSampler(D3D11SamplerState* _SamplerState, UINT _Slot)
{
    if (!_SamplerState)
    {
        printf("vertex sampler state is null\n");
        return false;
    }

    deviceContext->PSSetSamplers(_Slot, 1, _SamplerState->Get().GetAddressOf());
    return true;
}
void D3D11Context::ReleaseVertexShaderResources(UINT _Slot)
{
    ID3D11ShaderResourceView* shaderResourceView = NULL;
    deviceContext->VSSetShaderResources(_Slot, 1, &shaderResourceView);
}
void D3D11Context::ReleasePixelShaderResources(UINT _Slot)
{
    ID3D11ShaderResourceView* shaderResourceView = NULL;
    deviceContext->PSSetShaderResources(_Slot, 1, &shaderResourceView);
}
bool D3D11Context::UpdateIndexBuffer(D3D11Shader* _Shader)
{
    // error check
    if (!_Shader)
    {
        printf("shader is null\n");
        return false;
    }
    else if (_Shader->GetIndices().empty())
    {
        printf("indices data is empty\n");
        return false;
    }
    else if (!_Shader->GetIndexBuffer())
    {
        printf("index buffer is null\n");
        return false;
    }

    D3D11_MAPPED_SUBRESOURCE resource;
    if (FAILED(deviceContext->Map(_Shader->GetIndexBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
        return false;

    memcpy(resource.pData, _Shader->GetIndices().data(), (sizeof(UINT) * (UINT)_Shader->GetIndices().size()));
    deviceContext->Unmap(_Shader->GetIndexBuffer().Get(), 0);

    _Shader->SetIndicesSize((UINT)_Shader->GetIndices().size());
    _Shader->ClearIndices();
    return true;
}
bool D3D11Context::Draw(D3D11Shader* _Shader)
{
    // error check
    if (!_Shader)
    {
        printf("shader is null\n");
        return false;
    }
    else if (!_Shader->GetVertexShader())
    {
        printf("vertex shader is null\n");
        return false;
    }
    else if (!_Shader->GetPixelShader())
    {
        printf("pixel shader is null\n");
        return false;
    }

    if (_Shader->GetIndexBuffer()) deviceContext->DrawIndexed(_Shader->GetIndicesSize(), 0, 0);
    else deviceContext->Draw(_Shader->GetVerticesSize(), 0);

    return true;
}
bool D3D11Context::Set(D3D11Shader* _Shader)
{
    // error check
    if (!_Shader)
    {
        printf("shader is null\n");
        return false;
    }
    else if (!_Shader->GetVertexLayout())
    {
        printf("vertex layout is null\n");
        return false;
    }
    else if (!_Shader->GetVertexBuffer())
    {
        printf("vertex buffer is null\n");
        return false;
    }
    else if (!_Shader->GetVertexShader())
    {
        printf("vertex shader is null\n");
        return false;
    }
    else if (!_Shader->GetPixelShader())
    {
        printf("pixel shader is null\n");
        return false;
    }

    deviceContext->IASetInputLayout(_Shader->GetVertexLayout().Get());

    UINT stride = _Shader->GetSizeOf();
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, _Shader->GetVertexBuffer().GetAddressOf(), &stride, &offset);

    if (_Shader->GetIndexBuffer())
        D3D11Context::GetSingleton()->GetDeviceContext()->IASetIndexBuffer(_Shader->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

    deviceContext->VSSetShader(_Shader->GetVertexShader().Get(), NULL, 0);
    deviceContext->PSSetShader(_Shader->GetPixelShader().Get(), NULL, 0);

    return true;
}