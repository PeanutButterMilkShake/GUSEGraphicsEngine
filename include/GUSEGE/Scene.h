#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "UBO.h"
#include <vector>
#include <memory>

class Object;

class Scene
{
public:
    static const int MAX_LIGHTS = 100; // Maximum number of lights in the scene
    static Camera *mainCamera;
    static std::vector<Object*> objects;
    static Object *selectedObject;

    static void Init();
    static void UpdateLightUBO();
    static void Update();
    static void FixedUpdate();
    static void SelectObject(Object *object)
    {
        if (object == nullptr)
        {
            std::cerr << "No object to be selected" << std::endl;
            return;
        }
        selectedObject = object;
    }
    Scene();
    ~Scene();

private:
};

#endif