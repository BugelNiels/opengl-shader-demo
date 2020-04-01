#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>

struct Vertex
{
    QVector3D coords;
    QVector3D normal;
    QVector2D uv;
    QVector3D tangent;
    QVector3D bitangent;

    Vertex(QVector3D coords, QVector3D normal, QVector2D uv, QVector3D tangent, QVector3D bitangent)
        :
          coords(coords),
          normal(normal),
          uv(uv),
          tangent(tangent),
          bitangent(bitangent)
    {}
};

#endif // VERTEX_H

