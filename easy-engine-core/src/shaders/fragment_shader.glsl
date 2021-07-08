#version 450

in vec2 frag_textureCoords;
in vec3 frag_vertexPosition_modelspace;
in vec3 frag_vertexNormal_modelspace;

uniform mat4 model;

struct DirectionalLight {
	vec3 direction;

	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;

	float strength;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;

	float strength;
};

#define MAX_POINT_LIGHTS 128
#define MAX_DIRECTIONAL_LIGHTS 4

layout(std140) uniform Lights{
	PointLight point_lights[MAX_POINT_LIGHTS];
	DirectionalLight directional_lights[MAX_DIRECTIONAL_LIGHTS];
};

uniform float point_light_count;
uniform float directional_light_count;

uniform vec3 cameraPosition_worldspace;

uniform vec3 materialDiffuseColor;
uniform vec3 materialSpecularColor;
uniform vec3 materialEmmisiveColor;
uniform float materialShininess;
uniform float hasDiffuseTexture;
uniform float hasEmissiveTexture;

uniform sampler2D diffuseTextureSampler2D;
uniform sampler2D emissiveTextureSampler2D;

out vec4 outputColor;

vec4 CalculatePointLight(PointLight light, vec3 normal_worldspace, vec3 frag_vertexPosition_worldspace, vec3 cameraDirection) {

	vec4 diffuseColor = hasDiffuseTexture == 1 ? texture(diffuseTextureSampler2D, frag_textureCoords) : vec4(materialDiffuseColor, 1);

	vec3 lightDirection = normalize(light.position - frag_vertexPosition_worldspace);

	// diffuse shading
	float diff = max(dot(normal_worldspace, lightDirection), 0.0);

	// specular shading
	vec3 reflectionDirection = reflect(-lightDirection, normal_worldspace);
	float spec = pow(max(dot(cameraDirection, reflectionDirection), 0.0), materialShininess);

	// attenuation
	float distance = length(light.position - frag_vertexPosition_worldspace);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine results
	vec4 ambientComponent = vec4(light.diffuse_color, 1) * diffuseColor;
	vec4 diffuseComponent = vec4(light.diffuse_color, 1) * diff * diffuseColor;
	vec4 specularComponent = vec4(light.specular_color, 1) * spec * vec4(materialSpecularColor, 1);

	return (ambientComponent + diffuseComponent + specularComponent) * light.strength * attenuation;
}

vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal_worldspace) {
	return vec4(clamp(dot(normal_worldspace, light.direction), 0, 1) * light.diffuse_color, 1);
	// return vec4(1);
}

void main() {
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 normal_worldspace = normalize(normalMatrix * frag_vertexNormal_modelspace);
	vec3 cameraDirection_worldspace = normalize(cameraPosition_worldspace - normal_worldspace);

	vec3 frag_vertexPosition_worldspace = vec3(model * vec4(frag_vertexPosition_modelspace, 1));

	vec4 emissiveColor = hasEmissiveTexture == 1 ? texture(emissiveTextureSampler2D, frag_textureCoords) : vec4(materialEmmisiveColor, 1);

	outputColor += emissiveColor;

	// Apply directional lights
	for (int i = 0; i < directional_light_count; i++) {
		outputColor += CalculateDirectionalLight(directional_lights[i],  normal_worldspace);
	}

	// Do point light calculations for each point light
	for (int i = 0; i < point_light_count; i++) {
		PointLight point_light = point_lights[i];
		point_light.constant = 1; // TODO bug when uploading constant causing min-max values
		outputColor += CalculatePointLight(point_light, normal_worldspace, frag_vertexPosition_worldspace, cameraDirection_worldspace);
	}
}