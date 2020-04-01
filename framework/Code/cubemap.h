#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QMatrix4x4>

typedef struct cubeMap {
    QString name;
    GLuint VAO;
    GLuint VBO;
    GLint size;
    QMatrix4x4 modelTransform;
    QVector3D rotation;

    QVector3D initialRotation;
    QVector3D initialPosition;

    GLuint cubeTextures;
} *CubeMap;

#endif // CUBEMAP_H
