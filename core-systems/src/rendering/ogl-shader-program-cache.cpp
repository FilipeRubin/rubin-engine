#include "ogl-shader-program-cache.h"
#include "ogl-shader-program.h"
#include "ogl-shader-constants.h"
#include "ogl-shader-source-builder.h"
#include <rendering/ogl-renderer.h>
#include <math/matrix4x4.h>
#include <logging/log-macros.h>
#include <ogl.h>
#include <format>

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
	if (m_currentProgram == nullptr)
	{
		return;
	}

	using namespace OGLShaderConstants::Uniform;
	const RenderingRuleDescriptor& d = renderingRule.GetDescriptor();
	const OGLRenderParametersState& s = Renderer().RenderParametersState();

	if (d.sceneLighting != nullptr)
	{
		m_currentProgram->SetUniform(LIGHTING_AMBIENT, s.sceneLighting->AmbientLight());
		const FixedArray<DirectionalLight>& dl = s.sceneLighting->DirectionalLights();
		for (size_t i = 0U; i < dl.GetElementCount(); i++)
		{
			std::string direction = std::format(
				"{}[{}].direction",
				LIGHTING_DIRECTIONAL_ARRAY,
				i
			);
			std::string diffuse = std::format(
				"{}[{}].diffuse",
				LIGHTING_DIRECTIONAL_ARRAY,
				i
			);
			m_currentProgram->SetUniform(direction.c_str(), dl[i].direction);
			m_currentProgram->SetUniform(diffuse.c_str(), dl[i].diffuse * dl[i].intensity);
		}
	}
	if (d.useProjectionView)
	{
		const Camera3D& c = s.camera->Camera();
		Matrix4x4 projection = Matrix4x4::Perspective(c.aspectRatio, c.vFOV, c.zNear, c.zFar);
		Matrix4x4 view = Matrix4x4::View(-c.position, -c.rotation);
		Matrix4x4 projectionView = projection * view;
		m_currentProgram->SetUniform(PROJECTION_VIEW, projectionView);
	}
	if (d.useModelMatrix)
	{
		const Transform3D& t = s.transform->Transform();
		Matrix4x4 model = Matrix4x4::Model(t.position, t.rotation, t.scale);
		m_currentProgram->SetUniform(MODEL, model);
	}
}

OGLShaderProgram* OGLShaderProgramCache::CreateProgram(const OGLShaderKey& key)
{
	OGLShaderProgram* program = new OGLShaderProgram();
	OGLShaderSourceBuilder builder = OGLShaderSourceBuilder(key);
	std::string vss = builder.GenerateVertexSource();
	std::string fss = builder.GenerateFragmentSource();

	if (program->TryCompile(vss.c_str(), fss.c_str()))
	{
		LOG_DEBUG("OpenGL shader program compiled and linked.");
		return program;
	}
	delete program;
	return nullptr;
}
