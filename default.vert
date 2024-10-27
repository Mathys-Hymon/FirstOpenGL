#version 330 core

	// Positions / Coordinates
layout (location = 0) in vec3 aPos;

	// Normal
layout (location = 1) in vec3 aNormal;

	// Colors
layout (location = 2) in vec3 aColor;

	// Texture
layout (location = 3) in vec2 aTex;



	// Outputs thhe current position for the Fragment Shader
out vec3 crntPos;

	// Outputs the Normal for the Fragment Shader
out vec3 Normal;

	// Outputs the color for the Fragment Shader
out vec3 color;

	// Outputs the texture coordinate for the Fragment Shader
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
		// Calculate current Position
	crntPos = vec3(model * vec4(aPos, 1.0f));
		// Assign the normal from the vertex Data
	Normal = aNormal;
	    // Assigns the colors from the Vertex Data
	color = aColor;
		// Assign the texture coordinate from the vertex Data
	texCoord = aTex;
		// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}