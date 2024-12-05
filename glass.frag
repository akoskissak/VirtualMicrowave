#version 330 core

out vec4 FragColor;

uniform int isGlassOn;

void main() {
    if(isGlassOn == 1){
        FragColor = vec4(0.0f, 0.1f, 0.8f, 0.6f);
    }
    else{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}