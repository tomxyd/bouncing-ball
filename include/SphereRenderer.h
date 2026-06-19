#include "Shader.h"
#include "camera.h"
#include "Sphere.h"
#include "Utils.h"
#include <glm/glm.hpp>

//loads vertex data from sphere class
//send data to GPU
//load shader
//send transformation matrices to shader
class SphereRenderer
{
private:
   static const int NUM_VBO = 3;
   Shader shader;
   Sphere* mySphere = NULL;

   glm::vec3 currentLightPos;
   glm::vec3 initialLightLoc = glm::vec3(5.0f, 2.0f, 2.0f);
   float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };

   float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
   float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
   float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

   float matAmb[4] = { 0.2473f, 0.1995f, 0.0745f, 1 };
   float matDif[4] = { 0.7516f, 0.6065f, 0.2265f, 1 };
   float matSpe[4] = { 0.6283f, 0.5558f, 0.3661f, 1 };
   float mat_shininess = 51.2f;

   GLuint vao = 0;
   GLuint vbo[NUM_VBO];
   void default_sphere()
   {
       mySphere = new Sphere(48 * 2);
   }
   void setup_lighting();

public:
    SphereRenderer() { currentLightPos = glm::vec3(initialLightLoc); }
   ~SphereRenderer();
   SphereRenderer(const Shader& shader)
   {
       this->shader = shader;
       initialize_render_data();
   }
   void initialize_render_data();
   void draw_mesh(float& aspectRatio, glm::vec3& position, Camera& camera);
};

