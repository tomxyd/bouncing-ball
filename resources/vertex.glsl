#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertNormal;

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct PositionalLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

uniform mat4 v_matrix;
uniform mat4 m_matrix;
uniform mat4 p_matrix;
uniform mat4 norm_matrix;

uniform Material material;
uniform PositionalLight light;
uniform vec4 globalAmbient;

out vec4 varyingColor;

mat4 buildRotateX(float rad); 
mat4 buildRotateY(float rad); 
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main()
{ 
    vec4 P = m_matrix * vec4(position, 1.0);
    vec3 N = normalize((norm_matrix * vec4(vertNormal,1.0)).xyz);
    vec3 L = normalize(light.position - P.xyz);
    // view vector is from vertex to camera, camera loc is extracted from view matrix
    vec3 V = normalize(-v_matrix[3].xyz - P.xyz);
    // R is reflection of -L with respect to surface normal N
    vec3 R = reflect(-L,N);

    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L), 0.0);
    vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R,V), 0.0f), material.shininess);

	gl_Position = p_matrix * v_matrix * m_matrix  * vec4(position, 1.0);

    varyingColor = vec4((ambient + diffuse + specular), 1.0);
}

mat4 buildTranslate(float x, float y, float z)
{ 
	mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
						0.0, 1.0, 0.0, 0.0,
						0.0, 0.0, 1.0, 0.0,
						x, y, z, 1.0 );
	return trans;
}
// builds and returns a matrix that performs a rotation around the X axis
mat4 buildRotateX(float rad)
{ mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
     0.0, cos(rad), -sin(rad), 0.0,
     0.0, sin(rad), cos(rad), 0.0,
     0.0, 0.0, 0.0, 1.0 );
 return xrot;
}
// builds and returns a matrix that performs a rotation around the Y axis
mat4 buildRotateY(float rad)
{ mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
     0.0, 1.0, 0.0, 0.0,
     -sin(rad), 0.0, cos(rad), 0.0,
     0.0, 0.0, 0.0, 1.0 );
 return yrot;
}
// builds and returns a matrix that performs a rotation around the Z axis
mat4 buildRotateZ(float rad)
{ mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
     sin(rad), cos(rad), 0.0, 0.0,
     0.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 1.0 );
 return zrot;
}