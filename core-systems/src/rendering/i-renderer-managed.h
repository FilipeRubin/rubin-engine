#pragma once

class IRendererManaged
{
public:
	virtual ~IRendererManaged() = default;
	virtual void CreateResource() = 0;
	virtual void DestroyResource() = 0;
};
