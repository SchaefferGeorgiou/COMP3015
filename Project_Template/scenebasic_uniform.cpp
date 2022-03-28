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
#include "helper/texture.h"

using glm::vec4;
using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : plane(50.0f, 50.0f, 200, 200), alphaCutoff(0.0f), speed(0.1f) 
{
    centrePiece = ObjMesh::load("media/centrePiece.obj", true);
    rock = ObjMesh::load("media/Rock.obj", true);

    direction = true;
    dissolve = true;

    tex1 = Texture::loadTexture("media/texture/moss.png");
    tex2 = Texture::loadTexture("media/texture/brick1.jpg");
    tex3 = Texture::loadTexture("media/texture/cement.jpg");

}

void SceneBasic_Uniform::initScene()
{
    compile();

    glEnable(GL_DEPTH_TEST);

    alphaCutoff = 0.2f;

    model = mat4(1.0f);

    view = glm::lookAt(vec3(0.0f, 8.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    projection = mat4(1.0f);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex2);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);

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
    
    if (!dissolve)
    {
        alphaCutoff -= speed * 0.02f;

        if (alphaCutoff < 0.16f)
        {
            dissolve = true;
        }
    }
    else
    {
        alphaCutoff += speed * 0.2f;

        if (alphaCutoff > 0.9f)
        {
            dissolve = false;
        }
    }
    
    prog.setUniform("AlphaCutoff", alphaCutoff);

    model = glm::rotate(model, glm::radians( t * 24.0f), vec3(0.0f, 1.0f, 0.0f));//rotates

    


    view = glm::translate(view, vec3(0.0f, 0.0f, speed * 0.02f));
    
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //glm::vec4 lightPos = glm::vec4(0.0f, 1.0f, 2.0f, 1.0f);
    //prog.setUniform("Lights[0].Position", view * lightPos);
    //prog.setUniform("Lights[0].La", vec3(0.2f, 0.2f, 0.2f));
    //prog.setUniform("Lights[0].Ld", vec3(0.7f, 0.0f, 0.0f));

    setLights();
    setFog();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex3);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex3);

    //Thingy
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Shininess", 200.0f);
    
    model = glm::scale(model, vec3(0.6f));
    model = glm::translate(model, vec3(0.0f, 5.0f, 0.0f));

    setMatrices();
    centrePiece->render();

    //Rocks
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Shininess", 120.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(4.0f, 0.0f, 2.0f));
    setMatrices();
    rock->render();

    model = mat4(1.0f);
    model = glm::translate(model, vec3(-3.0f, 0.0f, -1.0f));
    model = glm::rotate(model, glm::radians(60.0f), vec3(0.2f, 0.5f, 0.3f));
    setMatrices();
    rock->render();

    //Small
    model = mat4(1.0f);
    model = glm::scale(model, vec3(0.4f));
    model = glm::translate(model, vec3(-8.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(56.0f), vec3(0.7f, 0.2f, 0.3f));
    setMatrices();
    rock->render();

    //Large
    model = mat4(1.0f);
    model = glm::scale(model, vec3(3.0f));
    model = glm::translate(model, vec3(2.0f, 0.0f, -2.0f));
    model = glm::rotate(model, glm::radians(20.0f), vec3(1.0f, 0.5f, 0.0f));
    setMatrices();
    rock->render();



    //Plane
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    setMatrices();


    //rebind before drawing
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex2);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    plane.render();    
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
    //1
    glm::mat3 normalMatrix = glm::mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    glm::vec4 lightPos = glm::vec4(0.0f, 25.0f, -15.0f, 1.0f);

    

    prog.setUniform("Lights[0].Position", view * lightPos);
    prog.setUniform("Lights[0].La", vec3(0.06f, 0.06f, 0.06f));//0.066 (0.2/3) so that ambient doesn't stack too much
    prog.setUniform("Lights[0].Ld", vec3(0.9f, 0.0f, 0.0f));
    prog.setUniform("Lights[0].Direction", normalMatrix * vec3(-lightPos));
    prog.setUniform("Lights[0].Exponent", 30.0f);
    prog.setUniform("Lights[0].Cutoff", glm::radians(8.0f));

    //2
    lightPos = glm::vec4(15.0f, 25.0f, 0.0f, 1.0f);
    prog.setUniform("Lights[1].Position", view * lightPos);
    prog.setUniform("Lights[1].La", vec3(0.06f, 0.06f, 0.06f));
    prog.setUniform("Lights[1].Ld", vec3(0.0f, 0.9f, 0.0f));
    prog.setUniform("Lights[1].Direction", normalMatrix * vec3(-lightPos));
    prog.setUniform("Lights[1].Exponent", 30.0f);
    prog.setUniform("Lights[1].Cutoff", glm::radians(8.0f));

    //3
    lightPos = glm::vec4(-15.0f, 25.0f, 0.0f, 1.0f);
    prog.setUniform("Lights[2].Position", view * lightPos);
    prog.setUniform("Lights[2].La", vec3(0.06f, 0.06f, 0.06f));
    prog.setUniform("Lights[2].Ld", vec3(0.0f, 0.0f, 0.9f));
    prog.setUniform("Lights[2].Direction", normalMatrix * vec3(-lightPos));
    prog.setUniform("Lights[2].Exponent", 30.0f);
    prog.setUniform("Lights[2].Cutoff", glm::radians(8.0f));
}

void SceneBasic_Uniform::setFog()
{
    prog.setUniform("Fog.MaxDist", 11.0f);
    prog.setUniform("Fog.MinDist", 10.0f);
    prog.setUniform("Fog.Colour", vec3(0.15f));
}