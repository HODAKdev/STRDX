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
    void SetResolution(const float _Width, const float _Height)
    {
        iResolution = DirectX::XMFLOAT2(_Width, _Height);
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
    void SetMatrix(const float _Width,
                   const float _Height,
                   const float _Fov,
                   const float _NearZ,
                   const float _FarZ,
                   const DirectX::XMFLOAT3& _Eye,
                   const DirectX::XMFLOAT3& _At,
                   const DirectX::XMFLOAT3& _Pos,
                   const DirectX::XMFLOAT3& _Rot,
                   const DirectX::XMFLOAT3& _Scale)
    {
        iWorld = DirectX::XMMatrixTranslation(_Pos.x, _Pos.y, _Pos.z) * DirectX::XMMatrixRotationRollPitchYaw(_Rot.x, _Rot.y, _Rot.z) * DirectX::XMMatrixScaling(_Scale.x, _Scale.y, _Scale.z);

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
