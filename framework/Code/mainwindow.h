#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mesh.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateUI(Scene scene);
private:
    void resetHidden();

private slots:
    void on_ResetRotationButton_clicked(bool checked);
    void on_RotationDialX_valueChanged(int value);
    void on_RotationDialY_valueChanged(int value);
    void on_RotationDialZ_valueChanged(int value);

    void on_ResetScaleButton_clicked(bool checked);
    void on_ScaleSlider_valueChanged(int value);

    void on_PhongButton_toggled(bool checked);
    void on_NormalButton_toggled(bool checked);
    void on_GouraudButton_toggled(bool checked);
    void on_WaterButton_toggled(bool checked);

    void on_DiffuseSlider_valueChanged(int value);
    void on_SpecularSlider_valueChanged(int value);
    void on_AmbientSlider_valueChanged(int value);
    void on_SpecExpSlider_valueChanged(int value);

    void on_DiffuseTex_toggled(bool checked);
    void on_NormalTex_toggled(bool checked);
    void on_SpecularTex_toggled(bool checked);

    void on_XSLider_valueChanged(int value);
    void on_YSLider_valueChanged(int value);
    void on_ZSLider_valueChanged(int value);
    void on_SpecularMultiplier_valueChanged(double arg1);
    void on_NormalMultiplier_valueChanged(double arg1);
    void on_checkBox_toggled(bool checked);
    void on_moreOptionsButton_clicked();
    void on_anisotropicFilter_toggled(bool checked);
    void on_wrapRepeat_toggled(bool checked);
    void on_wrapMirror_toggled(bool checked);
    void on_wrapEdgeClamp_toggled(bool checked);
    void on_wrapBorderClamp_toggled(bool checked);
    void on_maxNearest_toggled(bool checked);
    void on_maxLinear_toggled(bool checked);
    void on_minNearest_toggled(bool checked);
    void on_minLinear_toggled(bool checked);
    void on_minMipNearestNearest_toggled(bool checked);
    void on_minMipNearestLinear_toggled(bool checked);
    void on_minMipLinearNearest_toggled(bool checked);
    void on_minMipLinearLinear_toggled(bool checked);
    void on_showFiltersButton_clicked();
    void on_red_valueChanged(int arg1);
    void on_green_valueChanged(int arg1);
    void on_blue_valueChanged(int arg1);
    void on_animationCheckBox_toggled(bool checked);
    void on_resetAnimationButton_clicked();
    void on_realismButton_toggled(bool checked);
    void on_shaderUpdateButton_clicked();
};

#endif // MAINWINDOW_H
