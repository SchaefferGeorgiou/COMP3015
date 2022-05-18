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


////SURFACE ANIMATOR
//SceneBasic_Uniform::SceneBasic_Uniform() : time(0), plane(13.0f, 10.0f, 200, 2)
//{
//
//}


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

	projection = mat4(1.0f);
}

#pragma endregion

#pragma region compile


void SceneBasic_Uniform::compile()
{
	try {
		progOne.compileShader("shader/First.vert");
		//progOne.compileShader("shader/First.geom");
		progOne.compileShader("shader/First.frag");
		
		progOne.link();
		progOne.use();
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
	progOne.setUniform("ModelViewMatrix", mv);
	progOne.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	progOne.setUniform("MVP", projection * mv);
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

////WEEK 1-5
//void SceneBasic_Uniform::render()
//{
// //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	//glm::vec4 lightPos = glm::vec4(2.0f, 1.0f, 2.0f, 1.0f);
//	//prog.setUniform("Light.Position", view * lightPos);
//	//prog.setUniform("Light.La", vec3(0.2f, 0.2f, 0.2f));
//	//prog.setUniform("Light.Ld", vec3(0.2f, 0.2f, 0.2f));
//
//	////Skybox
//	//vec3 cameraPos = vec3(7.0f * cos(angle), 2.0f, 7.0f * sin(angle));
//	//view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	//// Draw sky
//	//prog.use();
//	//model = mat4(1.0f);
//	//setMatrices();
//	//sky.render();
//
//	//Piggy
//	//prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
//	//prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
//	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
//	//prog.setUniform("Material.Shininess", 120.0f);
//	//model = mat4(1.0f);
//	//model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
//	//setMatrices();
//	//mesh->render();
//
//	//glm::mat3 normalMatrix = glm::mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
//	//prog.setUniform("Light.Direction", normalMatrix * vec3(-lightPos));
//
//	////Ogre
//	//prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
//	//prog.setUniform("Material.Ks", 0.7f, 0.7f, 0.7f);
//	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
//	//prog.setUniform("Material.Shininess", 2000.0f);
//	//model = mat4(1.0f);
//	//setMatrices();
//	//ogre->render();
//	
//	////Cube
//	//prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
//	//prog.setUniform("Material.Shininess", 50.0f);
//	//model = mat4(1.0f);
//	//model = glm::translate(model, vec3(0.0f, 0.0f, -1.0f));
//	//setMatrices();
//	//cube.render();
//
//	////Teapot
//	//model = mat4(1.0f);
//	//model = glm::translate(model, vec3(0.0f, 0.0f, -1.0f));
//	//model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
//	//model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
//	//setMatrices();
//	//teapot.render();
//
//	////Donut
//	//prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
//	//prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
//	//prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
//	//prog.setUniform("Material.Shininess", 100.0f);
//	//model = mat4(1.0f);
//	//model = glm::translate(model, vec3(-1.0f, 0.75f, 3.0f));
//	//model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
//	//setMatrices();
//	//torus.render();
//
//	////Plane
//	//prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
//	//prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
//	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
//	//prog.setUniform("Material.Shininess", 180.0f);
//	//model = mat4(1.0f);
//	//setMatrices();
//	//plane.render();    
//
//	////Edge Detection
//	//pass1();
//	//glFlush();
//	//pass2();
//
//	////Gaussian Blur
//	//pass1();
//	//pass2();
//	//pass3();
//
//	////HDR
//	//pass1();
//	//computeLogAveLuminance();
//	//pass2();
//
//	////BLOOM
//	//pass1();
//	//computeLogAveLuminance();
//	//pass2();
//	//pass3();
//	//pass4();
//	//pass5();
//	
//	////DEFERRED
//	//pass1();
//	//pass2();
//
//}

////POINT SPRITE
//void SceneBasic_Uniform::render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	vec3 cameraPos(0.0f, 0.0f, 3.0f);
//	view = glm::lookAt(cameraPos,
//						vec3(0.0f, 0.0f, 0.0f),
//						vec3(0.0f, 1.0f, 0.0f));
//
//	model = mat4(1.0f);
//	setMatrices();
//
//	glBindVertexArray(sprites);
//	glDrawArrays(GL_POINTS, 0, numSprites);
//
//	glFinish();
//}

////WIREFRAME
//void SceneBasic_Uniform::render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	vec3 cameraPos(0.0f, 0.0f, 3.0f);
//	view = glm::lookAt(cameraPos,
//						vec3(0.0f, 0.0f, 0.0f),
//						vec3(0.0f, 1.0f, 0.0f));
//
//	model = mat4(1.0f);
//	setMatrices();
//	ogre->render();
//
//	glFinish();
//}

////SILHOUETTE
//void SceneBasic_Uniform::render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	vec3 cameraPos(1.5f * cos(angle), 0.0f, 1.5f * sin(angle));
//	view = glm::lookAt(cameraPos,
//		vec3(0.0f, -0.2f, 0.0f),
//		vec3(0.0f, 1.0f, 0.0f));
//
//	model = mat4(1.0f);
//	setMatrices();
//	ogre->render();
//
//	glFinish();
//}

////SURFACE ANIMATION
//void SceneBasic_Uniform::render()
//{
//	prog.setUniform("Time", time);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	
//	view = glm::lookAt(vec3(10.0f * cos(angle),4.0f,10.0f * sin(angle)), vec3(0.0f,0.0f,0.0f), vec3(0.0f, 1.0f, 0.0f));
//	projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);
//
//	prog.setUniform("Material.Ka", vec3(0.2f, 0.5f, 0.9f));
//	prog.setUniform("Material.Kd", vec3(0.2f,0.2f,0.2f));
//	prog.setUniform("Material.Ks", vec3(0.8f, 0.8f, 0.8f));
//	prog.setUniform("Material.Shininess", 100.0f);
//	prog.setUniform("Light.Intensity", vec3(1.0f, 1.0f, 1.0f));
//
//	model = mat4(1.0f);
//	model = glm::rotate(model, glm::radians(-10.0f), vec3(0.0f, 0.0f, 1.0f));
//	model - glm::rotate(model, glm::radians(50.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	plane.render();
//}


//CLOUD EFFECT
void SceneBasic_Uniform::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	view = glm::lookAt(vec3(0.0f,5.0f,-10.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(67.5f), (float)width / height, 0.3f, 100.0f);


	progOne.setUniform("Light.Position", vec4(0.0f,3.0f,3.0f,1.0f));
	progOne.setUniform("Light.Intensity", 0.7f);

	//Plane
	progOne.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
	progOne.setUniform("Material.Kd", 0.7f, 0.0f, 0.3f);
	progOne.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
	progOne.setUniform("Material.Shininess", 50.0f);
	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, 0.0f, 5.0f));


	setMatrices();
	plane.render();

}


#pragma endregion

#pragma region resize

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

#pragma endregion

#pragma region drawScene

void SceneBasic_Uniform::drawScene()
{



	//glBindVertexArray(quad);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

#pragma endregion