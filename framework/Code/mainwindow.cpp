#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->mainView->setFocus();
    ui->mainView->addReference(this);

    ui->SpecularMultiplier->setEnabled(false);
    ui->NormalMultiplier->setEnabled(false);

    ui->settingsBox2->hide();
    ui->filterGroupBox->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

// --- Functions that listen for widget events
// forewards to the mainview

void MainWindow::on_ResetRotationButton_clicked(bool checked) {
    Q_UNUSED(checked);
    ui->RotationDialX->setValue(0);
    ui->RotationDialY->setValue(0);
    ui->RotationDialZ->setValue(0);
    ui->mainView->setRotation(0, 0, 0);
}

void MainWindow::on_RotationDialX_valueChanged(int value) {
    ui->mainView->setRotation(value,
                              ui->RotationDialY->value(),
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialY_valueChanged(int value) {
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              value,
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialZ_valueChanged(int value) {
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              ui->RotationDialY->value(),
                              value);
}

void MainWindow::on_ResetScaleButton_clicked(bool checked) {
    Q_UNUSED(checked);
    ui->ScaleSlider->setValue(100);
    ui->mainView->setScale(100);
}

void MainWindow::on_ScaleSlider_valueChanged(int value) {
    ui->mainView->setScale(value);
}

void MainWindow::on_PhongButton_toggled(bool checked) {
    if (checked) {
        resetHidden();
        ui->mainView->setShadingMode(MainView::PHONG);
        ui->mainView->update();
    }
}

void MainWindow::on_NormalButton_toggled(bool checked) {
    if (checked) {
        resetHidden();
        ui->DiffuseTex->setEnabled(false);
        ui->SpecularTex->setEnabled(false);
        ui->SpecularMultiplier->setEnabled(false);
        ui->mainView->update();
        ui->mainView->setShadingMode(MainView::NORMAL);
    }
}

void MainWindow::on_GouraudButton_toggled(bool checked) {
    if (checked) {
        resetHidden();
        ui->SpecularTex->setEnabled(false);
        ui->NormalTex->setEnabled(false);
        ui->NormalMultiplier->setEnabled(false);

        ui->mainView->update();
        ui->mainView->setShadingMode(MainView::GOURAUD);
    }
}

void MainWindow::on_WaterButton_toggled(bool checked) {
    if (checked) {
        resetHidden();
        ui->SpecularTex->setEnabled(false);
        ui->NormalTex->setEnabled(false);
        ui->NormalMultiplier->setEnabled(false);

        ui->mainView->update();
        ui->mainView->setShadingMode(MainView::WATER);
    }
}

void MainWindow::on_DiffuseSlider_valueChanged(int value) {
    ui->mainView->setDiffuseComponent(value);
}

void MainWindow::on_SpecularSlider_valueChanged(int value) {
    ui->mainView->setSpecularComponent(value);
}

void MainWindow::on_AmbientSlider_valueChanged(int value) {
    ui->mainView->setAmbientComponent(value);
}

void MainWindow::on_SpecExpSlider_valueChanged(int value) {
    ui->mainView->setSpecularExponent(value);
}

void MainWindow::on_DiffuseTex_toggled(bool checked) {
    ui->mainView->toggleDiffTexture(checked);
}

void MainWindow::on_NormalTex_toggled(bool checked) {
    ui->mainView->toggleNormalMap(checked);
    if(checked) {
        ui->NormalMultiplier->setEnabled(true);
    } else {
        ui->NormalMultiplier->setEnabled(false);
    }
}

void MainWindow::on_SpecularTex_toggled(bool checked) {
    ui->mainView->toggleSpecularMap(checked);
    if(checked) {
        ui->SpecularMultiplier->setEnabled(true);
    } else {
        ui->SpecularMultiplier->setEnabled(false);
    }
}

void MainWindow::on_XSLider_valueChanged(int value) {
    ui->mainView->updateLightPositionX(value);
}

void MainWindow::on_YSLider_valueChanged(int value) {
    ui->mainView->updateLightPositionY(value);
}

void MainWindow::on_ZSLider_valueChanged(int value) {
    ui->mainView->updateLightPositionZ(value);
}

void MainWindow::on_SpecularMultiplier_valueChanged(double newValue) {
    ui->mainView->updateSpecularMultplier(static_cast<float> (newValue));
}

void MainWindow::on_NormalMultiplier_valueChanged(double newValue) {
    ui->mainView->updateNormalMultplier(static_cast<float> (1.0 / newValue));
}

void MainWindow::on_checkBox_toggled(bool checked) {
    ui->mainView->toggleWireframe();
}

void MainWindow::on_moreOptionsButton_clicked() {
    if(ui->settingsBox2->isHidden()) {
        ui->settingsBox2->show();
        ui->moreOptionsButton->setText("Hide Extra Options");
    } else {
        ui->settingsBox2->hide();
        ui->moreOptionsButton->setText("More Options..");
    }
}

void MainWindow::on_anisotropicFilter_toggled(bool checked) {
    ui->mainView->toggleAnisotropicFiltering(checked);
}

void MainWindow::on_wrapRepeat_toggled(bool checked) {
    if(checked) {
        ui->mainView->setTextureWrapMode(MainView::REPEAT);
    }
}

void MainWindow::on_wrapMirror_toggled(bool checked) {
    if(checked) {
        ui->mainView->setTextureWrapMode(MainView::MIRRORED_REPEAT);
    }
}

void MainWindow::on_wrapEdgeClamp_toggled(bool checked) {
    if(checked) {
        ui->mainView->setTextureWrapMode(MainView::CLAMP_TO_EDGE);
    }
}

void MainWindow::on_wrapBorderClamp_toggled(bool checked) {
    if(checked) {
        ui->mainView->setTextureWrapMode(MainView::CLAMP_TO_BORDER);
    }
}

void MainWindow::on_maxNearest_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMagFilter(MainView::NEAREST);
    }
}

void MainWindow::on_maxLinear_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMagFilter(MainView::LINEAR);
    }
}

void MainWindow::on_minNearest_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMinFilter(MainView::NEAREST);
    }
}

void MainWindow::on_minLinear_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMinFilter(MainView::LINEAR);
    }
}

void MainWindow::on_minMipNearestNearest_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMinFilter(MainView::NEAREST_MIPMAP_NEAREST);
    }
}

void MainWindow::on_minMipNearestLinear_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMinFilter(MainView::NEAREST_MIPMAP_LINEAR);
    }
}

void MainWindow::on_minMipLinearNearest_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMinFilter(MainView::LINEAR_MIPMAP_NEAREST);
    }
}

void MainWindow::on_minMipLinearLinear_toggled(bool checked) {
    if(checked) {
        ui->mainView->setMinFilter(MainView::LINEAR_MIPMAP_LINEAR);
    }
}

void MainWindow::on_showFiltersButton_clicked()
{
    if(ui->filterGroupBox->isHidden()) {
        ui->filterGroupBox->show();
        ui->showFiltersButton->setText("Hide Filter Options");
    } else {
        ui->filterGroupBox->hide();
        ui->showFiltersButton->setText("Show Filter Options");
    }
}

void MainWindow::on_red_valueChanged(int newRed) {
    ui->mainView->updateLightRED(newRed / 255.0f);
}

void MainWindow::on_green_valueChanged(int newGreen) {
    ui->mainView->updateLightGREEN(newGreen / 255.0f);
}

void MainWindow::on_blue_valueChanged(int newBlue) {
    ui->mainView->updateLightBLUE(newBlue / 255.0f);
}

void MainWindow::updateUI(Scene scene) {

    Mesh mesh = scene->objects[scene->selectedObjectIndex];
    ui->selectedObjectLabel->setText(mesh->id);

    ui->DiffuseTex->setEnabled(true);
    ui->DiffuseTex->setChecked(mesh->usingDiffuseTexture);

    ui->NormalTex->setEnabled(true);
    ui->NormalTex->setChecked(mesh->usingNormalMap);
    if(mesh->usingNormalMap) {
        ui->NormalMultiplier->setEnabled(true);
    } else {
        ui->NormalMultiplier->setEnabled(false);
    }

    ui->SpecularTex->setEnabled(true);
    ui->SpecularTex->setChecked(mesh->usingSpecularMap);
    if(mesh->usingSpecularMap) {
        ui->SpecularMultiplier->setEnabled(true);
    } else {
        ui->SpecularMultiplier->setEnabled(false);
    }

    ui->RotationDialX->setValue(mesh->rotation.x() * 360);
    ui->RotationDialY->setValue(mesh->rotation.y() * 360);
    ui->RotationDialZ->setValue(mesh->rotation.z() * 360);

    ui->AmbientSlider->setValue(mesh->ambientCoefficient * 100);
    ui->SpecularSlider->setValue(mesh->specularCoefficient * 100);
    ui->DiffuseSlider->setValue(mesh->diffuseCoefficient * 100);
    ui->SpecExpSlider->setValue(mesh->specularExponent);

    switch(mesh->shaderIndex) {
        case 0:
            ui->PhongButton->toggle();
            break;
        case 1:
            ui->NormalButton->toggle();

            ui->DiffuseTex->setEnabled(false);
            ui->SpecularTex->setEnabled(false);
            ui->SpecularMultiplier->setEnabled(false);
            break;
        case 2:
            ui->GouraudButton->toggle();

            ui->SpecularTex->setEnabled(false);
            ui->NormalTex->setEnabled(false);
            ui->NormalMultiplier->setEnabled(false);
            break;
        case 3:
            ui->WaterButton->toggle();

            ui->SpecularTex->setEnabled(false);
            ui->NormalTex->setEnabled(false);
            ui->NormalMultiplier->setEnabled(false);
            break;
    }

    ui->checkBox->setChecked(scene->wireframe);
    ui->animationCheckBox->setChecked(scene->animation);

    ui->red->setValue(scene->lightColor.x()*255);
    ui->green->setValue(scene->lightColor.y()*255);
    ui->blue->setValue(scene->lightColor.z()*255);

    ui->XSLider->setValue(scene->lightPos.x());
    ui->YSLider->setValue(scene->lightPos.y());
    ui->ZSLider->setValue(scene->lightPos.z());
}


// Utility, resets all the proper visibility and enabling of certain ui elements
void MainWindow::resetHidden() {
    if(ui->SpecularTex->isChecked() && ui->SpecularTex->isEnabled()) {
        ui->SpecularMultiplier->setEnabled(true);
    }
    if(ui->NormalTex->isChecked() && ui->NormalTex->isEnabled()) {
        ui->NormalMultiplier->setEnabled(true);
    }

    ui->DiffuseTex->setEnabled(true);
    ui->SpecularTex->setEnabled(true);
    ui->NormalTex->setEnabled(true);
}

void MainWindow::on_animationCheckBox_toggled(bool checked) {
    ui->mainView->toggleAnimation(checked);
}

void MainWindow::on_resetAnimationButton_clicked() {
    ui->mainView->resetAnimation();
}

void MainWindow::on_realismButton_toggled(bool checked) {
    if (checked) {
        resetHidden();
        ui->SpecularTex->setEnabled(false);
        ui->NormalTex->setEnabled(false);
        ui->NormalMultiplier->setEnabled(false);

        ui->mainView->update();
        ui->mainView->setShadingMode(MainView::REALISM);
    }
}

void MainWindow::on_shaderUpdateButton_clicked() {
//    ui->mainView->updateShaderPrograms();
}
