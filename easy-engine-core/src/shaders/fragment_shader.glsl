#version 450 

in vec2 frag_textureCoords;
in vec3 frag_vertexPosition_modelspace;
in vec3 frag_vertexNormal_modelspace;

uniform mat4 model;

uniform vec3 lightPosition_worldspace;
uniform vec3 lightColor;
uniform float lightPower;

uniform vec3 cameraPosition_worldspace;

uniform vec3 materialSpecularColor;
uniform float materialShininess;

uniform sampler2D textureSampler2D;

out vec4 outputColor;

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * frag_vertexNormal_modelspace);

	vec4 materialDiffuseColor = texture(textureSampler2D, frag_textureCoords);
    
    vec3 frag_vertexPosition_worldspace = vec3(model * vec4(frag_vertexPosition_modelspace, 1));
    
    vec3 surfaceToLightVector_worldspace = lightPosition_worldspace - frag_vertexPosition_worldspace;
	float distance = length(surfaceToLightVector_worldspace);

	float lightFalloff = distance * distance;

	// DIFFUSE
    float brightness = dot(normal, surfaceToLightVector_worldspace) / length(surfaceToLightVector_worldspace);
	// light bouncing on the back of a surface is negative, limit value to a min value of 0 (completely dark)
    vec4 diffuseComponent = clamp(brightness, 0, 1) * vec4(lightColor, 1) * materialDiffuseColor;

	// SPECULAR
	vec3 reflectionVector = normalize(reflect(lightPosition_worldspace, normal));
	vec3 surfaceToCamera = normalize(lightPosition_worldspace - frag_vertexPosition_modelspace);
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, materialShininess);
	vec3 specularComponent = vec3(0, 0, 0);
	if (specularCoefficient > 0) {
 		specularComponent = specularCoefficient * materialSpecularColor * lightColor;
	}
	// light falloff factor is distance^2, where distance is the distance between the vertex and the light
	outputColor = ((diffuseComponent + vec4(specularComponent, 1)) * lightPower) / lightFalloff;
}