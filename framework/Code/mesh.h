#ifndef MESH_H
#define MESH_H
#define M_PI 3.141593

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QMatrix4x4>
#include <memory>
#include <math.h>

typedef struct Object{
    QString id;

    QString name;
    GLuint VAO;
    GLuint VBO;
    GLint size;
    QMatrix4x4 modelTransform;
    QVector3D rotation;

    QVector3D initialRotation;
    QVector3D initialPosition;

    QMatrix4x4 animationTransform;

    QVector<GLuint> animations;

    QVector<QString> images;

    // Animation parameters

    float rotationSpeed;
    float rotationAngle;
    float time;
    float amplitude;
    float maxScale;
    float frequency;
    float scale;
    float growSpeed;
    float pos;
    float glideSpeed;

    // Material parameters

    float ambientCoefficient;
    float diffuseCoefficient;
    float specularCoefficient;
    float specularExponent;

    int usingDiffuseTexture;
    int usingSpecularMap;
    int usingNormalMap;

    QVector3D materialColor;

    GLuint shaderIndex;

    QVector<GLuint> textures;
    QVector<bool> textureSuccess;

    bool selected;
} *Mesh;

static void shake(Mesh mesh) {
    float offset = mesh->amplitude * sin(3 * M_PI * mesh->frequency * mesh->time);
    mesh->animationTransform.translate(offset, 0, 0);
}

static void bounce(Mesh mesh) {

    float height = mesh->amplitude * sin(2 * M_PI * mesh->frequency * mesh->time);
    mesh->animationTransform.translate(0, height, 0);
}

static void rotate(Mesh mesh) {

    mesh->rotationAngle += mesh->rotationSpeed;
    mesh->animationTransform.rotate(mesh->rotationAngle, 1, 0, 0);
}

static void inflate(Mesh mesh) {

    mesh->scale += mesh->growSpeed;
    mesh->animationTransform.scale(mesh->scale);
}

static void breathe(Mesh mesh) {
    float scale = mesh->maxScale * sin(2 * M_PI * mesh->frequency * mesh->time) + 1;
    mesh->animationTransform.scale(scale);
}

static void glide(Mesh mesh) {
    QVector3D newPos = {mesh->pos, 0,0};
    mesh->animationTransform.translate(newPos);
    mesh->pos += mesh->glideSpeed;
}

#endif // MESH_H
