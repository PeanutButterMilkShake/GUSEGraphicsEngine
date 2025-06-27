#include <GUSEGE/Scene.h>
#include <GUSEGE/Object.h>
#include <GUSEGE.h>
#include <GLFW/glfw3.h>

Camera *Scene::mainCamera = nullptr;
std::vector<Object*> Scene::objects;
Object *Scene::selectedObject = nullptr;

void Scene::Update()
{
    for (auto &object : objects)
    {
        object->Update(GUSEGE::deltaTime, GUSEGE::GetWindow());
    }
}

void Scene::FixedUpdate()
{
    for (auto &object : objects)
    {
        object->FixedUpdate(0.0f, GUSEGE::GetWindow());
    }
}

void Scene::Init()
{
    for (auto &object : objects)
    {
        object->Start();
    }
}

Scene::Scene()
{
}

Scene::~Scene()
{
}