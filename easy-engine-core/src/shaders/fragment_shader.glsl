#version 450 

in vec2 frag_textureCoords;
in vec3 frag_vertexPosition_modelspace;
in vec3 frag_vertexNormal_modelspace;

uniform mat4 model;

uniform vec3 lightPosition_worldspace;
uniform vec3 lightColor;
uniform float lightPower;

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

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * frag_vertexNormal_modelspace);

	vec4 diffuseColor = hasDiffuseTexture == 1 ? texture(diffuseTextureSampler2D, frag_textureCoords) : vec4(materialDiffuseColor, 1);
    
    vec3 frag_vertexPosition_worldspace = vec3(model * vec4(frag_vertexPosition_modelspace, 1));
    
    vec3 surfaceToLightVector_worldspace = lightPosition_worldspace - frag_vertexPosition_worldspace;
	float distance = length(surfaceToLightVector_worldspace);

	float lightFalloff = distance * distance;

	// DIFFUSE
    float brightness = dot(normal, surfaceToLightVector_worldspace) / length(surfaceToLightVector_worldspace);
	// light bouncing on the back of a surface is negative, limit value to a min value of 0 (completely dark)
    vec4 diffuseComponent = clamp(brightness, 0, 1) * vec4(lightColor, 1) * diffuseColor;

	// SPECULAR
	vec3 reflectionVector = normalize(reflect(lightPosition_worldspace, normal));
	vec3 surfaceToCamera = normalize(lightPosition_worldspace - frag_vertexPosition_modelspace);
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, materialShininess);
	vec3 specularComponent = vec3(0, 0, 0);
	if (specularCoefficient > 0) {
 		specularComponent = specularCoefficient * materialSpecularColor * lightColor;
	}

	// EMISSIVE
	vec4 emissiveColor = hasEmissiveTexture == 1 ? texture(emissiveTextureSampler2D, frag_textureCoords) : vec4(materialEmmisiveColor, 1);

	if (hasEmissiveTexture == 1 && emissiveColor.r == 0 && emissiveColor.g == 0 && emissiveColor.b == 0) {
		emissiveColor.a = 0;
	}

	vec4 outputColor_ = ((diffuseComponent + vec4(specularComponent, 1)) * lightPower) / lightFalloff;
	outputColor_.a = diffuseComponent.a;

	outputColor = outputColor_;
}