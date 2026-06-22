#include "Shader.h"
#include "camera.h"
#include "LoadedMesh.h"
#include <glm/glm.hpp>


class ObjectRenderer
{
private:
    static const int NUM_VBO = 3;
    Shader shader;

    objl::Loader loader;
    std::vector<unsigned int> indices;
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
    GLuint ebo = 0;
    GLuint vbo[NUM_VBO];
    void setup_lighting();

public:
    ObjectRenderer() { currentLightPos = glm::vec3(initialLightLoc); }
    ~ObjectRenderer();
    ObjectRenderer(const Shader& shader, const std::string& filePath);
    void initialize_render_data();
    void draw_mesh(float& aspectRatio, Camera& camera);
};

