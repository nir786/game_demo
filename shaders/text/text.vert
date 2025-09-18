#version 330 core

layout (location = 0 ) in vec2 aPos; 
layout (location = 1 ) in vec2 aUVs; 

out vec2 TexCoords; 
uniform mat4 projection ; 
uniform mat4 view; 

void main(){

TexCoords = aUVs ; 
gl_Position = projection * view * vec4(aPos ,0.0 ,1.0 ); 

}
