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


SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 20,20){}

void SceneBasic_Uniform::initScene()
{
    compile();

	glEnable(GL_DEPTH_TEST);

	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(15.0f), vec3(0.0f, 1.0f, 0.0f));

	view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	projection = mat4(1.0f);

	prog.setUniform("LightPosition", view * glm::vec4(5.0f, 5.0f, 2.0f, 1.0f));
	prog.setUniform("Ld", glm::vec3(1.0f, 1.0f, 1.0f));
	prog.setUniform("Kd", glm::vec3(0.2f, 0.55f, 0.9f));

	
	prog.setUniform("Ls", glm::vec3(1.0f, 1.0f, 1.0f));
	prog.setUniform("Ks", glm::vec3(1.0f, 1.0f, 1.0f));
	

	update(0.0f);

}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform_phong.vert");
		prog.compileShader("shader/basic_uniform_phong.frag");
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
	//update your angle here
}

void SceneBasic_Uniform::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);


	setMatrices();
    
	torus.render();
    //create the rotation matrix here and update the uniform in the shader 
	
}

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h,
		0.3f, 100.0f);
}



