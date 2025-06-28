#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Utility.h"

class Scene;

class Object
{
public:
    unsigned int id;
    std::string name;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    
    Vector3 globalPosition;
    Vector3 globalRotation;
    Vector3 globalScale;
    Object *parent;
    std::vector<Object *> children;

    Object();
    ~Object();

    virtual void Start();
    virtual void Update(float deltaTime, GLFWwindow* window);
    virtual void FixedUpdate(float fixedDeltaTime, GLFWwindow* window);

    void SetParent(Object *newParent);

private:
    static unsigned int nextId;
};

#endif
