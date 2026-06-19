#include "object_renderer.h"

ObjectRenderer::~ObjectRenderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(NUM_VBO, vbo);
}

ObjectRenderer::ObjectRenderer(const Shader& shader, const std::string& filePath)
{
	this->shader = shader;
	bool loaded = loader.LoadFile(filePath);
	if (loaded)
		initialize_render_data();
}

void ObjectRenderer::initialize_render_data()
{
	std::vector<float> pvalues; //vertex positions
	std::vector<float> tvalues; // texture coordinates
	std::vector<float> nvalues;	//normal coordinates

	for (auto& v : loader.LoadedVertices) {
		pvalues.push_back(v.Position.X);
		pvalues.push_back(v.Position.Y);
		pvalues.push_back(v.Position.Z);

		tvalues.push_back(v.TextureCoordinate.X);
		tvalues.push_back(v.TextureCoordinate.Y);

		nvalues.push_back(v.Normal.X);
		nvalues.push_back(v.Normal.Y);
		nvalues.push_back(v.Normal.Z);
	}

	indices = loader.LoadedIndices;

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(3, vbo);
	glGenBuffers(1, &ebo);

	// put the vertices into buffer #0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * sizeof(float), &pvalues[0], GL_STATIC_DRAW);
	// put the texture coordinates into buffer #1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * sizeof(float), &tvalues[0], GL_STATIC_DRAW);
	// put the normals into buffer #2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * sizeof(float), &nvalues[0], GL_STATIC_DRAW);

	// Element buffer (indices)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}


void ObjectRenderer::draw_mesh(float& aspectRatio, Camera& camera)
{
	this->shader.use();
	float transform_z = -8.0f; // where to place the object in z-axis

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 vMat = camera.GetViewMatrix();
	glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.0f, transform_z));
	//mMat *= glm::scale(glm::mat4(1.0f), glm::vec3(0.02f, 0.02f, 0.02f));
	//mMat =  glm::rotate(mMat, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	//std::cout << glGetError() << std::endl;


	glm::mat4 invTrMat = glm::transpose(glm::inverse(mMat)); // build the inverse-transpose(normal) matrices into the corresponding uniforms


	this->shader.setMat4("v_matrix", vMat);
	this->shader.setMat4("m_matrix", mMat);
	this->shader.setMat4("norm_matrix", invTrMat);
	this->shader.setMat4("p_matrix", projection);


	setup_lighting();

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, brickTexture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


}

void ObjectRenderer::setup_lighting()
{
	this->shader.setVec4("globalAmbient", globalAmbient[0], globalAmbient[1], globalAmbient[2], globalAmbient[3]);
	this->shader.setVec4("material.ambient", matAmb[0], matAmb[1], matAmb[2], matAmb[3]);
	this->shader.setVec4("material.diffuse", matDif[0], matDif[1], matDif[2], matDif[3]);
	this->shader.setVec4("material.specular", matSpe[0], matSpe[1], matSpe[2], matSpe[3]);
	this->shader.setVec4("light.ambient", lightAmbient[0], lightAmbient[1], lightAmbient[2], lightAmbient[3]);
	this->shader.setVec4("light.diffuse", lightDiffuse[0], lightDiffuse[1], lightDiffuse[2], lightDiffuse[3]);
	this->shader.setVec4("light.specular", lightSpecular[0], lightSpecular[1], lightSpecular[2], lightSpecular[3]);
	this->shader.setVec4("light.position", glm::vec4(currentLightPos, 1.0f));
	this->shader.setFloat("material.shininess", mat_shininess);

}