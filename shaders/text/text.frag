#version 330 core

in vec2 TexCoords;
out vec4 FragColor; 

uniform sampler2D atlas;
uniform vec3 textColor; 


void main( ){
float alpha = texture(atlas , TexCoords).r ; 
alpha = pow (alpha , 1.0 / 2.2); 
FragColor = vec4(textColor , alpha); 
}
