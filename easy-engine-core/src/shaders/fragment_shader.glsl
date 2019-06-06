#version 450 

smooth in vec3 frag_color;
in vec3 frag_vertexPosition_modelspace;
in vec3 frag_vertexNormal_modelspace;

uniform mat4 model;
uniform vec3 lightPosition_worldspace;

uniform vec3 lightColor;
uniform float lightPower;

out vec4 outputColor;

void main() {

	// TODO these 2 should be uniforms
	vec3 materialColor = vec3(1.f, 1.f, 1.f);
	vec3 materialSpecularColor = vec3(1.f, 1.f, 1.f);

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * frag_vertexNormal_modelspace);
    
    vec3 frag_vertexPosition_worldspace = vec3(model * vec4(frag_vertexPosition_modelspace, 1));
    
    vec3 surfaceToLightVector_worldspace = lightPosition_worldspace - frag_vertexPosition_worldspace;
	float distance = length(surfaceToLightVector_worldspace);

	float lightFalloff = distance * distance;

	// DIFFUSE
    // calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLightVector_worldspace) / (length(surfaceToLightVector_worldspace) * length(normal));
	// light bouncing on the back of a surface is negative, limit value to a min value of 0 (completely dark)
    vec3 diffuseComponent = clamp(brightness, 0, 1) * lightColor * lightPower * materialColor;

	// SPECULAR
	float materialShininess = 0.01;
	vec3 incidenceVector = -surfaceToLightVector_worldspace; 
	vec3 reflectionVector = reflect(incidenceVector, normal);
	vec3 surfaceToCamera = normalize(lightPosition_worldspace - frag_vertexPosition_modelspace); // TODO replace lightPosition_worldspace with camera position
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	float specularCoefficient = pow(cosAngle, materialShininess);

	vec3 specularComponent = specularCoefficient * materialSpecularColor * lightColor * lightPower * brightness;

	// light falloff factor is distance^2, where distance is the distance between the vertex and the light
	outputColor = vec4(((specularComponent + diffuseComponent)) / lightFalloff, 1.0);
}