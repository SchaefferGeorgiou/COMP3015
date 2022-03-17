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

class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    //Torus torus;
    Teapot teapot;
    //Plane plane;
    //Cube cube;
    //std::unique_ptr<ObjMesh> mesh;

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
