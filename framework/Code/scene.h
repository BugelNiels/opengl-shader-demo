#ifndef SCENE_H
#define SCENE_H

#include <QVector3D>

#include "mesh.h"
#include "cubemap.h"

typedef struct ObjectCollection {

    // Light information
    QVector3D lightPos;
    QVector3D lightColor;

    // Cube map
    CubeMap cubeMap;

    // Mesh info
    QVector<Mesh> objects;
    int selectedObjectIndex;

    // Camera info
    QVector3D cameraMovement;
    QVector3D currentMovement;
    float cameraRotation;
    float currentRotation;

    bool animation;
    bool wireframe;
} *Scene;

#endif // SCENE_H
