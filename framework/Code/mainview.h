#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "mesh.h"
#include "scene.h"
#include "cubemap.h"
#include "mainwindow.h"

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



class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    enum ShadingMode : GLuint {
        PHONG = 0, NORMAL, GOURAUD, WATER, REALISM, CUBEMAP
    };

    enum FilterMode : GLuint {
        NEAREST = 0, LINEAR, NEAREST_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_NEAREST, LINEAR_MIPMAP_LINEAR
    };
    enum WrappingMode : GLuint {
        REPEAT = 0, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER
    };

    enum animation : GLuint {
        ROTATE = 0, BOUNCE, BREATHE, INFLATE, SHAKE, MOVE
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);

    void setAmbientComponent(int newComp);
    void setDiffuseComponent(int newComp);
    void setSpecularComponent(int newComp);
    void setSpecularExponent(int newExp);

    void toggleDiffTexture(bool useDiff);
    void toggleNormalMap(bool useNormalMap);
    void toggleSpecularMap(bool useSpecMap);
    void toggleWireframe();
    void updateLightPositionX(int value);
    void updateLightPositionY(int value);
    void updateLightPositionZ(int value);

    void updateSpecularMultplier(float newValue);
    void updateNormalMultplier(float newValue);

    void toggleAnisotropicFiltering(bool checked);
    void setMagFilter(FilterMode filter);
    void setMinFilter(FilterMode filter);
    void setTextureWrapMode(WrappingMode wrapping);

    void updateLightRED(float red);
    void updateLightGREEN(float green);
    void updateLightBLUE(float blue);
    void dragRotateX(float value);
    void dragRotateY(float value);
    void addReference(MainWindow* mainWindow);
    void toggleAnimation(bool checked);
    void resetAnimation();
    void updateShaderPrograms();

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged(QOpenGLDebugMessage Message);

private:
    MainWindow* window;

    QOpenGLDebugLogger debugLogger;
    QTimer timer; // timer used for animation
    float time = 0;
    GLint id = 0;

    // Vector for shader programs
    QVector<QOpenGLShaderProgram*> shaders;

    QVector<Scene> scenes;
    int currentSceneIndex = 0;

    // Uniforms for transformation matrices
    GLint uniformModelViewTransform;
    GLint uniformModelTransform;
    GLint uniformViewTransform;
    GLint uniformProjectionTransform;
    GLint uniformNormTransform;

    // Uniforms for texture maps
    GLint uniformUV;
    GLint uniformSpecularMap;
    GLint uniformNormalMap;

    // Uniform and variables for multiplier
    GLint uniformSpecularMultiplier;
    GLint uniformNormalMultiplier;
    float specularMultiplier = 1.0f;
    float normalMultiplier = 1.0f;

    // Material and lighting uniforms
    GLint uniformLightPos;
    GLint uniformLightColor;
    GLint uniformMaterialColor;
    GLint uniformLightingConstants;

    // Uniform for selected;
    GLint uniformSelected;

    // WAter uniforms
    GLint uniformAmplitudes;
    GLint uniformFrequencies;
    GLint uniformPhases;
    GLint uniformTime;

    // cubemap uniforms
    GLint uniformCubeMap;

    // Transforms
    QMatrix4x4 projectionTransform;
    QMatrix4x4 viewTransform;
    QMatrix4x4 viewRotation;

    // Uniforms and variables that indicate which texture maps should be used
    GLint uniformUsingDiff;
    GLint uniformUsingSpec;
    GLint uniformUsingNorm;

    // Texture options
    bool anisotropicFiltering = false;
    GLint textureWrap = GL_REPEAT;
    GLint minFilter = GL_NEAREST;
    GLint magFilter = GL_NEAREST;

    // Options for user input, will move to different file eventually
    int prevMouseX;
    int prevMouseY;
    int startMouseX;
    int startMouseY;
    bool rotatingX;
    bool rotatingY;


    bool isSelecting = false;
    bool isPressedW = false;
    bool isPressedA = false;
    bool isPressedS = false;
    bool isPressedD = false;
    bool isPressedE = false;
    bool isPressedQ = false;
    bool isPressedUp = false;
    bool isPressedDown = false;
    bool isPressedShift = false;

    void initializeScene1();
    void initializeScene2();
    void addObject(QString name, Scene scene);
    void addCubeMap(QString name, Scene scene);
    void addShaderProgram(QString path);
    void createShaderProgram();
    void drawObject(Mesh mesh);
    void drawCubeMap(CubeMap cMap);
    void animateMesh(Mesh mesh);
    void setGlobalUniforms();
    void updateShaderProgram(int newIndex);
    void loadMesh(Mesh mesh);
    void loadCubeMap(CubeMap cMap);
    GLuint loadCubeMapTexture(QVector<QString> faces);
    void loadMeshTextures(Mesh mesh);
    void loadTexture(Mesh mesh, QString file, int index);
    QVector<quint8> imageToBytes(QImage image);
    void reloadTextures();
    void setTextureParameters(Mesh mesh, int index);

    void destroyModelBuffers(Mesh mesh);

    void updateSelectedObject();
    void updateMovement();
    void updateProjectionTransform();
    void updateViewTransform();
    void updateModelTransforms(Mesh mesh);
    void updateWrappingOption(WrappingMode optionEnum);
    void updateMagFilterOption(FilterMode optionEnum);
    void updateMinFilterOption(FilterMode optionEnum);
};

#endif // MAINVIEW_H
