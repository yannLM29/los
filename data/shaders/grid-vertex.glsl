#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    if(aPos.y != 0) {
        gl_Position = projection * view * vec4(aPos, 1.0f);
    } else {
        gl_Position = projection * view * model * vec4(aPos, 1.0f);
    }
    vec4 temp_pos = model * vec4(aPos, 1.0f);
    position = temp_pos.xyz;
}