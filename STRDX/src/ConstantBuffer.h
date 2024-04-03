#pragma once

#include <DirectXMath.h>

struct ConstantBuffer
{
public:
    ConstantBuffer() : iTime(0.0f),
                       iResolution(DirectX::XMFLOAT2(0, 0)),
                       iWorld(DirectX::XMMatrixIdentity()),
                       iView(DirectX::XMMatrixIdentity()),
                       iProjection(DirectX::XMMatrixIdentity()) {}

public: // private for later
    float iTime;
    DirectX::XMFLOAT2 iResolution;

    // matrix
    DirectX::XMMATRIX iWorld;
    DirectX::XMMATRIX iView;
    DirectX::XMMATRIX iProjection;

public:
    void SetTime(const float _Time)
    {
        iTime = _Time;
    }
    float GetTime()
    {
        return iTime;
    }
    void SetResolution(const DirectX::XMFLOAT2& _Resolution)
    {
        iResolution = _Resolution;
    }
    DirectX::XMFLOAT2 GetResolution()
    {
        return iResolution;
    }
    void SetWorld(const DirectX::XMMATRIX& _World)
    {
        iWorld = _World;
    }
    DirectX::XMMATRIX GetWorld()
    {
        return iWorld;
    }
    void SetView(const DirectX::XMMATRIX& _View)
    {
        iView = _View;
    }
    DirectX::XMMATRIX GetView()
    {
        return iView;
    }
    void SetProjection(const DirectX::XMMATRIX& _Projection)
    {
        iProjection = _Projection;
    }
    DirectX::XMMATRIX GetProjection()
    {
        return iProjection;
    }
};
