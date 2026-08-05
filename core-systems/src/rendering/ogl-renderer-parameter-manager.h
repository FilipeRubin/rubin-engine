#pragma once
#include "resources/ogl-rendering-rule.h"
#include "ogl-renderer-user.h"
#include <rendering/i-renderer-parameter-manager.h>
#include <list>
#include <memory>
#include <utility>

class OGLRendererParameterManager final : public IRendererParameterManager, public OGLRendererUser
{
public:
	OGLRendererParameterManager(OGLRenderer& renderer);
	ICamera3DParameter* CreateCamera3D() override;
	IDirectionalLightParameter* CreateDirectionalLight() override;
	ITransform3DParameter* CreateTransform3D() override;
private:
	std::list<std::unique_ptr<IRenderParameter>> m_parameters;
	template<typename T, typename... Args>
	inline T* CreateParameter(Args&&... args)
	{
		std::unique_ptr<T> parameter = std::make_unique<T>(GetRenderer(), std::forward<Args>(args)...);
		T* result = static_cast<T*>(parameter.get());
		m_parameters.emplace_back(std::move(parameter));
		return result;
	}
};
