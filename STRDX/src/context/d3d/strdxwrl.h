#pragma once

#include <wrl/client.h>

template<typename T>
using STRDXWRL = Microsoft::WRL::ComPtr<T>;

#define STRDXWRL_RESET(wrl) if (wrl) { wrl.Reset(); }
#define STRDXWRL_RELEASE(wrl) if (wrl) { wrl->Release(); }