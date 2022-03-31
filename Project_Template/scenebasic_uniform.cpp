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



SceneBasic_Uniform::SceneBasic_Uniform() : angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>() / 8.0f), torus(1.75f * 0.75f, 0.75f * 0.75f, 50, 50), teapot(14, glm::mat4(1.0f)), plane(50.0f, 50.0f, 1, 1)
{
	//mesh = ObjMesh::load("../Project_Template/media/pig_triangulated.obj", true);
	//ogre = ObjMesh::load("../Project_Template/media/bs_ears.obj",false, true);
}

////Multiple Light
//void SceneBasic_Uniform::initScene()
//{
//    compile();
//
//	glEnable(GL_DEPTH_TEST);
//
//	
//	//model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
//	//model = glm::rotate(model, glm::radians(15.0f), vec3(0.0f, 1.0f, 0.0f));
//
//	view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//
//	projection = mat4(1.0f);
//
//
//	//prog.setUniform("Light.La", glm::vec3(0.2f, 0.2f, 0.2f));
//	//prog.setUniform("Light.Ld", glm::vec3(0.9f, 0.5f, 0.2f));
//	//prog.setUniform("Lights[1].La", glm::vec3(0.06f, 0.06f, 0.06f));
//	//prog.setUniform("Lights[1].Ld", glm::vec3(0.0f, 0.6f, 0.0f));	
//	//prog.setUniform("Lights[2].La", glm::vec3(0.06f, 0.06f, 0.06f));
//	//prog.setUniform("Lights[2].Ld", glm::vec3(0.0f, 0.0f, 0.6f));
//	
//
//	//Moving cameras 
//	//float x, z;
//	//for (int i = 0; i < 3; i++)
//	//{
//	//	std::stringstream name;
//	//	name << "Lights[" << i << "].Position";
//	//	x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
//	//	z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
//	//	prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, 1.0f));
//	//}
//
//	
//	
//}

////Normal Map
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//	glEnable(GL_DEPTH_TEST);
//
//	view = glm::lookAt(vec3(-1.0f, 0.25f, 2.0f),
//					   vec3(0.0f, 0.0f, 0.0f),
//					   vec3(0.0f, 1.0f, 0.0f));
//
//	projection = mat4(1.0f);
//
//	prog.setUniform("Light.Ld", vec3(1.0f,1.0f,1.0f));
//	prog.setUniform("Light.La", vec3(0.2f,0.2f,0.2f)); 
//
//	GLuint diffuse = Texture::loadTexture("../Project_Template/media/texture/ogre_diffuse.png");
//	GLuint normal = Texture::loadTexture("../Project_Template/media/texture/ogre_normalmap.png");
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, diffuse);
//
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, normal);
//
//	
//	
//}

//Skybox
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//	glEnable(GL_DEPTH_TEST);
//
//	projection = mat4(1.0f);
//
//	angle = glm::radians(90.0f); //set the initial angle
//
//	//extract the cube texture
//	GLuint cubeTex = Texture::loadHdrCubeMap("../Project_Template/media/texture/cube/pisa-hdr/pisa");
//
//	//activate and bindtexture
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex);
//}

////Edge Detection
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//	glEnable(GL_DEPTH_TEST);
//	projection = mat4(1.0f);
//	angle = glm::pi<float>() / 4.0f;
//	setupFBO();
//
//	// Array for full-screen quad
//	GLfloat verts[] = {
//	-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//	-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
//	};
//	GLfloat tc[] = {
//	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//	0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
//	};
//	// Set up the buffers
//	unsigned int handle[2];
//	glGenBuffers(2, handle);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);
//	// Set up the vertex array object
//	glGenVertexArrays(1, &fsQuad);
//	glBindVertexArray(fsQuad);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
//	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0); // Vertex position
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(2); // Texture coordinates
//	glBindVertexArray(0);
//	prog.setUniform("EdgeThreshold", 0.05f);
//	prog.setUniform("Light.Ld", vec3(1.0f));
//	prog.setUniform("Light.Ls", vec3(1.0f));
//	prog.setUniform("Light.La", vec3(0.2f));
//
//}

void SceneBasic_Uniform::initScene()
{
	compile();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	projection = mat4(1.0f);
	angle = glm::pi<float>() / 4.0f;
	setupFBO();

	// Array for full-screen quad
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
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);
	// Set up the vertex array object
	glGenVertexArrays(1, &fsQuad);
	glBindVertexArray(fsQuad);
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0); // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2); // Texture coordinates
	glBindVertexArray(0);
	prog.setUniform("Light.Ld", vec3(1.0f));
	prog.setUniform("Light.Ls", vec3(1.0f));
	prog.setUniform("Light.La", vec3(0.2f));

	float weights[5], sum, sigma2 = 8.0f;
	// Compute and sum the weights
	weights[0] = gauss(0, sigma2);
	sum = weights[0];
	for (int i = 1; i < 5; i++)
	{
		weights[i] = gauss(float(i), sigma2);
		sum += 2 * weights[i];
	}
	// Normalize the weights and set the uniform
	for (int i = 0; i < 5; i++)
	{
		std::stringstream uniName;
		uniName << "Weight[" << i << "]";
		float val = weights[i] / sum;
		prog.setUniform(uniName.str().c_str(), val);
	}

}





void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform_Blinn_phong_gaussian_blur.vert");
		prog.compileShader("shader/basic_uniform_Blinn_phong_gaussian_blur.frag");


		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::setMatrices()
{
	mat4 mv = view * model;

	prog.setUniform("ModelViewMatrix", mv);

	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]),
									vec3(mv[1]),
									vec3(mv[2])));

	prog.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::update( float t )
{
	//float deltaT = t - tPrev;

	//if (tPrev == 0.0f)
	//{
	//	deltaT = 0.0f;
	//}		
	//tPrev = t;
	//angle += rotSpeed * deltaT;
	//

	//if (angle > glm::two_pi<float>())
	//{
	//	angle -= glm::two_pi<float>();
	//	
	//}

		
}

void SceneBasic_Uniform::render()
{
 //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glm::vec4 lightPos = glm::vec4(2.0f, 1.0f, 2.0f, 1.0f);
	//prog.setUniform("Light.Position", view * lightPos);
	//prog.setUniform("Light.La", vec3(0.2f, 0.2f, 0.2f));
	//prog.setUniform("Light.Ld", vec3(0.2f, 0.2f, 0.2f));


	////Skybox
	//vec3 cameraPos = vec3(7.0f * cos(angle), 2.0f, 7.0f * sin(angle));
	//view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	//// Draw sky
	//prog.use();
	//model = mat4(1.0f);
	//setMatrices();
	//sky.render();

	//Piggy
	//prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
	//prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
	//prog.setUniform("Material.Shininess", 120.0f);
	//model = mat4(1.0f);
	//model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	//setMatrices();
	//mesh->render();

	//glm::mat3 normalMatrix = glm::mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
	//prog.setUniform("Light.Direction", normalMatrix * vec3(-lightPos));

	////Ogre
	//prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
	//prog.setUniform("Material.Ks", 0.7f, 0.7f, 0.7f);
	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
	//prog.setUniform("Material.Shininess", 2000.0f);
	//model = mat4(1.0f);
	//setMatrices();
	//ogre->render();
	
	////Cube
	//prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
	//prog.setUniform("Material.Shininess", 50.0f);
	//model = mat4(1.0f);
	//model = glm::translate(model, vec3(0.0f, 0.0f, -1.0f));
	//setMatrices();
	//cube.render();

	////Teapot
	//model = mat4(1.0f);
	//model = glm::translate(model, vec3(0.0f, 0.0f, -1.0f));
	//model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	//setMatrices();
	//teapot.render();

	////Donut
	//prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
	//prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
	//prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
	//prog.setUniform("Material.Shininess", 100.0f);
	//model = mat4(1.0f);
	//model = glm::translate(model, vec3(-1.0f, 0.75f, 3.0f));
	//model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	//setMatrices();
	//torus.render();

	////Plane
	//prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
	//prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
	//prog.setUniform("Material.Shininess", 180.0f);
	//model = mat4(1.0f);
	//setMatrices();
	//plane.render();    

	////Edge Detection
	//pass1();
	//glFlush();
	//pass2();

	pass1();
	pass2();
	pass3();

}

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h,
		0.3f, 100.0f);
}

////EDGE DETECTION\\\\
//void SceneBasic_Uniform::setupFBO()
//{
//	// Generate and bind the framebuffer
//	glGenFramebuffers(1, &fboHandle);
//	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
//
//	// Create the texture object
//	glGenTextures(1, &renderTex);
//	glBindTexture(GL_TEXTURE_2D, renderTex);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
//
//	// Bind the texture to the FBO
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTex, 0);
//
//	// Create the depth buffer
//	GLuint depthBuf;
//	glGenRenderbuffers(1, &depthBuf);
//	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//
//	// Bind the depth buffer to the FBO
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
//
//	// Set the targets for the fragment output variables
//	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
//	glDrawBuffers(1, drawBuffers);
//
//	// Unbind the framebuffer, and revert to default framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//}

void SceneBasic_Uniform::pass1()
{
	prog.setUniform("Pass", 1);
	glBindFramebuffer(GL_FRAMEBUFFER, renderFBO);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = glm::lookAt(vec3(7.0f * cos(angle), 4.0f, 7.0f * sin(angle)),
		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(60.0f), (float)width / height,
		0.3f, 100.0f);


	prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
	prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
	prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
	prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
	prog.setUniform("Material.Shininess", 100.0f);
	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	teapot.render();

	prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
	prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
	prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
	prog.setUniform("Material.Shininess", 1.0f);
	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, -0.75f, 0.0f));
	setMatrices();
	plane.render();

	prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
	prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.2f);
	prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
	prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
	prog.setUniform("Material.Shininess", 100.0f);
	model = mat4(1.0f);
	model = glm::translate(model, vec3(1.0f, 1.0f, 3.0f));
	model = glm::rotate(model, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	torus.render();
}


//void SceneBasic_Uniform::pass2()
//{
//	prog.setUniform("Pass", 2);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, renderTex);
//	glDisable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	model = mat4(1.0f);
//	view = mat4(1.0f);
//	projection = mat4(1.0f);
//	setMatrices();
//
//	// Render the full-screen quad
//	glBindVertexArray(fsQuad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//	glBindVertexArray(0);
//}

void SceneBasic_Uniform::setupFBO() {
	// Generate and bind the framebuffer
	glGenFramebuffers(1, &renderFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, renderFBO);
	// Create the texture object
	glGenTextures(1, &renderTex);
	glBindTexture(GL_TEXTURE_2D, renderTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	// Bind the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		renderTex, 0);
	// Create the depth buffer
	GLuint depthBuf;
	glGenRenderbuffers(1, &depthBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	// Bind the depth buffer to the FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, depthBuf);
	// Set the targets for the fragment output variables
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);
	// Unbind the framebuffer, and revert to default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Generate and bind the framebuffer
	glGenFramebuffers(1, &intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
	// Create the texture object
	glGenTextures(1, &intermediateTex);
	glActiveTexture(GL_TEXTURE0); // Use texture unit 0
	glBindTexture(GL_TEXTURE_2D, intermediateTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	// Bind the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		intermediateTex, 0);
	// No depth buffer needed for this FBO
	// Set the targets for the fragment output variables
	glDrawBuffers(1, drawBuffers);
	// Unbind the framebuffer, and revert to default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneBasic_Uniform::pass2()
{
	prog.setUniform("Pass", 2);
	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTex);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	model = mat4(1.0f);
	view = mat4(1.0f);
	projection = mat4(1.0f);
	setMatrices();
	// Render the full-screen quad
	glBindVertexArray(fsQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SceneBasic_Uniform::pass3()
{
	prog.setUniform("Pass", 3);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, intermediateTex);
	glClear(GL_COLOR_BUFFER_BIT);
	model = mat4(1.0f);
	view = mat4(1.0f);
	projection = mat4(1.0f);
	setMatrices();
	// Render the full-screen quad
	glBindVertexArray(fsQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

float SceneBasic_Uniform::gauss(float x, float sigma2)
{
	double coeff = 1.0 / (glm::two_pi<double>() * sigma2);
	double expon = -(x * x) / (2.0 * sigma2);
	return (float)(coeff * exp(expon));
}