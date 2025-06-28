#include <GUSEGE/Scene.h>
#include <GUSEGE/Object.h>
#include <GUSEGE.h>
#include <GLFW/glfw3.h>

Camera *Scene::mainCamera = nullptr;
std::vector<Object*> Scene::objects;
Object *Scene::selectedObject = nullptr;

void ApplyGlobalTransforms(Object* object) {
    Object* current = object;

    object->globalPosition = Vector3();
    object->globalRotation = Vector3();
    object->globalScale = Vector3();

    

    while (current != nullptr)
    {
        object->globalPosition += current->position;
        object->globalRotation += current->rotation;
        object->globalScale += current->scale;

        current = current->parent;
    }
}


void Scene::Update()
{
    for (auto &object : objects)
    {
        //ApplyGlobalTransforms(object);
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