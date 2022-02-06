#include "PointCloudVis.h"

PointCloudVis::PointCloudVis()
    : m_shader{}
{
	if (!m_shader.load("resources/pointCloud.vert", "resources/pointCloud.frag"))
	{
		throw std::exception(); //"could not load shaders");
	}
}

/// <summary>
///
/// </summary>
void PointCloudVis::draw(unsigned int pointCloudTexId, unsigned int rgbTexId, bool drawNormals, glm::mat4x4 &mvpMat)
{
	m_shader.begin();

	m_shader.setUniformMatrix4f("modelViewProjectionMatrix", mvpMat);

	//m_shader.setUniform1f("mixFactor", factor);

	glUniform1i(m_shader.getUniformLocation("worldTex"), 0);
	glUniform1i(m_shader.getUniformLocation("colorTex"), 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pointCloudTexId);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, rgbTexId);

	GLuint emptyVAO;
	glGenVertexArrays(1, &emptyVAO);
	glBindVertexArray(emptyVAO);
	glPointSize(1.0f);
	glDrawArrays(GL_POINTS, 0, 640 * 480);

	m_shader.end();
}