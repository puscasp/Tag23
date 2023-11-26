#version 330 core

layout (location = 0) vec2 inputPos;
layout (location = 1) vec4 inputColor

out vec4 vertexColor; // specify a color output to the fragment shader
void main()
{
gl_Position =  vec4(inputPos, 1.0, 1.0); // we give a vec3 to vec4’s constructor
vertexColor = inputColor; // output variable to dark-red
}