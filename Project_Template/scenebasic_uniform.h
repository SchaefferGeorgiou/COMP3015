#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/objmesh.h"
#include "helper/plane.h"

class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    Plane plane;
    std::unique_ptr<ObjMesh> centrePiece;
    std::unique_ptr<ObjMesh> rock;

    void setMatrices();
    void compile();

    void setLights();
    void setFog();

    float alphaCutoff, speed;

    bool direction, dissolve;

    GLuint tex1, tex2, tex3;

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H