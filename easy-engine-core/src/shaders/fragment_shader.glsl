#version 450 

in vec2 frag_textureCoords;
in vec3 frag_vertexPosition_modelspace;
in vec3 frag_vertexNormal_modelspace;

uniform mat4 model;

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

layout (std140) uniform Lights { 
	PointLight point_lights[MAX_POINT_LIGHTS];
};

uniform float point_light_count;

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
    vec4 ambientComponent  = vec4(light.ambient_color, 1)  * diffuseColor;
    vec4 diffuseComponent  = vec4(light.diffuse_color, 1)  * diff * diffuseColor;
    vec4 specularComponent = vec4(light.specular_color, 1) * spec * vec4(materialSpecularColor, 1);

    ambientComponent  *= attenuation * light.strength;
    diffuseComponent  *= attenuation * light.strength;
    specularComponent *= attenuation * light.strength;
    return diffuseComponent;
}

void main() {
    mat3 normalMatrix      = transpose(inverse(mat3(model)));
    vec3 normal_worldspace = normalize(normalMatrix * frag_vertexNormal_modelspace);
	vec3 cameraDirection   = normalize(cameraPosition_worldspace - normal_worldspace);
    
    vec3 frag_vertexPosition_worldspace = vec3(model * vec4(frag_vertexPosition_modelspace, 1));

	vec4 emissiveColor = hasEmissiveTexture == 1 ? texture(emissiveTextureSampler2D, frag_textureCoords) : vec4(materialEmmisiveColor, 1);

    outputColor += emissiveColor;

	// Do point light calculations for each point light
	for(int i = 0; i < point_light_count; i++) {
		outputColor += CalculatePointLight(point_lights[i], normal_worldspace, frag_vertexPosition_worldspace, cameraDirection);
	}
}