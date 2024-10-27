#version 330 core

	// Outputs colors in RGBA
out vec4 FragColor;



	// Import the current Position from the Vertex Shader
in vec3 crntPos;

	//Import the Normal from the Vertex Shader
in vec3 Normal;

	// Import the color from the Vertex Shader
in vec3 color;
	
	// Import the texture coordinate from the Vertex Shader
in vec2 texCoord;


uniform sampler2D diffuse0;                 // Get texture  Unit from the main
uniform sampler2D specular0;                 // Get specular Unit from the main
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

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}




vec4 direcLight()
{
	float ambient = 0.2f;                //ambient light intensity


	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));      // Vector should point in the opposit direction
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;   
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}




vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	

	float ambient = 0.2f;                //ambient light intensity

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);


	// specular lightning
	float specularLight = 0.5f;   
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}


void main()
{
	FragColor = spotLight();     //apply light depanding of the normal
}