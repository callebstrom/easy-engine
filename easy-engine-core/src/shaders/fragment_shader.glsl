#version 450 

smooth in vec3 frag_color;
in vec3 frag_vertexPosition_modelspace;
in vec3 frag_vertexNormal_modelspace;

out vec4 outputColor;
uniform mat4 model;
uniform vec3 lightColor;
uniform vec3 lightPosition_worldspace;

void main() {

	vec3 materialColor = vec3(0.8f, 0.2f, 0.0f);

	 //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * frag_vertexNormal_modelspace);
    
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 frag_vertexPosition_worldspace = vec3(model * vec4(frag_vertexPosition_modelspace, 1));
    
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLightVector_worldspace = lightPosition_worldspace - frag_vertexPosition_worldspace;

    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLightVector_worldspace) / (length(surfaceToLightVector_worldspace) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)

	outputColor = vec4(brightness * lightColor * materialColor, 1.0);
}