#pragma once

#include <DirectXMath.h>

struct CB
{
public:
    CB() : iTime(0.0f),
           iResolution(DirectX::XMFLOAT2(0.0f, 0.0f)),
           iWorld(DirectX::XMMatrixIdentity()),
           iView(DirectX::XMMatrixIdentity()),
           iProjection(DirectX::XMMatrixIdentity()) {}

private:
    float iTime;
    DirectX::XMFLOAT2 iResolution;
    DirectX::XMMATRIX iWorld;
    DirectX::XMMATRIX iView;
    DirectX::XMMATRIX iProjection;

public:
    void SetTime(float _Time)
    {
        iTime = _Time;
    }
    void SetResolution(float _Width, float _Height)
    {
        iResolution = DirectX::XMFLOAT2(_Width, _Height);
    }
    void SetWorld(const DirectX::XMMATRIX& _World)
    {
        iWorld = _World;
    }
    void SetView(const DirectX::XMMATRIX& _View)
    {
        iView = _View;
    }
    void SetProjection(const DirectX::XMMATRIX& _Projection)
    {
        iProjection = _Projection;
    }
    void SetMatrix(float _Width,
                   float _Height,
                   float _Fov,
                   float _NearZ,
                   float _FarZ,
                   const DirectX::XMFLOAT3& _Eye,
                   const DirectX::XMFLOAT3& _At,
                   const DirectX::XMFLOAT3& _Position,
                   const DirectX::XMFLOAT3& _Rotation,
                   const DirectX::XMFLOAT3& _Scale)
    {
        iWorld = DirectX::XMMatrixTranslation(_Position.x, _Position.y, _Position.z) * DirectX::XMMatrixRotationRollPitchYaw(_Rotation.x, _Rotation.y, _Rotation.z) * DirectX::XMMatrixScaling(_Scale.x, _Scale.y, _Scale.z);

        DirectX::XMVECTOR Eye = DirectX::XMVectorSet(_Eye.x, _Eye.y, _Eye.z, 0.0f);
        DirectX::XMVECTOR At = DirectX::XMVectorSet(_At.x, _At.y, _At.z, 0.0f);
        DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        iView = DirectX::XMMatrixLookAtLH(Eye, At, Up);

        iProjection = DirectX::XMMatrixPerspectiveFovLH(_Fov, _Width / _Height, _NearZ, _FarZ);

        iWorld = DirectX::XMMatrixTranspose(iWorld);
        iView = DirectX::XMMatrixTranspose(iView);
        iProjection = DirectX::XMMatrixTranspose(iProjection);
    }
};
