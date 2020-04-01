#include "mainview.h"
#include "model.h"
#include "vertex.h"

#include <QDateTime>


/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";
    viewRotation.setToIdentity();

    initializeScene1();

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    qDebug() << "MainView destructor";

    makeCurrent();

    for(int i = 0; i < shaders.size(); i++) {
        shaders[i]->removeAllShaders();
        free(shaders[i]);
    }
    for(Scene s : scenes) {
        for(Mesh mesh : s->objects) {
            destroyModelBuffers(mesh);
            free(mesh);
        }
        free(s);
    }
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    connect(&debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)),
            this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if (debugLogger.initialize()) {
        qDebug() << ":: Logging initialized";
        debugLogger.startLogging(QOpenGLDebugLogger::SynchronousLogging);
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Disable backface culling
    glDisable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Set the color to be used by glClear. This is, effectively, the background color.
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    createShaderProgram();
    for(Scene s : scenes) {
        loadCubeMap(s->cubeMap);
        for(int i = 0; i < s->objects.size(); i++) {
            loadMesh(s->objects[i]);
        }
    }

    // Initialize transformations
    viewTransform.setToIdentity();
    updateProjectionTransform();
    for(Scene s : scenes) {
        for(int i = 0; i < s->objects.size(); i++) {
            updateModelTransforms(s->objects[i]);
        }
    }

    // Start timer for animation
    timer.start(1000.0 / 60.0);
}

/**
 * @brief MainView::addShaderProgram
 * Adds a shader program, both vertex and fragment shader
 *
 * @param name Name of the shader program
 */
void MainView::addShaderProgram(QString name) {
    QString pathVert = ":/shaders/vertshader_" + name + ".glsl";
    QString pathFrag = ":/shaders/fragshader_" + name + ".glsl";

    shaders.append(new QOpenGLShaderProgram());
    shaders.back()->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           pathVert);
    shaders.back()->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           pathFrag);
    shaders.back()->link();
}

/**
 * @brief MainView::updateShaderProgram
 *
 * @param newIndex The index of the new shader program
 */
void MainView::updateShaderProgram(int shaderIndex) {

    // Uniform for texture maps
    uniformUV = shaders[shaderIndex]->uniformLocation("textureColor");
    uniformSpecularMap = shaders[shaderIndex]->uniformLocation("specularMap");
    uniformNormalMap = shaders[shaderIndex]->uniformLocation("normalMap");

    // Uniforms for whether diffuse, specular and normal maps need to be used
    uniformUsingDiff = shaders[shaderIndex]->uniformLocation("useDiff");
    uniformUsingSpec = shaders[shaderIndex]->uniformLocation("useSpec");
    uniformUsingNorm = shaders[shaderIndex]->uniformLocation("useNorm");

    uniformViewTransform = shaders[shaderIndex]->uniformLocation("viewTransform");
    uniformModelTransform = shaders[shaderIndex]->uniformLocation("modelTransform");


    // Uniforms for specular and normal multiplier
    uniformSpecularMultiplier = shaders[shaderIndex]->uniformLocation("specularMultiplier");
    uniformNormalMultiplier = shaders[shaderIndex]->uniformLocation("normalMultiplier");

    // Uniforms for transform matrices
    uniformModelViewTransform =  shaders[shaderIndex]->uniformLocation("modelViewTransform");
    uniformProjectionTransform =  shaders[shaderIndex]->uniformLocation("projectionTransform");
    uniformNormTransform =  shaders[shaderIndex]->uniformLocation("normTransform");

    // Uniforms for light and material information
    uniformLightPos = shaders[shaderIndex]->uniformLocation("lightPos");
    uniformLightColor = shaders[shaderIndex]->uniformLocation("lightColor");
    uniformMaterialColor = shaders[shaderIndex]->uniformLocation("materialColor");
    uniformLightingConstants = shaders[shaderIndex]->uniformLocation("lightingConstants");

    uniformAmplitudes = shaders[shaderIndex]->uniformLocation("amplitudes");
    uniformFrequencies = shaders[shaderIndex]->uniformLocation("frequencies");
    uniformPhases = shaders[shaderIndex]->uniformLocation("phases");
    uniformTime = shaders[shaderIndex]->uniformLocation("time");

    uniformSelected = shaders[shaderIndex]->uniformLocation("selected");
}

void MainView::createShaderProgram() {
//    shaders.clear();
    // Create shader program
    addShaderProgram("phong");
    addShaderProgram("normal");
    addShaderProgram("gouraud");
    addShaderProgram("water");
    addShaderProgram("realism");
    addShaderProgram("cubemap");

    // Get the uniforms, set phong (index 0) as default
    updateShaderProgram(0);
}

/**
 * @brief MainView::setGlobalUniforms
 * Sets the uniforms that are independent of a mesh
 */
void MainView::setGlobalUniforms() {

    // Set multipliers for specular and normal
    glUniform1f(uniformSpecularMultiplier, specularMultiplier);
    glUniform1f(uniformNormalMultiplier, normalMultiplier);

    // Set values for wave function
    float amplitudes[4] = {0.02f, 0.04f, 0.01f, 0.03f};
    glUniform1fv(uniformAmplitudes, 4, amplitudes);
    float frequences[4] = {20, 6, 12, 8};
    glUniform1fv(uniformFrequencies, 4, frequences);
    float phases[4] = {0.5f, 1.5f, 0.3f, 2.1f};
    glUniform1fv(uniformPhases, 4, phases);
    glUniform1f(uniformTime, time);

    // Set the matrices
    glUniformMatrix4fv(uniformProjectionTransform, 1, GL_FALSE, projectionTransform.data());
}

/**
 * @brief MainView::animateMesh
 * Perform animation on mesh
 *
 * @param mesh The mesh that is being animated
 */
void MainView::animateMesh(Mesh mesh) {
    Scene s = scenes[currentSceneIndex];
    if(s->animation && mesh->animations.size() > 0){
        mesh->animationTransform.setToIdentity();
        for(GLuint animationType : mesh->animations) {
            switch(animationType) {
                case ROTATE:
                    rotate(mesh);
                    break;
                case BOUNCE:
                    bounce(mesh);
                    break;
                case BREATHE:
                    breathe(mesh);
                    break;
                case INFLATE:
                    inflate(mesh);
                    break;
                case SHAKE:
                    shake(mesh);
                    break;
                case MOVE:
                    glide(mesh);
                    break;
            }
        }
        mesh->time += 0.4f;
    }
}

/**
 * @brief MainView::drawObject
 * Sets all uniforms and textures of a mesh and draws it on the screen
 *
 * @param mesh The mesh to draw
 */
void MainView::drawObject(Mesh mesh) {
    Scene s = scenes[currentSceneIndex];

    animateMesh(mesh);

    // Set texture information
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textures[0]);
    glUniform1i(uniformUV, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mesh->textures[1]);
    glUniform1i(uniformSpecularMap, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mesh->textures[2]);
    glUniform1i(uniformNormalMap, 2);

    glActiveTexture(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, s->cubeMap->cubeTextures);
    glUniform1i(uniformCubeMap, 0);

    // Set uniforms that are independent of the mesh
    setGlobalUniforms();

    glUniform1i(uniformSelected, mesh->selected);

    // Set booleans whether to use the texture maps
    glUniform1i(uniformUsingDiff, mesh->usingDiffuseTexture);
    glUniform1i(uniformUsingSpec, mesh->usingSpecularMap);
    glUniform1i(uniformUsingNorm, mesh->usingNormalMap);

    // Calculate transformation matrices
    QMatrix4x4 mvTransform = viewTransform;
    QVector4D light = mvTransform * QVector4D(s->lightPos, 1.0);
    mvTransform *= mesh->modelTransform * mesh->animationTransform;
    QMatrix3x3 normTransform = mvTransform.normalMatrix();

    // Set matrices
    glUniformMatrix4fv(uniformModelViewTransform, 1, GL_FALSE, mvTransform.data());
    glUniformMatrix3fv(uniformNormTransform, 1, GL_FALSE, normTransform.data());
    glUniformMatrix4fv(uniformModelTransform, 1, GL_FALSE, mesh->modelTransform.data());
    glUniformMatrix4fv(uniformViewTransform, 1, GL_FALSE, viewTransform.data());

    // Set lighting and material information
    glUniform3f(uniformLightPos, light.x(), light.y(), light.z());
    glUniform3f(uniformMaterialColor, mesh->materialColor.x(), mesh->materialColor.y(), mesh->materialColor.z());
    glUniform4f(uniformLightingConstants, mesh->ambientCoefficient, mesh->diffuseCoefficient, mesh->specularCoefficient, mesh->specularExponent);
    glUniform3f(uniformLightColor, s->lightColor.x(), s->lightColor.y(), s->lightColor.z());

    // Bind and draw mesh
    glBindVertexArray(mesh->VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh->size);
}

void MainView::drawCubeMap(CubeMap cMap) {
    glDepthMask(GL_FALSE);

    int index = CUBEMAP;

    updateShaderProgram(index);
    shaders[index]->bind();

    // Calculate transformation matrices
    QMatrix4x4 mvTransform = cMap->modelTransform * viewTransform;

    // Set matrices
    glUniformMatrix4fv(uniformModelViewTransform, 1, GL_FALSE, mvTransform.data());
    glUniformMatrix4fv(uniformProjectionTransform, 1, GL_FALSE, projectionTransform.data());

    // Set texture information
    uniformCubeMap = shaders[index]->uniformLocation("cubeMap");

    // Bind and draw mesh
    glActiveTexture(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cMap->cubeTextures);
    glUniform1i(uniformCubeMap, 0);
    glBindVertexArray(cMap->VAO);
    glDrawArrays(GL_TRIANGLES, 0, cMap->size);

    shaders[index]->release();

    glDepthMask(GL_TRUE);
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    Scene s = scenes[currentSceneIndex];

    updateMovement();
    updateViewTransform();
    // Clear the screen before rendering

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    drawCubeMap(s->cubeMap);

    // Optionally enable wireframe
    if(s->wireframe) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    time += 1.0 / 60.0f;


    for(int i = 0; i < s->objects.size(); i++) {
        glStencilFunc(GL_ALWAYS, i + 1, 0xFF);
        Mesh mesh = s->objects[i];
        // Activate and set the three textures
        updateShaderProgram(mesh->shaderIndex);

        shaders[mesh->shaderIndex]->bind();

        uniformCubeMap = shaders[mesh->shaderIndex]->uniformLocation("cubeMap");
        drawObject(mesh);

        shaders[mesh->shaderIndex]->release();
    }

    if(isSelecting) {
        updateSelectedObject();
    }
}

void MainView::updateSelectedObject() {
    Scene s = scenes[currentSceneIndex];
    GLuint index;

    glReadPixels(prevMouseX, geometry().height() - prevMouseY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    if(index != 0) {
        s->objects[s->selectedObjectIndex]->selected = false;
        s->selectedObjectIndex = index - 1;
        s->objects[s->selectedObjectIndex]->selected = true;
        window->updateUI(s);
    } else {
        s->objects[s->selectedObjectIndex]->selected = false;
    }
    isSelecting = false;
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) {
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    updateProjectionTransform();
}


// --- Image reader

QVector<quint8> MainView::imageToBytes(QImage image) {
    // needed since (0,0) is bottom left in OpenGL
    QImage im = image.mirrored();
    QVector<quint8> pixelData;
    pixelData.reserve(im.width()*im.height()*4);

    for (int i = 0; i != im.height(); ++i) {
        for (int j = 0; j != im.width(); ++j) {
            QRgb pixel = im.pixel(j,i);

            // pixel is of format #AARRGGBB (in hexadecimal notation)
            // so with bitshifting and binary AND you can get
            // the values of the different components
            quint8 r = (quint8)((pixel >> 16) & 0xFF); // Red component
            quint8 g = (quint8)((pixel >> 8) & 0xFF); // Green component
            quint8 b = (quint8)(pixel & 0xFF); // Blue component
            quint8 a = (quint8)((pixel >> 24) & 0xFF); // Alpha component

            // Add them to the Vector
            pixelData.append(r);
            pixelData.append(g);
            pixelData.append(b);
            pixelData.append(a);
        }
    }
    return pixelData;
}

/**
 * @brief MainView::addReference
 * Adds a reference to the mainWindow
 */
void MainView::addReference(MainWindow* mainWindow) {
    window = mainWindow;
    window->updateUI(scenes[currentSceneIndex]);
}

// --- OpenGL cleanup helpers

void MainView::destroyModelBuffers(Mesh mesh) {
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteVertexArrays(1, &mesh->VAO);
}

// --- Private helpers


/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
