#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/torus.h"
#include "helper/teapot.h"

#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/cube.h"
#include "helper/skybox.h"
#include "helper/sphere.h"

class SceneBasic_Uniform : public Scene
{
private:
    //GLSLProgram prog;
    //Torus torus;
    //Teapot teapot;
    //Plane plane;
    //Cube cube;
    //std::unique_ptr<ObjMesh> mesh;
    //std::unique_ptr<ObjMesh> ogre;
    //SkyBox sky;
    //Sphere sphere;

    //void setMatrices();
    //void compile();

    ////GAUSSIAN
    //float angle, tPrev, rotSpeed;
    //GLuint fsQuad;
    //GLuint renderFBO, intermediateFBO;
    //GLuint renderTex, intermediateTex;
    //void setupFBO();
    //void pass1();
    //void pass2();
    //void pass3();
    //float gauss(float, float);

    ////HDR
    //GLSLProgram prog;
    //GLuint hdrFBO;
    //GLuint quad;
    //GLuint hdrTex, avgTex;
    //Plane plane;
    //Sphere sphere;
    //Teapot teapot;
    //void setMatrices();
    //void compile();
    //void setupFBO();
    //void pass1();
    //void pass2();
    //void computeLogAveLuminance();
    //void drawScene();

    //BLOOM
    //GLSLProgram prog;
    //GLuint fsQuad;
    //GLuint hdrFBO, blurFBO;
    //GLuint hdrTex, tex1, tex2;
    //GLuint linearSampler, nearestSampler;
    //Plane plane;
    //Sphere sphere;
    //Teapot teapot;
    //float angle;
    //int bloomBufWidth, bloomBufHeight;
    //void setMatrices();
    //void compile();
    //void setupFBO();
    //void pass1();
    //void pass2();
    //void pass3();
    //void pass4();
    //void pass5();
    //float gauss(float, float);
    //void computeLogAveLuminance();
    //void drawScene();
    
    ////DEFERRED
    //GLSLProgram prog;
    //GLuint deferredFBO;
    //GLuint quad;
    //Plane plane;
    //Torus torus;
    //Teapot teapot;
    //float angle, tPrev, rotSpeed;
    //void setMatrices();
    //void compile();
    //void setupFBO();
    //void createGBufTex(GLenum, GLenum, GLuint&);
    //void pass1();
    //void pass2();

    //Point Sprite
    GLSLProgram prog;

    GLuint sprites;
    int numSprites;
    float* locations;

    void setMatrices();
    void compile();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
