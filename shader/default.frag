#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float TexIndex;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, vec2( (TexCoord.x + TexIndex) / 6.0f, TexCoord.y));	
}