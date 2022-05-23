#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sstream>

#include "helper/texture.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;


SceneBasic_Uniform::SceneBasic_Uniform() : plane(20.0f, 20.0f, 2, 2)
{

}

#pragma region initScene


//CLOUD EFFECT
void SceneBasic_Uniform::initScene()
{
	compile();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	

	// Array for quad
	GLfloat verts[] = {
	-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
	};
	GLfloat tc[] = {
	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};
	// Set up the buffers
	unsigned int handle[2];
	glGenBuffers(2, handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts,	GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);

	// Set up the vertex array object
	glGenVertexArrays(1, &quad);
	glBindVertexArray(quad);
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0); // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2); // Texture coordinates
	glBindVertexArray(0);

	setupFBO();

}

#pragma endregion

#pragma region compile


void SceneBasic_Uniform::compile()
{
	try {
		prog1.compileShader("shader/Deferr.vert");
		
		prog1.compileShader("shader/Deferr.frag");
		prog1.link();
		
		prog2.compileShader("shader/BlinnPhong.vert");
		prog2.compileShader("shader/BlinnPhong.frag");
		prog2.link();
		
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

#pragma endregion

#pragma region setMatrices


void SceneBasic_Uniform::setMatrices()
{
	mat4 mv = view * model;
	if (pass == 1)
	{		
		prog1.setUniform("ModelViewMatrix", mv);
		prog1.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
		prog1.setUniform("MVP", projection * mv);
	}
	else if (pass == 2)
	{
		prog2.setUniform("MVP", projection * mv);

	}	
	else
	{
	}


}

#pragma endregion

void SceneBasic_Uniform::update( float t )
{
	//float deltaT = t - tPrev;
	//if (tPrev == 0.0f)
	//{
	//	deltaT = 0.0f;
	//}
	//tPrev = t;
	//angle += 0.2f * deltaT;
	//
	//if (angle > glm::two_pi<float>())
	//{
	//	angle -= glm::two_pi<float>();		
	//}

	//time = t;
}

#pragma region render


void SceneBasic_Uniform::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Pass1();
	Pass2();
	
}


#pragma endregion

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic_Uniform::createGBufTex(GLenum texUnit, GLenum format, GLuint& texid)
{
	glActiveTexture(texUnit);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
}

void SceneBasic_Uniform::setupFBO()
{
	GLuint depthBuf, posTex, normTex, colourTex;

	// Create and bind the FBO
	glGenFramebuffers(1, &deferredFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);

	// The depth buffer
	glGenRenderbuffers(1, &depthBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

	// Create the textures for position, normal and colour
	createGBufTex(GL_TEXTURE0, GL_RGB32F, posTex); // Position
	createGBufTex(GL_TEXTURE1, GL_RGB32F, normTex); // Normal
	createGBufTex(GL_TEXTURE2, GL_RGB8, colourTex); // Colour

	// Attach the textures to the framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,	posTex, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,	normTex, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,	colourTex, 0);

	GLenum drawBuffers[] = { GL_NONE,
							 GL_COLOR_ATTACHMENT0,
							 GL_COLOR_ATTACHMENT1,
							 GL_COLOR_ATTACHMENT2 };

	glDrawBuffers(4, drawBuffers);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#pragma region Passes

void SceneBasic_Uniform::Pass1()
{
	prog1.use();
	glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	pass = 1;

	view = glm::lookAt(vec3(7.0f * cos(angle), 4.0f, 7.0f * sin(angle)),
		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(60.0f), (float)width / height,
		0.3f, 100.0f);

	//Plane
	prog1.setUniform("Material.Kd", 0.7f, 0.0f, 0.3f);

	
	
	//model = glm::translate(model, vec3(0.0f, 0.0f, 5.0f));
	setMatrices();
	plane.render();

	
}

void SceneBasic_Uniform::Pass2()
{
	prog2.use();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	pass = 2;

	prog2.setUniform("Light.Position", vec4(0.0f, 3.0f, 3.0f, 1.0f));
	prog2.setUniform("Light.Intensity", 0.7f);

	prog2.setUniform("Material.Shininess", 50.0f);

	view = mat4(1.0);
	model = mat4(1.0);
	projection = mat4(1.0);
	setMatrices();
	
	
	//glBindVertexArray(quad);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

}

#pragma endregion


