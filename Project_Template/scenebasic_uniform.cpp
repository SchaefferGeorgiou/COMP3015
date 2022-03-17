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
using glm::mat4;


SceneBasic_Uniform::SceneBasic_Uniform()
{
	//mesh = ObjMesh::load("../Project_Template/media/pig_triangulated.obj", true);
	ogre = ObjMesh::load("../Project_Template/media/bs_ears.obj", true);
}

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
void SceneBasic_Uniform::initScene()
{
	compile();
	glEnable(GL_DEPTH_TEST);

	view = glm::lookAt(vec3(-1.0f, 0.25f, 2.0f),
					   vec3(0.0f, 0.0f, 0.0f),
					   vec3(0.0f, 1.0f, 0.0f));

	projection = mat4(1.0f);

	prog.setUniform("Light.Ld", vec3(1.0f,1.0f,1.0f));
	prog.setUniform("Light.La", vec3(0.2f,0.2f,0.2f)); 

	GLuint diffuse = Texture::loadTexture("../Project_Template/media/texture/ogre_diffuse.png");
	GLuint normal = Texture::loadTexture("../Project_Template/media/texture/ogre_normalmap.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal);

	
	
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform_Blinn_phong_normal_map.vert");
		prog.compileShader("shader/basic_uniform_Blinn_phong_texture.frag");


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
		vec3(mv[1]), vec3(mv[2])));

	prog.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::update( float t )
{
	
	//model = glm::rotate(model, glm::radians(0.4f * 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(0.4f * 2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Piggy
	//prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
	//prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
	//prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
	//prog.setUniform("Material.Shininess", 120.0f);
	//model = mat4(1.0f);
	//model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	//setMatrices();
	//mesh->render();


	glm::vec4 lightPos = glm::vec4(2.0f, 1.0f, 2.0f,1.0f);
	prog.setUniform("Light.Position", view * lightPos);

	glm::mat3 normalMatrix = glm::mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
	/*prog.setUniform("Light.Direction", normalMatrix * vec3(-lightPos));*/

	//Ogre
	prog.setUniform("Material.Kd", 0.9f, 0.4f, 0.4f);
	prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
	prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
	prog.setUniform("Material.Shininess", 0.5f);
	model = mat4(1.0f);
	
	setMatrices();
	ogre->render();
	

	
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
}

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h,
		0.3f, 100.0f);
}



