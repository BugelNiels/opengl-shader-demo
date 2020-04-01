#include "mainview.h"

/**
 * @brief MainView::initializeScene
 * Initialises all objects in the scene with their respective animations and attributes
 */
void MainView::initializeScene1() {
    Scene scene = new struct ObjectCollection;

    scene->lightPos = QVector3D(0.0f, 30.0f, 100.0f);
    scene->lightColor = QVector3D(1.0f, 1.0f, 1.0f);

    scene->animation = false;
    scene->selectedObjectIndex = 0;
    scene->wireframe = false;

    scene->cameraMovement = {0.0f, 0.0f, 0.0f};
    scene->cameraRotation = 0.0f;
    scene->currentMovement = QVector3D(0, 0, 0);
    scene->currentRotation = 0;


    addCubeMap("lake", scene);

    addObject("helmet", scene);
    Mesh mesh = scene->objects[0];
    QVector<QString> tex;
    tex.append(":/textures/" + mesh->name + "_diff.png");
    tex.append(":/textures/" + mesh->name + "_spec.png");
    tex.append(":/textures/" + mesh->name + "_norm.png");
    mesh->images = tex;


    scenes.append(scene);
}

/**
 * @brief MainView::initializeScene
 * Initialises all objects in the scene with their respective animations and attributes
 */
void MainView::initializeScene2() {
    Scene scene = new struct ObjectCollection;

    scene->lightPos = QVector3D(0.0f, 0.0f, 100.0f);
    scene->lightColor = QVector3D(1.0f, 1.0f, 1.0f);

    scene->animation = false;
    scene->selectedObjectIndex = 0;
    scene->wireframe = false;


    addObject("grid", scene);
    Mesh grid = scene->objects[0];
    grid->animations.append(BOUNCE);
    grid->shaderIndex = WATER;

    scenes.append(scene);
}

void MainView::addCubeMap(QString name, Scene scene) {
    CubeMap c = new struct cubeMap;
    c->name = name;

    c->initialRotation = {0, 0, 0};
    c->initialPosition = {0, 0, 0};
    c->rotation = {0.0f, 1.0f, 0.0f};
    c->modelTransform.setToIdentity();
    c->modelTransform.scale(1);
    scene->cubeMap = c;
}


/**
 * @brief MainView::addObject
 * Adds an object, initialised with some default values
 *
 * @param name The name of the mesh to load
 */
void MainView::addObject(QString name, Scene scene) {
    Mesh m = new struct Object;
    m->id = name + "." + QString::number(id);
    m->name = name;
    m->textureSuccess.append(false);
    m->textureSuccess.append(false);
    m->textureSuccess.append(false);

    m->initialRotation = {0, 0, 0};
    m->initialPosition = {0, 0, 0};
    m->animationTransform.setToIdentity();
    m->rotation = {0.0f, 1.0f, 0.0f};
    m->scale = 1.0f;
    m->shaderIndex = 0;
    m->usingDiffuseTexture = 0;
    m->usingSpecularMap = 0;
    m->usingNormalMap = 0;
    m->selected = false;

    // Animation default values;
    m->rotationSpeed = (rand() % 50 + 50)/50.0f;
    m->rotationAngle = 0;
    m->frequency = 0.04f;
    m->amplitude = 2;
    m->time = 0;
    m->maxScale = 0.4f;
    m->pos = 0;
    m->glideSpeed = 0.1f;
    m->growSpeed = 0.01f;

    // Material parameters
    m->ambientCoefficient = 0.3f;
    m->diffuseCoefficient = 0.7f;
    m->specularCoefficient = 1.0f;
    m->specularExponent = 32;
    m->materialColor = {0.5f, 0.5f, 0.5f};

    scene->objects.append(m);
}

/**
 * @brief MainView::loadTexture
 * Loads a texture
 *
 * @param file path of the texture
 * @param index texture index
 */
void MainView::loadTexture(Mesh mesh, QString file, int index) {

    QImage image(file);
    if(image.isNull()) {
        mesh->textureSuccess[index] = false;
    } else {
        mesh->textureSuccess[index] = true;
    }
    QVector<quint8> bytes = imageToBytes(image);
    setTextureParameters(mesh, index);

    // Optionally enable anisotropic filtering
    if(anisotropicFiltering) {
        GLfloat f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &f);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, f);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 6);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

/**
 * @brief MainView::setTextureParameters
 * Updates/sets the texture parameters
 *
 * @param index The index of the texture whose parameters we need to update
 */
void MainView::setTextureParameters(Mesh mesh, int index) {
    glBindTexture(GL_TEXTURE_2D, mesh->textures[index]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
}

void MainView::loadMeshTextures(Mesh mesh) {
    // Load in the diffuse, specular and normal textures

    GLint numTextures = mesh->images.size();
    for(int i = 0; i < numTextures; i++) {
        GLuint texInt;
        mesh->textures.append(texInt);
    }
    glGenTextures(numTextures, mesh->textures.data());
    for (int i = 0; i < numTextures; i++) {
        loadTexture(mesh, mesh->images[i], i);
    }
}

GLuint MainView::loadCubeMapTexture(QVector<QString> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < faces.size(); i++) {
        QImage image(faces[i]);
        QVector<quint8> bytes = imageToBytes(image);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes.data());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void MainView::loadCubeMap(CubeMap cMap) {
    Model model(":/models/cube.obj");
    model.unitize();

    QVector<QString> faces;
    faces.append(":/textures/" + cMap->name + "_posx.jpg");
    faces.append(":/textures/" + cMap->name + "_negx.jpg");
    faces.append(":/textures/" + cMap->name + "_posy.jpg");
    faces.append(":/textures/" + cMap->name + "_negy.jpg");
    faces.append(":/textures/" + cMap->name + "_posz.jpg");
    faces.append(":/textures/" + cMap->name + "_negz.jpg");

    cMap->cubeTextures = loadCubeMapTexture(faces);

    QVector<QVector3D> vertexCoords = model.getVertices();

    QVector<float> meshData = model.getVNTInterleaved();

    cMap->size = vertexCoords.size();

    // Generate VAO
    glGenVertexArrays(1, &(cMap->VAO));
    glBindVertexArray(cMap->VAO);

    // Generate VBO
    glGenBuffers(1, &(cMap->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, cMap->VBO);

    // Write the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), meshData.data(), GL_STATIC_DRAW);

    // coordinates(3), normals(3), texture coordinates(2)
    unsigned long vertexSize = 8;

    // Set vertex coordinates to location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Set normal coordinates to location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set uv to location 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
 * @brief MainView::loadMesh
 * Loads a mesh
 */
void MainView::loadMesh(Mesh mesh) {
    Model model(":/models/" + mesh->name + ".obj");
    model.unitize();

    loadMeshTextures(mesh);

    QVector<QVector3D> vertexCoords = model.getVertices();

    QVector<float> meshData = model.getVNTInterleaved();

    mesh->size = vertexCoords.size();

    // Generate VAO
    glGenVertexArrays(1, &(mesh->VAO));
    glBindVertexArray(mesh->VAO);

    // Generate VBO
    glGenBuffers(1, &(mesh->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    // Write the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), meshData.data(), GL_STATIC_DRAW);

    // coordinates(3), normals(3), texture coordinates(2)
    unsigned long vertexSize = 8;

    // Set vertex coordinates to location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Set normal coordinates to location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set uv to location 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
