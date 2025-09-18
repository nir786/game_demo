#version 330 core 
in vec2 TexCoord; 
out vec4 FragColor; 

uniform sampler2D atlas;
//uniform vec4 color ; 


void main(){

 FragColor = texture(atlas ,TexCoord); 
//FragColor = vec4 (0.2 ,0.8 , 0.3 , 1.0); 
}
