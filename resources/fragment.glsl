#version 330 core
out vec4 FragColor;
in vec4 varyingColor;
uniform sampler2D samp;

void main()
{
    FragColor = varyingColor;
}
