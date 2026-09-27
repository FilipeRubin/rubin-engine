#pragma once

class IRendererResource
{
public:
	virtual ~IRendererResource() = default;
	virtual void Destroy() = 0;
	virtual bool IsValid() const = 0;
};
