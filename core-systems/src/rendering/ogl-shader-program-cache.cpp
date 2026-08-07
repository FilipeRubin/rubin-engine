#include "ogl-shader-program-cache.h"
#include "ogl-shader-program.h"
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
	const RenderingRuleDescriptor& d = renderingRule.GetDescriptor();
	const OGLRenderParametersState& s = GetRenderer().RenderParametersState();

	if (d.useDirectionalLight)
	{
		const DirectionalLight& dl = s.directionalLight->Light();

		GLint location;
		location = glGetUniformLocation(m_currentProgram->GetProgram(), "u_ambientLight");
		glUniform4fv(location, 1, reinterpret_cast<const GLfloat*>(&dl.ambient));
		location = glGetUniformLocation(m_currentProgram->GetProgram(), "u_directionalLightDiffuse");
		glUniform4fv(location, 1, reinterpret_cast<const GLfloat*>(&dl.diffuse));
		location = glGetUniformLocation(m_currentProgram->GetProgram(), "u_directionalLightDirection");
		glUniform3fv(location, 1, reinterpret_cast<const GLfloat*>(&dl.direction));
	}
	if (d.useCamera3D)
	{
		const Camera3D& c = s.camera->Camera();

		Matrix4x4 view = (
			Matrix4x4::RotationX(-c.rotation.x) *
			Matrix4x4::RotationY(-c.rotation.y) *
			Matrix4x4::RotationZ(-c.rotation.z) *
			Matrix4x4::Translation(-c.position)
			);
		Matrix4x4 projection = Matrix4x4::Perspective(
			c.aspectRatio,
			c.vFOV,
			c.zNear,
			c.zFar
		);

		GLint location;
		location = glGetUniformLocation(m_currentProgram->GetProgram(), "u_view");
		glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&view));
		location = glGetUniformLocation(m_currentProgram->GetProgram(), "u_projection");
		glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&projection));
	}
	if (d.useTransform3D)
	{
		const Transform3D& t = s.transform->Transform();

		Matrix4x4 model = (
			Matrix4x4::Translation(t.position) *
			Matrix4x4::RotationZ(t.rotation.z) *
			Matrix4x4::RotationY(t.rotation.y) *
			Matrix4x4::RotationX(t.rotation.x) *
			Matrix4x4::Scaling(t.scale)
			);

		GLint location;
		location = glGetUniformLocation(m_currentProgram->GetProgram(), "u_model");
		glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&model));
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
	LOG_ERROR("Failed to create shader program.");
	return nullptr;
}
