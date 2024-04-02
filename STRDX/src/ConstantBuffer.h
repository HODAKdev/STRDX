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

public:
    float iTime;
    DirectX::XMFLOAT2 iResolution;

    // matrix
    DirectX::XMMATRIX iWorld;
    DirectX::XMMATRIX iView;
    DirectX::XMMATRIX iProjection;
};