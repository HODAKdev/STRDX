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

private:
    float iTime;
    DirectX::XMFLOAT2 iResolution;

    // matrix
    DirectX::XMMATRIX iWorld;
    DirectX::XMMATRIX iView;
    DirectX::XMMATRIX iProjection;

public:
    void SetTime(float _Time)
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
    void Set(const float _Time,
             const float _Width,
             const float _Height,
             const float _Fov = 0.0f,
             const float _NearZ = 0.0f,
             const float _FarZ = 0.0f,
             const DirectX::XMFLOAT3& _Eye = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
             const DirectX::XMFLOAT3& _At = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
             const DirectX::XMFLOAT3& _Pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
             const DirectX::XMFLOAT3& _Rot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
             const DirectX::XMFLOAT3& _Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f))
    {
        iTime = _Time;
        iResolution = DirectX::XMFLOAT2(_Width, _Height);
        iWorld = DirectX::XMMatrixTranslation(_Pos.x, _Pos.y, _Pos.z) * DirectX::XMMatrixRotationRollPitchYaw(_Rot.x, _Rot.y, _Rot.z) * DirectX::XMMatrixScaling(_Scale.x, _Scale.y, _Scale.z);
        DirectX::XMVECTOR Eye = DirectX::XMVectorSet(_Eye.x, _Eye.y, _Eye.z, 0.0f);
        DirectX::XMVECTOR At = DirectX::XMVectorSet(_At.x, _At.y, _At.z, 0.0f);
        DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        iView = DirectX::XMMatrixLookAtLH(Eye, At, Up);
        iProjection = DirectX::XMMatrixPerspectiveFovLH(_Fov, _Width / _Height, _NearZ, _FarZ);
        iProjection = DirectX::XMMatrixTranspose(iProjection);
        iView = DirectX::XMMatrixTranspose(iView);
        iWorld = DirectX::XMMatrixTranspose(iWorld);
    }
};
