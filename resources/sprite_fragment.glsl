#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{   
    vec2 uv = TexCoords.xy;
    float t = pow(uv.x, 4.0); // pow-example
    vec3 c = mix(vec3(0.1, 0.15, 0.35), vec3(1.0, 0.85, 0.35), t);
    float d = (uv.x + uv.y) * 0.5; //diagonal-shift

    vec2 p = uv - 0.5;
    float e = length(p);
    float radius = 0.25;
    float circle = 1 - step(radius, e);
    vec3 bg = vec3(0.0,0.0,0.0);
    vec3 colour = mix(bg,spriteColor,circle);
    color = vec4(colour, circle);
} 