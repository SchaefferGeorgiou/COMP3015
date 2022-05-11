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

////SILHOUETTE
//SceneBasic_Uniform::SceneBasic_Uniform() : angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>()/8.0f)
//{
//	//mesh = ObjMesh::load("../Project_Template/media/pig_triangulated.obj", true);
//	ogre = ObjMesh::loadWithAdjacency("../Project_Template/media/bs_ears.obj");
//}

//SURFACE ANIMATOR
//SceneBasic_Uniform::SceneBasic_Uniform() : time(0), plane(13.0f, 10.0f, 200, 2)
//{
//
//}

SceneBasic_Uniform::SceneBasic_Uniform() : tPrev(0), shadowMapWidth(512), shadowMapHeight(512), teapot(14, glm::mat4(1.0f)), plane(40.0f, 40.0f, 2, 2), torus(0.7f * 2.0f, 0.3f * 2.0f, 50, 50)
{

}

#pragma region initScene

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

////GAUSSIAN BLUR
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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
//	prog.setUniform("Light.Ld", vec3(1.0f));
//	prog.setUniform("Light.Ls", vec3(1.0f));
//	prog.setUniform("Light.La", vec3(0.2f));
//
//	float weights[5], sum, sigma2 = 8.0f;
//	// Compute and sum the weights
//	weights[0] = gauss(0, sigma2);
//	sum = weights[0];
//	for (int i = 1; i < 5; i++)
//	{
//		weights[i] = gauss(float(i), sigma2);
//		sum += 2 * weights[i];
//	}
//	// Normalize the weights and set the uniform
//	for (int i = 0; i < 5; i++)
//	{
//		std::stringstream uniName;
//		uniName << "Weight[" << i << "]";
//		float val = weights[i] / sum;
//		prog.setUniform(uniName.str().c_str(), val);
//	}
//
//}

////HDR
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//	glEnable(GL_DEPTH_TEST);
//	projection = mat4(1.0f);
//
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
//
//	// Set up the vertex array object
//	glGenVertexArrays(1, &quad);
//	glBindVertexArray(quad);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
//	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0); // Vertex position
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(2); // Texture coordinates
//	glBindVertexArray(0);
//
//	vec3 intense = vec3(5.0f);
//	prog.setUniform("Lights[0].L", intense);
//	prog.setUniform("Lights[1].L", intense);
//	prog.setUniform("Lights[2].L", intense);
//	intense = vec3(0.2f);
//	prog.setUniform("Lights[0].La", intense);
//	prog.setUniform("Lights[1].La", intense);
//	prog.setUniform("Lights[2].La", intense);
//}

////BLOOM
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//
//	vec3 intense = vec3(0.6f);
//	prog.setUniform("Lights[0].L", intense);
//	prog.setUniform("Lights[1].L", intense);
//	prog.setUniform("Lights[2].L", intense);
//
//	intense = vec3(0.2f);
//	prog.setUniform("Lights[0].La", intense);
//	prog.setUniform("Lights[1].La", intense);
//	prog.setUniform("Lights[2].La", intense);
//
//	projection = mat4(1.0f);
//	angle = glm::pi<float>() / 2.0f;
//
//	prog.setUniform("Gamma", 0.5f);
//
//	setupFBO();
//
//	// Array for full-screen quad
//	GLfloat verts[] = {
//	-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//	-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
//	};
//
//	GLfloat tc[] = {
//	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//	0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
//	};
//
//	// Set up the buffers
//	unsigned int handle[2];
//	glGenBuffers(2, handle);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);
//
//	// Set up the vertex array object
//	glGenVertexArrays(1, &fsQuad);
//	glBindVertexArray(fsQuad);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
//	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glEnableVertexAttribArray(0); // Vertex position
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glEnableVertexAttribArray(2); // Texture coordinates
//	glBindVertexArray(0);
//	prog.setUniform("LumThresh", 1.7f);
//	float weights[10], sum, sigma2 = 25.0f;
//
//	// Compute and sum the weights
//	weights[0] = gauss(0, sigma2);
//	sum = weights[0];
//	for (int i = 1; i < 10; i++) {
//		weights[i] = gauss(float(i), sigma2);
//		sum += 2 * weights[i];
//	}
//
//	// Normalize the weights and set the uniform
//	for (int i = 0; i < 10; i++) {
//		std::stringstream uniName;
//		uniName << "Weight[" << i << "]";
//		float val = weights[i] / sum;
//		prog.setUniform(uniName.str().c_str(), val);
//	}
//
//	// Set up two sampler objects for linear and nearest filtering
//	GLuint samplers[2];
//	glGenSamplers(2, samplers);
//	linearSampler = samplers[0];
//	nearestSampler = samplers[1];
//	GLfloat border[] = { 0.0f,0.0f,0.0f,0.0f };
//
//	// Set up the nearest sampler
//	glSamplerParameteri(nearestSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glSamplerParameteri(nearestSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glSamplerParameteri(nearestSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//	glSamplerParameteri(nearestSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	glSamplerParameterfv(nearestSampler, GL_TEXTURE_BORDER_COLOR, border);
//
//	// Set up the linear sampler
//	glSamplerParameteri(linearSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glSamplerParameteri(linearSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//	glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	glSamplerParameterfv(linearSampler, GL_TEXTURE_BORDER_COLOR, border);
//
//	// We want nearest sampling except for the last pass.
//	glBindSampler(0, nearestSampler);
//	glBindSampler(1, nearestSampler);
//}

////DEFERRED
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//	glEnable(GL_DEPTH_TEST);
//	float c = 1.5f;
//	angle = glm::pi<float>() / 2.0f;
//	// Array for quad
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
//	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts,
//		GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);
//	// Set up the vertex array object
//	glGenVertexArrays(1, &quad);
//	glBindVertexArray(quad);
//	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
//	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0); // Vertex position
//	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
//	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(2); // Texture coordinates
//	glBindVertexArray(0);
//	setupFBO();
//	prog.setUniform("Light.L", vec3(1.0f));
//}

////Sprites
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//
//	numSprites = 50;
//	locations = new float[numSprites * 3];
//	srand((unsigned int)time(0));
//
//	for (size_t i = 0; i < numSprites; i++)
//	{
//		vec3 p(((float)rand() / RAND_MAX * 2.0F) - 1.0F,
//			((float)rand() / RAND_MAX * 2.0f) - 1.0f,
//			((float)rand() / RAND_MAX * 2.0f) - 1.0f);
//
//		locations[i * 3] = p.x;
//		locations[i * 3 + 1] = p.y;
//		locations[i * 3 + 2] = p.z;
//	}
//
//	GLuint handle;
//	glGenBuffers(1, &handle);
//
//	glBindBuffer(GL_ARRAY_BUFFER, handle);
//	glBufferData(GL_ARRAY_BUFFER, numSprites * 3 * sizeof(float), locations, GL_STATIC_DRAW);
//
//	delete[] locations;
//
//	glGenVertexArrays(1, &sprites);
//	glBindVertexArray(sprites);
//
//	glBindBuffer(GL_ARRAY_BUFFER, handle);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(0);
//
//	const char* texName = "media/texture/flower.png";
//	Texture::loadTexture(texName);
//
//	prog.setUniform("SpriteTex", 0);
//	prog.setUniform("Size2", 0.15f);
//}

////WIREFRAME
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//
//	float c = 1.5f;
//
//	projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f * c, 0.3f * c, 0.1f, 100.0f);
//
//	prog.setUniform("Line.Width", 0.75f);
//	prog.setUniform("Line.Colour", vec4(0.05f,0.0f,0.05f,1.0f));
//	prog.setUniform("Material.Ka", 0.2f,0.2f,0.2f);
//	prog.setUniform("Material.Kd", 0.7f,0.7f,0.7f);
//	prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
//	prog.setUniform("Material.Shininess", 100.0f);
//	prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f));
//	prog.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);
//
//}

////SILHOUETTE
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//
//	angle = glm::half_pi<float>();
//
//	prog.setUniform("EdgeWidth", 0.005f);
//	prog.setUniform("PctExtend", 0.25f);
//	prog.setUniform("LineColour", vec4(1.0f, 1.0f, 1.0f, 1.0f));
//	prog.setUniform("Material.Ka", vec3(0.2f, 0.2f, 0.2f));
//	prog.setUniform("Material.Kd", vec3(0.9f, 0.5f, 0.2f));
//	prog.setUniform("Light.Position", vec4(0.0f,5.0f,-3.0f,1.0f));
//	prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f));	
//}

////SURFACE ANIMATION
//void SceneBasic_Uniform::initScene()
//{
//	compile();
//
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//
//	prog.setUniform("Light.Intensity", vec3(1.0f, 1.0f, 1.0f));
//	prog.setUniform("Light.Position", vec3(0.0f, 1.0f, 1.0f));
//	angle = glm::half_pi<float>();
//}

//SHADOW MAP
void SceneBasic_Uniform::initScene()
{
	compile();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	angle = glm::quarter_pi<float>();

	setupFBO();

	GLuint programHandle = prog.getHandle();
	pass1Index = glGetSubroutineIndex(programHandle, GL_FRAGMENT_SHADER, "recordDepth");
	pass2Index = glGetSubroutineIndex(programHandle, GL_FRAGMENT_SHADER, "shadeWithShadow");

	shadowBias = mat4(vec4(0.5f, 0.0f, 0.0f, 0.0f),
					vec4(0.0f, 0.5f, 0.0f, 0.0f),
					vec4(0.0f, 0.0f, 0.5f, 0.0f),
					vec4(0.0f, 0.0f, 0.0f, 0.5f));

	float c = 1.65f;
	vec3 lightPos = vec3(0.0f, c * 5.25f, c * 7.5f);
	lightFrustrum.orient(lightPos, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	lightFrustrum.setPerspective(50.0f, 1.0f, 1.0f, 25.0f);
	lightPV = shadowBias * lightFrustrum.getProjectionMatrix() * lightFrustrum.getViewMatrix();

	prog.setUniform("Light.Intensity", vec3(0.85f));
	prog.setUniform("ShadowMap", 0);
}

#pragma endregion

#pragma region compile

//void SceneBasic_Uniform::compile()
//{
//	try {
//		prog.compileShader("shader/basic_uniform_Blinn_phong_shadow_map.vert");
//		prog.compileShader("shader/basic_uniform_Blinn_phong_shadow_map.frag");
//		
//
//		prog.link();
//		prog.use();
//	} catch (GLSLProgramException &e) {
//		cerr << e.what() << endl;
//		exit(EXIT_FAILURE);
//	}
//}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform_Blinn_phong_shadow_map.vert");
		prog.compileShader("shader/basic_uniform_Blinn_phong_shadow_map.frag");
		prog.link();
		prog.use();

		solidProg.compileShader("shader/solid.vs", GLSLShader::VERTEX);
		solidProg.compileShader("shader/solid.fs", GLSLShader::FRAGMENT);
		solidProg.link();
	}
	catch (GLSLProgramException& e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

#pragma endregion

#pragma region setMatrices

////WEEK 1-5
//void SceneBasic_Uniform::setMatrices()
//{
//	mat4 mv = view * model;
//
//	prog.setUniform("ModelViewMatrix", mv);
//
//	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]),
//									vec3(mv[1]),
//									vec3(mv[2])));
//
//	prog.setUniform("MVP", projection * mv);
//}

////WIREFRAME
//void SceneBasic_Uniform::setMatrices()
//{
//	mat4 mv = view * model;
//
//	prog.setUniform("ModelViewMatrix", mv);
//	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
//	prog.setUniform("MVP", projection * mv);
//	prog.setUniform("ProjectionMatrix", viewport);
//
//}

////SILHOUETTE
//void SceneBasic_Uniform::setMatrices()
//{
//	mat4 mv = view * model;
//
//	prog.setUniform("ModelViewMatrix", mv);
//	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
//	prog.setUniform("MVP", projection * mv);
//
//}

////SURFACE ANIMATION
//void SceneBasic_Uniform::setMatrices()
//{
//	mat4 mv = view * model;
//
//	prog.setUniform("ModelViewMatrix", mv);
//	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
//	prog.setUniform("MVP", projection * mv);
//
//}

void SceneBasic_Uniform::setMatrices()
{
	mat4 mv = view * model;

	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);
	prog.setUniform("ShadowMatrix", lightPV * model);

}


#pragma endregion

void SceneBasic_Uniform::update( float t )
{
	float deltaT = t - tPrev;
	if (tPrev == 0.0f)
	{
		deltaT = 0.0f;
	}

	tPrev = t;

	angle += 0.2f * deltaT;
	
	if (angle > glm::two_pi<float>())
	{
		angle -= glm::two_pi<float>();		
	}

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

//SHADOWMAP
void SceneBasic_Uniform::render()
{
	prog.use();
	
	view = lightFrustrum.getViewMatrix();
	projection = lightFrustrum.getProjectionMatrix();
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.5f, 10.0f);

	drawScene();
	glCullFace(GL_BACK);

	glFlush();

	float c = 2.0f;

	vec3 cameraPos(c * 11.5f * cos(angle), c * 7.0f, c * 11.5f * sin(angle));
	view = glm::lookAt(cameraPos, vec3(0), vec3(0.0f, 1.0f, 0.0f));
	prog.setUniform("Light.Position", view * vec4(lightFrustrum.getOrigin(), 1.0f));
	projection = glm::perspective(glm::radians(50.0f), (float)width / height, 0.1f, 100.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass2Index);
	drawScene();

	solidProg.use();
	solidProg.setUniform("Colour", vec4(1.0f, 0.0f, 0.0f, 1.0f));
	mat4 mv = view * lightFrustrum.getInverseViewMatrix();
	solidProg.setUniform("MVP", projection * mv);
	lightFrustrum.render();

}

#pragma endregion

#pragma region resize
////WIREFRAME
//void SceneBasic_Uniform::resize(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	float w2 = w / 2.0f;
//	float h2 = w / 2.0f;
//	viewport = mat4(vec4(w2, 0.0f,0.0f,0.0f),
//					  vec4(0.0f,h2, 0.0f, 0.0f),
//					  vec4(0.0f, 0.0f, 1.0f, 0.0f),
//					  vec4(w2 + 0, h2 + 0, 0.0f, 1.0f));
//}

////SILHOUETTE
//void SceneBasic_Uniform::resize(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	float c = 1.5f;
//	projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f * c, 0.3f * c, 0.01f, 100.0f);
//}

////SURFACE ANIMATION
//void SceneBasic_Uniform::resize(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	width = w;
//	height = h;
//	projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
//}

void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	
}

#pragma endregion

#pragma region setupFBO

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

////GAUSSIAN
//void SceneBasic_Uniform::setupFBO() {
//	// Generate and bind the framebuffer
//	glGenFramebuffers(1, &renderFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, renderFBO);
//	// Create the texture object
//	glGenTextures(1, &renderTex);
//	glBindTexture(GL_TEXTURE_2D, renderTex);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
//	// Bind the texture to the FBO
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
//		renderTex, 0);
//	// Create the depth buffer
//	GLuint depthBuf;
//	glGenRenderbuffers(1, &depthBuf);
//	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//	// Bind the depth buffer to the FBO
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//		GL_RENDERBUFFER, depthBuf);
//	// Set the targets for the fragment output variables
//	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
//	glDrawBuffers(1, drawBuffers);
//	// Unbind the framebuffer, and revert to default framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	// Generate and bind the framebuffer
//	glGenFramebuffers(1, &intermediateFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
//	// Create the texture object
//	glGenTextures(1, &intermediateTex);
//	glActiveTexture(GL_TEXTURE0); // Use texture unit 0
//	glBindTexture(GL_TEXTURE_2D, intermediateTex);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
//	// Bind the texture to the FBO
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
//		intermediateTex, 0);
//	// No depth buffer needed for this FBO
//	// Set the targets for the fragment output variables
//	glDrawBuffers(1, drawBuffers);
//	// Unbind the framebuffer, and revert to default framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

////HDR
//void SceneBasic_Uniform::setupFBO()
//{
//	GLuint depthBuf;
//	// Create and bind the FBO
//	glGenFramebuffers(1, &hdrFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//
//	// The depth buffer
//	glGenRenderbuffers(1, &depthBuf);
//	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//
//	// The HDR color buffer
//	glActiveTexture(GL_TEXTURE0);
//	glGenTextures(1, &hdrTex);
//	glBindTexture(GL_TEXTURE_2D, hdrTex);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width, height);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	// Attach the images to the framebuffer
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//		GL_RENDERBUFFER, depthBuf);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
//		hdrTex, 0);
//
//	GLenum drawBuffers[] = { GL_NONE, GL_COLOR_ATTACHMENT0 };
//	glDrawBuffers(2, drawBuffers);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

////BLOOM
//void SceneBasic_Uniform::setupFBO()
//{
//	// Generate and bind the framebuffer
//	glGenFramebuffers(1, &hdrFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//
//	// Create the texture object
//	glGenTextures(1, &hdrTex);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, hdrTex);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width, height);
//
//	// Bind the texture to the FBO
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
//		hdrTex, 0);
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
//	// Create an FBO for the bright-pass filter and blur
//	glGenFramebuffers(1, &blurFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, blurFBO);
//
//	// Create two texture objects to ping-pong for the bright-pass filter
//	// and the two-pass blur
//	bloomBufWidth = width / 8;
//	bloomBufHeight = height / 8;
//	glGenTextures(1, &tex1);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, tex1);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, bloomBufWidth, bloomBufHeight);
//	glActiveTexture(GL_TEXTURE2);
//	glGenTextures(1, &tex2);
//	glBindTexture(GL_TEXTURE_2D, tex2);
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, bloomBufWidth, bloomBufHeight);
//
//	// Bind tex1 to the FBO
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,	tex1, 0);
//	glDrawBuffers(1, drawBuffers);
//
//	// Unbind the framebuffer, and revert to default framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

////DEFERRED
//void SceneBasic_Uniform::setupFBO()
//{
//	GLuint depthBuf, posTex, normTex, colorTex;
//	// Create and bind the FBO
//	glGenFramebuffers(1, &deferredFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
//	// The depth buffer
//	glGenRenderbuffers(1, &depthBuf);
//	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//	// Create the textures for position, normal and color
//	createGBufTex(GL_TEXTURE0, GL_RGB32F, posTex); // Position
//	createGBufTex(GL_TEXTURE1, GL_RGB32F, normTex); // Normal
//	createGBufTex(GL_TEXTURE2, GL_RGB8, colorTex); // Color
//	// Attach the textures to the framebuffer
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//		GL_RENDERBUFFER, depthBuf);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
//		posTex, 0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
//		normTex, 0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
//		colorTex, 0);
//	GLenum drawBuffers[] = { GL_NONE, GL_COLOR_ATTACHMENT0,
//	GL_COLOR_ATTACHMENT1,
//	GL_COLOR_ATTACHMENT2 };
//	glDrawBuffers(4, drawBuffers);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

//SHADOW MAP
void SceneBasic_Uniform::setupFBO()
{

	GLfloat border[] = { 1.0f, 0.0f, 0.0f, 0.0f };

	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, shadowMapWidth, shadowMapHeight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTex);

	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	GLenum drawBuffers[] = { GL_NONE };
	glDrawBuffers(1, drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result == GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Framebuffer is complete.\n");
	}
	else
	{
		printf("Framebuffer is not complete.\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#pragma endregion

#pragma region passes

////EDGE DETECTION & GAUSSIAN BLUR
//void SceneBasic_Uniform::pass1()
//{
//	prog.setUniform("Pass", 1);
//	glBindFramebuffer(GL_FRAMEBUFFER, renderFBO);
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	view = glm::lookAt(vec3(7.0f * cos(angle), 4.0f, 7.0f * sin(angle)),
//		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	projection = glm::perspective(glm::radians(60.0f), (float)width / height,
//		0.3f, 100.0f);
//
//
//	prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
//	prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
//	prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
//	prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
//	prog.setUniform("Material.Shininess", 100.0f);
//	model = mat4(1.0f);
//	model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	teapot.render();
//
//	prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
//	prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
//	prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
//	prog.setUniform("Material.Shininess", 1.0f);
//	model = mat4(1.0f);
//	model = glm::translate(model, vec3(0.0f, -0.75f, 0.0f));
//	setMatrices();
//	plane.render();
//
//	prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
//	prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.2f);
//	prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
//	prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
//	prog.setUniform("Material.Shininess", 100.0f);
//	model = mat4(1.0f);
//	model = glm::translate(model, vec3(1.0f, 1.0f, 3.0f));
//	model = glm::rotate(model, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	torus.render();
//}

////HDR & BLOOM
//void SceneBasic_Uniform::pass1()
//{
//	prog.setUniform("Pass", 1);
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//	glViewport(0, 0, width, height);
//	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//
//	view = glm::lookAt(vec3(2.0f, 0.0f, 14.0f), vec3(0.0f, 0.0f, 0.0f),
//		vec3(0.0f, 1.0f, 0.0f));
//	projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 100.0f);
//
//	drawScene();
//}

////DEFERRED
//void SceneBasic_Uniform::pass1()
//{
//	prog.setUniform("Pass", 1);
//	glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//	view = glm::lookAt(vec3(7.0f * cos(angle), 4.0f, 7.0f * sin(angle)),
//		vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	projection = glm::perspective(glm::radians(60.0f), (float)width / height,
//		0.3f, 100.0f);
//	prog.setUniform("Light.Position", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//	prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
//	model = mat4(1.0f);
//	model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
//	model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	teapot.render();
//	prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
//	model = mat4(1.0f);
//	model = glm::translate(model, vec3(0.0f, -0.75f, 0.0f));
//	setMatrices();
//	plane.render();
//	prog.setUniform("Light.Position", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//	prog.setUniform("Material.Kd", 0.2f, 0.5f, 0.9f);
//	model = mat4(1.0f);
//	model = glm::translate(model, vec3(1.0f, 1.0f, 3.0f));
//	model = glm::rotate(model, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	torus.render();
//	glFinish();
//}

////Edge Detection
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

////GAUSSIAN BLUR
//void SceneBasic_Uniform::pass2()
//{
//	prog.setUniform("Pass", 2);
//	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, renderTex);
//	glDisable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT);
//	model = mat4(1.0f);
//	view = mat4(1.0f);
//	projection = mat4(1.0f);
//	setMatrices();
//	// Render the full-screen quad
//	glBindVertexArray(fsQuad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}

////HDR
//void SceneBasic_Uniform::pass2()
//{
//	prog.setUniform("Pass", 2);
//	// Revert to default framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glDisable(GL_DEPTH_TEST);
//	view = mat4(1.0);
//	model = mat4(1.0);
//	projection = mat4(1.0);
//	setMatrices();
//	// Render the quad
//	glBindVertexArray(quad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}

////BLOOM
//void SceneBasic_Uniform::pass2()
//{
//	prog.setUniform("Pass", 2);
//	glBindFramebuffer(GL_FRAMEBUFFER, blurFBO);
//
//	// We're writing to tex1 this time
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex1, 0);
//	glViewport(0, 0, bloomBufWidth, bloomBufHeight);
//	glDisable(GL_DEPTH_TEST);
//	glClearColor(0, 0, 0, 0);
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
//}

////DEFERRED
//void SceneBasic_Uniform::pass2()
//{
//	prog.setUniform("Pass", 2);
//	// Revert to default framebuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glDisable(GL_DEPTH_TEST);
//	view = mat4(1.0);
//	model = mat4(1.0);
//	projection = mat4(1.0);
//	setMatrices();
//	// Render the quad
//	glBindVertexArray(quad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}

//GAUSSIAN BLUR(?)
//void SceneBasic_Uniform::pass3()
//{
//	prog.setUniform("Pass", 3);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, intermediateTex);
//	glClear(GL_COLOR_BUFFER_BIT);
//	model = mat4(1.0f);
//	view = mat4(1.0f);
//	projection = mat4(1.0f);
//	setMatrices();
//	// Render the full-screen quad
//	glBindVertexArray(fsQuad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}

////BLOOM
//void SceneBasic_Uniform::pass3()
//{
//	prog.setUniform("Pass", 3);
//
//	// We're writing to tex2 this time
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,	tex2, 0);
//
//	// Render the full-screen quad
//	glBindVertexArray(fsQuad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}

////BLOOM
//void SceneBasic_Uniform::pass4()
//{
//	prog.setUniform("Pass", 4);
//
//	// We're writing to tex1 this time
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,	tex1, 0);
//
//	// Render the full-screen quad
//	glBindVertexArray(fsQuad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}

////BLOOM
//void SceneBasic_Uniform::pass5()
//{
//	prog.setUniform("Pass", 5);
//
//	// Bind to the default framebuffer, this time we're going to
//	// actually draw to the screen!
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glViewport(0, 0, width, height);
//
//	// In this pass, we're reading from tex1 (unit 1) and we want
//	// linear sampling to get an extra blur
//	glBindSampler(1, linearSampler);
//
//	// Render the full-screen quad
//	glBindVertexArray(fsQuad);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//
//	// Revert to nearest sampling
//	glBindSampler(1, nearestSampler);
//}

#pragma endregion
////GAUSSIAN BLUR & BLOOM
//float SceneBasic_Uniform::gauss(float x, float sigma2)
//{
//	double coeff = 1.0 / (glm::two_pi<double>() * sigma2);
//	double expon = -(x * x) / (2.0 * sigma2);
//	return (float)(coeff * exp(expon));
//}

////HDR & BLOOM
//void SceneBasic_Uniform::computeLogAveLuminance()
//{
//	int size = width * height;
//
//	std::vector<GLfloat> texData(size * 3);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, hdrTex);
//	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, texData.data());
//
//	float sum = 0.0f;
//
//	for (int i = 0; i < size; i++) {
//		float lum = glm::dot(vec3(texData[i * 3 + 0], texData[i * 3 + 1],
//			texData[i * 3 + 2]),
//			vec3(0.2126f, 0.7152f, 0.0722f));
//		sum += logf(lum + 0.00001f);
//	}
//
//	prog.setUniform("AveLum", expf(sum / size));
//}

////DEFERRED
//void SceneBasic_Uniform::createGBufTex(GLenum texUnit, GLenum format, GLuint & texid)
//{
//	glActiveTexture(texUnit);
//	glGenTextures(1, &texid);
//	glBindTexture(GL_TEXTURE_2D, texid);
//	glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
//}

#pragma region drawScene

////HDR & BLOOM
//void SceneBasic_Uniform::drawScene()
//{
//	vec3 intense = vec3(1.0f);
//	prog.setUniform("Lights[0].L", intense);
//	prog.setUniform("Lights[1].L", intense);
//	prog.setUniform("Lights[2].L", intense);
//
//	vec4 lightPos = vec4(0.0f, 4.0f, 2.5f, 1.0f);
//	lightPos.x = -7.0f;
//	prog.setUniform("Lights[0].Position", view * lightPos);
//	lightPos.x = 0.0f;
//	prog.setUniform("Lights[1].Position", view * lightPos);
//	lightPos.x = 7.0f;
//	prog.setUniform("Lights[2].Position", view * lightPos);
//
//	prog.setUniform("Material.Kd", 0.9f, 0.3f, 0.2f);
//	prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f);
//	prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
//	prog.setUniform("Material.Shininess", 100.0f);
//
//	// The backdrop plane
//	model = glm::rotate(mat4(1.0f), glm::radians(90.0f), vec3(1.0f, 0.0f,
//		0.0f));
//	setMatrices();
//	plane.render();
//
//	// The bottom plane
//	model = glm::translate(mat4(1.0f), vec3(0.0f, -5.0f, 0.0f));
//	setMatrices();
//	plane.render();
//
//	// Top plane
//	model = glm::translate(mat4(1.0f), vec3(0.0f, 5.0f, 0.0f));
//	model = glm::rotate(model, glm::radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	plane.render();
//
//	prog.setUniform("Material.Kd", vec3(0.4f, 0.9f, 0.4f));
//	model = glm::translate(mat4(1.0f), vec3(-3.0f, -3.0f, 2.0f));
//	setMatrices();
//	sphere.render();
//
//	prog.setUniform("Material.Kd", vec3(0.4f, 0.4f, 0.9f));
//	model = glm::translate(mat4(1.0f), vec3(3.0f, -5.0f, 1.5f));
//	model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
//	setMatrices();
//	teapot.render();
//}

//SHADOW MAP
void SceneBasic_Uniform::drawScene()
{
	vec3 colour = vec3(0.2f, 0.5f, 0.9f);
	prog.setUniform("Material.Ka", colour * 0.05f);
	prog.setUniform("Material.Kd", colour);
	prog.setUniform("Material.Ks", vec3(0.9f));
	prog.setUniform("Material.Shininess", 150.0f);
	model = mat4(1.0f);

	setMatrices();
	teapot.render();


	prog.setUniform("Material.Ka", colour * 0.05f);
	prog.setUniform("Material.Kd", colour);
	prog.setUniform("Material.Ks", vec3(0.9f));
	prog.setUniform("Material.Shininess", 150.0f);
	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	torus.render();

	prog.setUniform("Material.Ka", vec3(0.05f));
	prog.setUniform("Material.Kd", vec3(0.25f));
	prog.setUniform("Material.Ks", vec3(0.0f));
	prog.setUniform("Material.Shininess", 1.0f);
	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, 2.0f, 5.0f));
	model = glm::rotate(model, glm::radians(-45.0f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	plane.render();

	model = mat4(1.0f);
	model = glm::translate(model, vec3(-5.0f, 5.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));
	setMatrices();
	plane.render();

	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, 5.0f, -5.0f));
	model = glm::rotate(model, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	plane.render();
	model = mat4(1.0f);

}

#pragma endregion