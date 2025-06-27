#include <GUSEGE/Object.h>
#include <GUSEGE/Scene.h>
#include <GLFW/glfw3.h>

unsigned int Object::nextId = 1;

Object::Object()
{
    Scene::objects.push_back(this);
    scale = Vector3(1.0f, 1.0f, 1.0f);
    position = Vector3(0.0f, 0.0f, 0.0f);
    rotation = Vector3(0.0f, 0.0f, 0.0f);
    id = nextId++;
}

Object::~Object()
{

}

void Object::Start()
{
}

void Object::Update(float deltaTime, GLFWwindow* window)
{
}

void Object::FixedUpdate(float fixedDeltaTime, GLFWwindow* window)
{
}