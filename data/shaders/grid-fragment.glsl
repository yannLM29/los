#version 330 core
out vec4 FragColor;

in vec3 position;
uniform vec3 color;

void main()
{
    vec3 line_color = color;
    if(position.y != 0 && position.x == 0 && position.z == 0) {
        line_color = vec3(0.0, 1.0, 0.0);
    } else if(position.x == 0) {
        line_color = vec3(0.0, 0.0, 1.0);
    } else if(position.z == 0) {
        line_color = vec3(1.0, 0.0, 0.0);
    }

    FragColor = vec4(line_color, 1.0f);
}

