#pragma once
#include "window-parameters.h"
#include "input/i-basic-input.h"
#include "types/dimensions.h"
#include <functional>

using WindowSizeCallback = std::function<void(const Dimensions& size)>;

class IWindow
{
public:
	virtual ~IWindow() = default;
	virtual void Finalize() = 0;
	virtual void Process() = 0;
	virtual bool ShouldClose() const = 0;
	virtual bool IsInitialized() const = 0;
	virtual bool TryInitialize(const WindowParameters& parameters = {}) = 0;
	virtual IBasicInput& BasicInput() = 0;
	virtual Dimensions GetSize() const = 0;
	virtual float GetAspectRatio() const = 0;
	virtual float GetTime() const = 0;
	virtual void SetTitle(const wchar_t* title) = 0;
	virtual WindowSizeCallback GetWindowSizeCallback() const = 0;
	virtual void SetWindowSizeCallback(WindowSizeCallback windowSizeCallback) = 0;
};
