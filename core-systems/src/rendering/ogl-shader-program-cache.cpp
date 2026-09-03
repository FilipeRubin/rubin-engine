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

void OGLShaderProgramCache::SetUniforms(const OGLShaderKey& key)
{
	if (m_currentProgram == nullptr)
	{
		return;
	}

	using namespace OGLShaderConstants::Uniform;
	const RenderingRuleDescriptor& d = key.GetDescriptor();
	const MeshType& m = key.GetMeshType();
	const OGLRenderParametersState& s = Renderer().RenderParametersState();

	if (d.sceneLighting != nullptr)
	{
		m_currentProgram->SetUniform(LIGHTING_AMBIENT, s.sceneLighting->AmbientLight());
		const FixedArray<DirectionalLight>& dl = s.sceneLighting->DirectionalLights();
		for (size_t i = 0U; i < dl.GetElementCount(); i++)
		{
			std::string directionUniform = std::format("{}[{}].direction",
				LIGHTING_DIRECTIONAL_ARRAY, i
			);
			std::string diffuseUniform = std::format("{}[{}].diffuse",
				LIGHTING_DIRECTIONAL_ARRAY, i
			);

			const Vector3& direction = dl[i].direction;
			const Color& diffuse = dl[i].diffuse * dl[i].intensity;

			m_currentProgram->SetUniform(directionUniform.c_str(), direction);
			m_currentProgram->SetUniform(diffuseUniform.c_str(), diffuse);
		}
	}
	if (not (d.useProjection and d.useViewCamera))
	{
		if (d.useProjection)
		{
			if (m == MeshType::STATIC_2D)
			{
				Matrix3x3 projection = Matrix3x3::ScreenToNDC((Vector2)Renderer().GetViewportSize());
				m_currentProgram->SetUniform(PROJECTION, projection);
			}
			else if (m == MeshType::STATIC_3D)
			{
				const Camera3D& c = s.camera3D->Camera();
				Matrix4x4 projection = Matrix4x4::Perspective(c.aspectRatio, c.vFOV, c.zNear, c.zFar);
				m_currentProgram->SetUniform(PROJECTION, projection);
			}
		}
		else if (d.useViewCamera)
		{
			if (m == MeshType::STATIC_2D)
			{
				Matrix3x3 view = Matrix3x3::Identity();
				m_currentProgram->SetUniform(VIEW, view);
				LOG_WARNING("2D view camera needs to be implemented!");
			}
			else if (m == MeshType::STATIC_3D)
			{
				const Camera3D& c = s.camera3D->Camera();
				Matrix4x4 view = Matrix4x4::View(-c.position, -c.rotation);
				m_currentProgram->SetUniform(VIEW, view);
			}
		}
	}
	else
	{
		if (m == MeshType::STATIC_2D)
		{
			Matrix3x3 projection = Matrix3x3::ScreenToNDC((Vector2)Renderer().GetViewportSize());
			Matrix3x3 view = Matrix3x3::Identity();
			m_currentProgram->SetUniform(PROJECTION_VIEW, projection * view);
			LOG_WARNING("2D view camera needs to be implemented!");
		}
		else if (m == MeshType::STATIC_3D)
		{
			const Camera3D& c = s.camera3D->Camera();
			Matrix4x4 projection = Matrix4x4::Perspective(c.aspectRatio, c.vFOV, c.zNear, c.zFar);
			Matrix4x4 view = Matrix4x4::View(-c.position, -c.rotation);
			m_currentProgram->SetUniform(PROJECTION_VIEW, projection * view);
		}
	}
	if (d.useModelTransform)
	{
		if (m == MeshType::STATIC_2D)
		{
			const Transform2D& t = s.transform2D->Transform();
			Matrix3x3 model = Matrix3x3::Model(t.position, t.rotation, t.scale);
			m_currentProgram->SetUniform(MODEL, model);
		}
		else
		{
			const Transform3D& t = s.transform3D->Transform();
			Matrix4x4 model = Matrix4x4::Model(t.position, t.rotation, t.scale);
			m_currentProgram->SetUniform(MODEL, model);
		}
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
