#include "model.h"
#include "math.h"
#include <limits>

#include <QDebug>
#include <QFile>
#include <QTextStream>

Model::Model(QString filename) {
    qDebug() << ":: Loading model:" << filename;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        QString line;
        QStringList tokens;

        while(!in.atEnd()) {
            line = in.readLine();
            if (line.startsWith("#")) continue; // skip comments

            tokens = line.split(" ", QString::SkipEmptyParts);

            // Switch depending on first element
            if (tokens[0] == "v") {
                parseVertex(tokens);
            }

            if (tokens[0] == "vn" ) {
                parseNormal(tokens);
            }

            if (tokens[0] == "vt" ) {
                parseTexture(tokens);
            }

            if (tokens[0] == "f" ) {
                parseFace(tokens);
            }
        }

        file.close();

        // create an array version of the data
        unpackIndexes();

        // Allign all vertex indices with the right normal/texturecoord indices
        alignData();
    }
}

/**
 * @brief Model::unitze Not Implemented yet!
 *
 * Unitize the model by scaling so that it fits a box with sides 1
 * and origin at 0,0,0
 * Usefull for models with different scales
 *
 */
void Model::unitize() {
    float boundingBoxTargetSize = 5;

    // Find points for bounding box
    QVector3D p1 = QVector3D(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    QVector3D p2 = QVector3D(0.0, 0.0, 0.0);

    // find bounding box enclosed by p1 and p2
    for (int i = 0; i < vertices.size(); ++i)
    {
        QVector3D v = vertices.at(i);
        p1.setX(std::min(v.x(), p1.x()));
        p1.setY(std::min(v.y(), p1.y()));
        p1.setZ(std::min(v.z(), p1.z()));

        p2.setX(std::max(v.x(), p2.x()));
        p2.setY(std::max(v.y(), p2.y()));
        p2.setZ(std::max(v.z(), p2.z()));
    }

    // Find longest of width, depth and height
    float longestEdge = 0.0f;
    QVector3D dimensions = QVector3D(fabs(p1.x() - p2.x()), fabs(p1.y() - p2.y()), fabs(p1.z() - p2.z()));

    longestEdge = std::max(dimensions.x(), dimensions.y());
    longestEdge = std::max(longestEdge, dimensions.z());

    // Find scaling factor and create scaling matrix
    QMatrix4x4 meshTransform;
    meshTransform.setToIdentity();
    float sizeMultiplier = boundingBoxTargetSize / longestEdge;

    meshTransform.scale(sizeMultiplier);

    // Find middle of bounding box and add this transformation to matrix
    QVector3D origin = p1 + dimensions * 0.5;
    meshTransform.translate(-origin);

    // Set the matrices
    QVector<QVector3D> verts = QVector<QVector3D>();
    verts.reserve(vertices.size());
    QVector<QVector3D> verts_indexed = QVector<QVector3D>();
    verts_indexed.reserve(vertices_indexed.size());

    for (int i = 0; i < vertices.size(); ++i) {
        verts.append(meshTransform * vertices.at(i));
    }

    for (int i = 0; i < vertices_indexed.size(); ++i) {
        verts_indexed.append(meshTransform * vertices_indexed.at(i));
    }

    vertices.clear();
    vertices = verts;
    vertices_indexed.clear();
    vertices_indexed = verts_indexed;
}

void Model::subdivide() {
}

QVector<QVector3D> Model::getVertices() {
    return vertices;
}

QVector<QVector3D> Model::getNormals() {
    return normals;
}

QVector<QVector2D> Model::getTextureCoords() {
    return textureCoords;
}

QVector<QVector3D> Model::getVertices_indexed() {
    return vertices_indexed;
}

QVector<QVector3D> Model::getNormals_indexed() {
    return normals_indexed;
}

QVector<QVector2D> Model::getTextureCoords_indexed() {
    return textureCoords_indexed;
}

QVector<unsigned>  Model::getIndices() {
    return indices;
}

QVector<float> Model::getVNInterleaved() {
    QVector<float> buffer;

    for (int i = 0; i != vertices.size(); ++i) {
        QVector3D vertex = vertices.at(i);
        QVector3D normal = normals.at(i);
        append3dToBuffer(vertex, &buffer);
        append3dToBuffer(normal, &buffer);
    }

    return buffer;
}

QVector<float> Model::getVNTInterleaved() {
    QVector<float> buffer;

    for (int i = 0; i != vertices.size(); ++i) {
        QVector3D vertex = vertices.at(i);
        QVector3D normal = normals.at(i);
        QVector2D uv = textureCoords.at(i);

        append3dToBuffer(vertex, &buffer);
        append3dToBuffer(normal, &buffer);
        buffer.append(uv.x());
        buffer.append(uv.y());
    }

    return buffer;
}

// Throws when there are no normals or texture values
QVector<float> Model::getVNInterleaved_indexed() {
    QVector<float> buffer;

    for (int i = 0; i != vertices_indexed.size(); ++i) {
        QVector3D vertex = vertices_indexed.at(i);
        QVector3D normal = normals_indexed.at(i);
        append3dToBuffer(vertex, &buffer);
        append3dToBuffer(normal, &buffer);
    }

    return buffer;
}

// Throws when there are no normals or texture values
QVector<float> Model::getVNTInterleaved_indexed() {
    QVector<float> buffer;

    for (int i = 0; i != vertices_indexed.size(); ++i) {
        QVector3D vertex = vertices_indexed.at(i);
        QVector3D normal = normals_indexed.at(i);
        QVector2D uv = textureCoords_indexed.at(i);
        append3dToBuffer(vertex, &buffer);
        append3dToBuffer(normal, &buffer);
        buffer.append(uv.x());
        buffer.append(uv.y());
    }

    return buffer;
}

/**
 * @brief Model::getNumTriangles
 *
 * Gets the number of triangles in the model
 *
 * @return number of triangles
 */
int Model::getNumTriangles() {
    return vertices.size()/3;
}

void Model::parseVertex(QStringList tokens) {
    float x,y,z;
    x = tokens[1].toFloat();
    y = tokens[2].toFloat();
    z = tokens[3].toFloat();
    vertices_indexed.append(QVector3D(x,y,z));
}

void Model::parseNormal(QStringList tokens) {
    hNorms = true;
    float x,y,z;
    x = tokens[1].toFloat();
    y = tokens[2].toFloat();
    z = tokens[3].toFloat();
    norm.append(QVector3D(x,y,z));
}

void Model::parseTexture(QStringList tokens) {
    hTexs = true;
    float u,v;
    u = tokens[1].toFloat();
    v = tokens[2].toFloat();
    tex.append(QVector2D(u,v));
}

void Model::append3dToBuffer(QVector3D vector, QVector<float> *buffer) {
    buffer->append(vector.x());
    buffer->append(vector.y());
    buffer->append(vector.z());
}

void Model::parseFace(QStringList tokens) {
    QStringList elements;

    for( int i = 1; i != tokens.size(); ++i ) {
        elements = tokens[i].split("/");
        // -1 since .obj count from 1
        indices.append(elements[0].toInt()-1);

        if ( elements.size() > 1 && ! elements[1].isEmpty() ) {
            texcoord_indices.append(elements[1].toInt()-1);
        }

        if (elements.size() > 2 && ! elements[2].isEmpty() ) {
            normal_indices.append(elements[2].toInt()-1);
        }
    }
}


/**
 * @brief Model::alignData
 *
 * Make sure that the indices from the vertices align with those
 * of the normals and the texture coordinates, create extra vertices
 * if vertex has multiple normals or texturecoords
 */
void Model::alignData() {
    QVector<QVector3D> verts = QVector<QVector3D>();
    verts.reserve(vertices_indexed.size());
    QVector<QVector3D> norms = QVector<QVector3D>();
    norms.reserve(vertices_indexed.size());
    QVector<QVector2D> texcs = QVector<QVector2D>();
    texcs.reserve(vertices_indexed.size());
    QVector<Vertex> vs = QVector<Vertex>();

    QVector<unsigned> ind = QVector<unsigned>();
    ind.reserve(indices.size());

    unsigned currentIndex = 0;

    for (int i = 0; i != indices.size(); ++i) {
        QVector3D v = vertices_indexed[indices[i]];

        QVector3D n = QVector2D(0,0);
        if ( hNorms ) {
            n = norm[normal_indices[i]];
        }

        QVector2D t = QVector2D(0,0);
        if ( hTexs ) {
            t = tex[texcoord_indices[i]];
        }

        Vertex k = Vertex(v,n,t);
        if (vs.contains(k)) {
            // Vertex already exists, use that index
            ind.append(vs.indexOf(k));
        } else {
            // Create a new vertex
            verts.append(v);
            norms.append(n);
            texcs.append(t);
            vs.append(k);
            ind.append(currentIndex);
            ++currentIndex;
        }
    }
    // Remove old data
    vertices_indexed.clear();
    normals_indexed.clear();
    textureCoords_indexed.clear();
    indices.clear();

    // Set the new data
    vertices_indexed = verts;
    normals_indexed = norms;
    textureCoords_indexed = texcs;
    indices = ind;
}

/**
 * @brief Model::unpackIndexes
 *
 * Unpack indices so that they are available for glDrawArrays()
 *
 */
void Model::unpackIndexes() {
    vertices.clear();
    normals.clear();
    textureCoords.clear();
    for ( int i = 0; i != indices.size(); ++i ) {
        vertices.append(vertices_indexed[indices[i]]);

        if ( hNorms ) {
            normals.append(norm[normal_indices[i]]);
        }

        if ( hTexs ) {
            textureCoords.append(tex[texcoord_indices[i]]);
        }
    }
}
