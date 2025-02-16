#version 330 core
out vec4 FragColor;

in vec3 position;

void main()
{
    vec3 color = vec3(1.0, 1.0, 1.0);
    if(position.y != 0) {
        color.x = 0.0;
        color.z = 0.0;
    } else if(position.x == 0) {
        color.x = 0.0;
        color.y = 0.0;
    } else if(position.z == 0) {
        color.z = 0.0;
        color.y = 0.0;
    }

    FragColor = vec4(color, 1.0f);
}

