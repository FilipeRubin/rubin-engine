static const char* lambertVertexShaderSource = R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;

out vec2 v_out_uv;
out vec3 v_out_nor;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(v_in_pos, 1.0);
	v_out_uv = v_in_uv;
	v_out_nor = mat3(transpose(inverse(u_model))) * v_in_nor;
}
)";

static const char* lambertFragmentShaderSource = R"(
#version 460 core

in vec2 v_out_uv;
in vec3 v_out_nor;

out vec4 f_color;

uniform sampler2D u_texture;
uniform vec4 u_ambientLight;
uniform vec4 u_directionalLightDiffuse;
uniform vec3 u_directionalLightDirection;

void main()
{
	float directionalLightAmount = max(dot(normalize(v_out_nor), normalize(-u_directionalLightDirection)), 0.0);
	vec3 directionalLightColor = u_directionalLightDiffuse.rgb * directionalLightAmount;
	vec3 lightColor = u_ambientLight.rgb + directionalLightColor;
	f_color = texture(u_texture, v_out_uv) * vec4(lightColor, 1.0);
}
)";
