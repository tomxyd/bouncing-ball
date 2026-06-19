#include "SphereRenderer.h"

SphereRenderer::~SphereRenderer()
{
	delete mySphere;
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(NUM_VBO, vbo);
}

void SphereRenderer::initialize_render_data()
{
	default_sphere();

	//procedurally generates necessary data
	std::vector<int> ind = mySphere->getIndices();
	std::vector<glm::vec3> vert = mySphere->getVertices();
	std::vector<glm::vec2> tex = mySphere->getTexCoords();
	std::vector<glm::vec3> norm = mySphere->getNormals();
	std::vector<float> pvalues; //vertex positions
	std::vector<float> tvalues; // texture coordinates
	std::vector<float> nvalues;	//normal coordinates

	int numIndices = mySphere->getNumIndices();
	for (int i = 0; i < numIndices; i++) {
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);
		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);
		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
	}

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(3, vbo);
	// put the vertices into buffer #0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

	// put the normals into buffer #2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
}


void SphereRenderer::draw_mesh(float& aspectRatio, glm::vec3& position, Camera& camera)
{
	this->shader.use();
	float transform_z = -8.0f; // where to place the object in z-axis

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 vMat = camera.GetViewMatrix();
	glm::mat4 mMat = glm::translate(glm::mat4(1.0f), glm::vec3(position));
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

	glDrawArrays(GL_TRIANGLES, 0, mySphere->getNumIndices());

}

void SphereRenderer::setup_lighting()
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