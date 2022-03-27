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

using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>() / 8.0f)
{
    centrePiece = ObjMesh::load("../Project_Template/media/centrePiece.obj", true);
    //rock = ObjMesh::load("../Project_Template/media/Rock.obj", false, true);

}

void SceneBasic_Uniform::initScene()
{
    compile();

    glEnable(GL_DEPTH_TEST);

    setLights();

}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
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
	//update your angle here
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 120.0f);
    model = mat4(1.0f);
    setMatrices();
    centrePiece->render();

    
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic_Uniform::setLights()
{
    glm::mat3 normalMatrix = glm::mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));

    //Right
    glm::vec4 lightPos = glm::vec4(2.0f, 1.0f, 2.0f, 1.0f);
    prog.setUniform("Lights[0].Position", view * lightPos);
    prog.setUniform("Lights[0].La", vec3(0.2f, 0.0f, 0.0f));
    prog.setUniform("Lights[0].Ld", vec3(0.7f, 0.0f, 0.0f));
    prog.setUniform("Lights[0].Direction", normalMatrix * vec3(-lightPos));
    prog.setUniform("Lights[0].Exponent", 50.0f);
    prog.setUniform("Lights[0].Cutoff", glm::radians(15.0f));

    ////Left
    //lightPos = glm::vec4(-2.0f, 1.0f, 2.0f, 1.0f);
    //prog.setUniform("Lights[1].Position", view * lightPos);
    //prog.setUniform("Lights[1].La", vec3(0.0f, 0.2f, 0.0f));
    //prog.setUniform("Lights[1].Ld", vec3(0.0f, 0.7f, 0.0f));
    //prog.setUniform("Lights[1].Direction", normalMatrix * vec3(-lightPos));
    //prog.setUniform("Lights[1].Exponent", 50.0f);
    //prog.setUniform("Lights[1].Cutoff", glm::radians(15.0f));

    ////Centre
    //lightPos = glm::vec4(0.0f, 1.0f, -2.0f, 1.0f);
    //prog.setUniform("Lights[2].Position", view * lightPos);
    //prog.setUniform("Lights[2].La", vec3(0.0f, 0.0f, 0.2f));
    //prog.setUniform("Lights[2].Ld", vec3(0.0f, 0.0f, 0.7f));
    //prog.setUniform("Lights[2].Direction", normalMatrix * vec3(-lightPos));
    //prog.setUniform("Lights[2].Exponent", 50.0f);
    //prog.setUniform("Lights[2].Cutoff", glm::radians(15.0f));
}
