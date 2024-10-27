#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;

// Inputs the texture coordinate from the Vertex Shader
in vec2 texCoord;

in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;                 // Get texture  Unit from the main
uniform sampler2D tex1;                 // Get specular Unit from the main
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 1.0f;
	float b = 0.04f;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);


	float ambient = 0.2f;                //ambient light intensity


	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;   
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse * intensity + ambient) + texture(tex1, texCoord).r * specular * intensity) * lightColor;
}


void main()
{
	FragColor = pointLight();     //apply light depanding of the normal
}