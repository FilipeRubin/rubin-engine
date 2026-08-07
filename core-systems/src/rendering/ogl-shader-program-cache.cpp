#include "ogl-shader-program-cache.h"
#include "ogl-shader-program.h"
#include "ogl-shader-constants.h"
#include <rendering/ogl-renderer.h>
#include <math/matrix4x4.h>
#include <logging/log-macros.h>
#include <ogl.h>

OGLShaderProgramCache::OGLShaderProgramCache(OGLRenderer& renderer) :
	OGLRendererUser(renderer),
	m_currentProgram(nullptr)
{}

OGLShaderProgramCache::~OGLShaderProgramCache()
{
	for (const std::pair<const OGLShaderKey, OGLShaderProgram*>& entry : m_cache)
	{
		entry.second->Delete();
		delete entry.second;
	}

	m_cache.clear();
}

void OGLShaderProgramCache::BindOrCreate(const OGLRenderingRule& renderingRule, MeshType meshType)
{
	RenderingRuleDescriptor descriptor = renderingRule.GetDescriptor();
	OGLShaderKey key = OGLShaderKey(descriptor, meshType);
	std::unordered_map<OGLShaderKey, OGLShaderProgram*, OGLShaderKey::Hash>::iterator it = m_cache.find(key);

	if (it != m_cache.end())
	{
		it->second->Use();
		m_currentProgram = it->second;
		return;
	}

	OGLShaderProgram* program = CreateProgram(key);
	if (program != nullptr)
	{
		m_cache.emplace(key, program);
		program->Use();
		m_currentProgram = program;
	}
}

void OGLShaderProgramCache::SetUniforms(const OGLRenderingRule& renderingRule)
{
	using namespace OGLShaderConstants;
	const RenderingRuleDescriptor& d = renderingRule.GetDescriptor();
	const OGLRenderParametersState& s = GetRenderer().RenderParametersState();

	if (d.useDirectionalLight)
	{
		const DirectionalLight& dl = s.directionalLight->Light();
		m_currentProgram->SetUniform(DIR_LIGHT_AMBIENT, dl.ambient);
		m_currentProgram->SetUniform(DIR_LIGHT_DIFFUSE, dl.diffuse);
		m_currentProgram->SetUniform(DIR_LIGHT_DIRECTION, dl.direction);
	}
	if (d.useCamera3D)
	{
		const Camera3D& c = s.camera->Camera();
		Matrix4x4 view = Matrix4x4::View(-c.position, -c.rotation);
		Matrix4x4 projection = Matrix4x4::Perspective(c.aspectRatio, c.vFOV, c.zNear, c.zFar);
		m_currentProgram->SetUniform(VIEW, view);
		m_currentProgram->SetUniform(PROJECTION, projection);
	}
	if (d.useTransform3D)
	{
		const Transform3D& t = s.transform->Transform();
		Matrix4x4 model = Matrix4x4::Model(t.position, t.rotation, t.scale);
		m_currentProgram->SetUniform(MODEL, model);
	}
}

OGLShaderProgram* OGLShaderProgramCache::CreateProgram(const OGLShaderKey& key)
{
	LOG_WARNING("Implement custom shaders.");
	OGLShaderProgram* program = new OGLShaderProgram();
#include <data/unshaded-shader.h>
#include <data/lambert-shader.h>

	const char*& vss =
		key.GetDescriptor().useDirectionalLight ?
		lambertVertexShaderSource :
		unshadedVertexShaderSource;
	const char*& fss =
		key.GetDescriptor().useDirectionalLight ?
		lambertFragmentShaderSource :
		unshadedFragmentShaderSource;

	if (program->TryCompile(vss, fss))
	{
		LOG_DEBUG("OpenGL shader program compiled and linked.");
		return program;
	}
	return nullptr;
}
