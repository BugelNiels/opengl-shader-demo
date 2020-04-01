#include "mainview.h"

void MainView::reloadTextures() {
    for(Scene s : scenes) {
        for(int i = 0; i < s->objects.size(); i++) {
            setTextureParameters(s->objects[i], 0);
            setTextureParameters(s->objects[i], 1);
            setTextureParameters(s->objects[i], 2);
        }
    }
    update();
}

void MainView::updateMovement() {
    Scene s = scenes[currentSceneIndex];
    s->currentMovement = QVector3D(0, 0, 0);
    s->currentRotation = 0;
    float movementSpeed = 0.1f;
    float rotationSpeed = 1.2f;
    if(isPressedShift) {
        movementSpeed *= 2.0f;
        rotationSpeed *= 2.0f;
    }

    viewRotation.setToIdentity();
    viewRotation.rotate(s->cameraRotation, 0, 1, 0);

    if(isPressedE) {
        s->currentRotation += rotationSpeed;
    }
    if(isPressedQ) {
        s->currentRotation -= rotationSpeed;
    }
    if(isPressedW) {
        s->currentMovement += QVector3D(0, 0, movementSpeed) * viewRotation;
    }
    if(isPressedS) {
        s->currentMovement += QVector3D(0, 0, -movementSpeed) * viewRotation;
    }
    if(isPressedA) {
        s->currentMovement += QVector3D(movementSpeed, 0, 0) * viewRotation;
    }
    if(isPressedD) {
        s->currentMovement += QVector3D(-movementSpeed, 0, 0) * viewRotation;
    }
    if(isPressedUp) {
        s->currentMovement += QVector3D(0, -movementSpeed, 0);
    }
    if(isPressedDown) {
        s->currentMovement += QVector3D(0, movementSpeed, 0);
    }
}

void MainView::updateProjectionTransform() {
    float aspect_ratio = static_cast<float>(width()) / static_cast<float>(height());
    projectionTransform.setToIdentity();
    projectionTransform.perspective(60, aspect_ratio, 0.2f, 50);
}

void MainView::updateViewTransform() {
    Scene s = scenes[currentSceneIndex];
    viewTransform.setToIdentity();
    viewTransform.translate(s->cameraMovement);
    viewRotation.setToIdentity();
    viewRotation.rotate(s->cameraRotation, 0, 1, 0);
    viewTransform = viewRotation * viewTransform;
    s->cameraMovement += s->currentMovement;
    s->cameraRotation += s->currentRotation;
}

void MainView::updateModelTransforms(Mesh mesh) {
    mesh->modelTransform.setToIdentity();
    mesh->modelTransform.translate(0, 0, -20);
    mesh->modelTransform.translate(mesh->initialPosition);
    mesh->modelTransform.scale(mesh->scale);
    mesh->modelTransform.rotate(QQuaternion::fromEulerAngles(mesh->initialRotation));
    mesh->modelTransform.rotate(QQuaternion::fromEulerAngles(mesh->rotation));
    update();
}

/**
 * @brief MainView::updateWrappingOption
 * Sets the wrapping option for the texture
 *
 * @param wrapping The new wrapping mode
 */
void MainView::updateWrappingOption(WrappingMode wrapping) {
    switch (wrapping) {
        case REPEAT :
            textureWrap = GL_REPEAT;
            break;
        case MIRRORED_REPEAT :
            textureWrap = GL_MIRRORED_REPEAT;
            break;
        case CLAMP_TO_EDGE :
            textureWrap = GL_CLAMP_TO_EDGE;
            break;
        case CLAMP_TO_BORDER :
            textureWrap = GL_CLAMP_TO_BORDER;
            break;
    }
}

/**
 * @brief MainView::updateMagFilterOption
 * Sets the magnifying filter for the texture
 *
 * @param filter The new magnifying filter option
 */
void MainView::updateMagFilterOption(FilterMode filter) {
    switch (filter) {
        case NEAREST :
            magFilter = GL_NEAREST;
            break;
        case LINEAR :
            magFilter = GL_LINEAR;
            break;
        default:
            break;
    }
}

/**
 * @brief MainView::updateMinFilterOption
 * Sets the minifying filter for the texture
 *
 * @param filter The new minifying filter option
 */
void MainView::updateMinFilterOption(FilterMode filter) {
    switch (filter) {
        case NEAREST :
            minFilter = GL_NEAREST;
            break;
        case LINEAR :
            minFilter = GL_LINEAR;
            break;
        case NEAREST_MIPMAP_NEAREST :
            minFilter = GL_NEAREST_MIPMAP_NEAREST;
            break;
        case NEAREST_MIPMAP_LINEAR :
            minFilter = GL_NEAREST_MIPMAP_LINEAR;
            break;
        case LINEAR_MIPMAP_NEAREST :
            minFilter = GL_LINEAR_MIPMAP_NEAREST;
            break;
        case LINEAR_MIPMAP_LINEAR :
            minFilter = GL_LINEAR_MIPMAP_LINEAR;
            break;
    }
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->rotation = { static_cast<float>(rotateX), static_cast<float>(rotateY), static_cast<float>(rotateZ) };
    updateModelTransforms(s->objects[s->selectedObjectIndex]);
}

void MainView::setScale(int newScale) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->scale = static_cast<float>(newScale) / 100.f;
    updateModelTransforms(s->objects[s->selectedObjectIndex]);
}

void MainView::setShadingMode(ShadingMode shading) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->shaderIndex = shading;
}

void MainView::setAmbientComponent(int newComp) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->ambientCoefficient = newComp / 100.0f;
    update();
}

void MainView::setDiffuseComponent(int newComp) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->diffuseCoefficient = newComp / 100.0f;
    update();
}

void MainView::setSpecularComponent(int newComp) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->specularCoefficient = newComp / 100.0f;
    update();
}

void MainView::setSpecularExponent(int newExp) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->specularExponent = newExp;
    update();
}

void MainView::toggleDiffTexture(bool useDiff) {
    Scene s = scenes[currentSceneIndex];
    if(s->objects[s->selectedObjectIndex]->textureSuccess[0]) {
        s->objects[s->selectedObjectIndex]->usingDiffuseTexture = useDiff;
        update();
    }
}

void MainView::toggleSpecularMap(bool useSpecMap) {
    Scene s = scenes[currentSceneIndex];
    if(s->objects[s->selectedObjectIndex]->textureSuccess[1]) {
        s->objects[s->selectedObjectIndex]->usingSpecularMap = useSpecMap;
        update();
    }
}

void MainView::toggleNormalMap(bool useNormalMap) {
    Scene s = scenes[currentSceneIndex];
    if(s->objects[s->selectedObjectIndex]->textureSuccess[2]) {
        s->objects[s->selectedObjectIndex]->usingNormalMap = useNormalMap;
        update();
    }
}

void MainView::updateLightPositionX(int value) {
    Scene s = scenes[currentSceneIndex];
    s->lightPos.setX(value);
    update();
}

void MainView::updateLightPositionY(int value) {
    Scene s = scenes[currentSceneIndex];
    s->lightPos.setY(value);
    update();
}

void MainView::updateLightPositionZ(int value) {
    Scene s = scenes[currentSceneIndex];
    s->lightPos.setZ(value);
    update();
}

void MainView::updateSpecularMultplier(float newValue) {
    specularMultiplier = newValue;
    update();
}

void MainView::updateNormalMultplier(float newValue) {
    normalMultiplier = newValue;
    update();
}

void MainView::toggleWireframe() {
    Scene s = scenes[currentSceneIndex];
    s->wireframe = !s->wireframe;
    update();
}

void MainView::toggleAnisotropicFiltering(bool checked) {
    anisotropicFiltering = checked;
    reloadTextures();
}

void MainView::setMagFilter(FilterMode filter) {
    updateMagFilterOption(filter);
    reloadTextures();
}

void MainView::setMinFilter(FilterMode filter) {
    updateMinFilterOption(filter);
    reloadTextures();
}

void MainView::setTextureWrapMode(WrappingMode wrapping) {
    updateWrappingOption(wrapping);
    reloadTextures();
}

void MainView::updateLightRED(float red) {
    Scene s = scenes[currentSceneIndex];
    s->lightColor.setX(red);
    update();
}

void MainView::updateLightGREEN(float green) {
    Scene s = scenes[currentSceneIndex];
    s->lightColor.setY(green);
    update();
}

void MainView::updateLightBLUE(float blue) {
    Scene s = scenes[currentSceneIndex];
    s->lightColor.setZ(blue);
    update();
}

void MainView::dragRotateX(float value) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->rotation.setY(value);
    updateModelTransforms(s->objects[s->selectedObjectIndex]);
}

void MainView::dragRotateY(float value) {
    Scene s = scenes[currentSceneIndex];
    s->objects[s->selectedObjectIndex]->rotation.setX(value);
    updateModelTransforms(s->objects[s->selectedObjectIndex]);
}

void MainView::toggleAnimation(bool checked) {
    Scene s = scenes[currentSceneIndex];
    s->animation = checked;
}

void MainView::updateShaderPrograms() {
//    createShaderProgram();
//    update();
}

void MainView::resetAnimation() {
    Scene s = scenes[currentSceneIndex];
    for(Mesh m : s->objects) {
        m->animationTransform.setToIdentity();
        m->rotationAngle = 0;
        m->time = 0;
        m->pos = 0;
        m->scale = 1;
    }
}
