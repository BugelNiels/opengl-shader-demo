/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *settingsBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *selectedLabel;
    QLabel *selectedObjectLabel;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *animationCheckBox;
    QPushButton *resetAnimationButton;
    QGroupBox *rotationBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QDial *RotationDialX;
    QDial *RotationDialY;
    QDial *RotationDialZ;
    QPushButton *ResetRotationButton;
    QGroupBox *scalingBox;
    QVBoxLayout *verticalLayout_4;
    QSlider *ScaleSlider;
    QPushButton *ResetScaleButton;
    QGroupBox *shadingBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *PhongButton;
    QRadioButton *NormalButton;
    QRadioButton *GouraudButton;
    QRadioButton *WaterButton;
    QGroupBox *verticalGroupBox1;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox;
    QPushButton *showFiltersButton;
    QPushButton *moreOptionsButton;
    QGroupBox *filterGroupBox;
    QVBoxLayout *filterOptionsGroupBox;
    QCheckBox *anisotropicFilter;
    QGroupBox *wrappingBox;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *wrapRepeat;
    QRadioButton *wrapMirror;
    QRadioButton *wrapEdgeClamp;
    QRadioButton *wrapBorderClamp;
    QGroupBox *maxFilterBox;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *maxNearest;
    QRadioButton *maxLinear;
    QGroupBox *minFilterBox;
    QVBoxLayout *verticalLayout_7;
    QRadioButton *minNearest;
    QRadioButton *minLinear;
    QRadioButton *minMipNearestNearest;
    QRadioButton *minMipNearestLinear;
    QRadioButton *minMipLinearNearest;
    QRadioButton *minMipLinearLinear;
    MainView *mainView;
    QGroupBox *settingsBox2;
    QVBoxLayout *shadingSettings;
    QGroupBox *lightingBox;
    QVBoxLayout *lightBox;
    QLabel *ambientLabel;
    QSlider *AmbientSlider;
    QLabel *diffuseLabel;
    QSlider *DiffuseSlider;
    QLabel *specularLabel;
    QSlider *SpecularSlider;
    QLabel *specularExpLabel;
    QSlider *SpecExpSlider;
    QGroupBox *lightColorBox;
    QHBoxLayout *LightColorBox;
    QSpinBox *red;
    QSpinBox *green;
    QSpinBox *blue;
    QLabel *lightPosLabel;
    QHBoxLayout *lightPosLabelBox;
    QLabel *xLabel;
    QLabel *yLabel;
    QLabel *zLabel;
    QHBoxLayout *lightPosBox;
    QSlider *XSLider;
    QSlider *YSLider;
    QSlider *ZSLider;
    QGroupBox *materialBox;
    QVBoxLayout *box;
    QCheckBox *DiffuseTex;
    QCheckBox *SpecularTex;
    QCheckBox *NormalTex;
    QGroupBox *multiplierBox;
    QVBoxLayout *normalIntensityBox;
    QLabel *specularMultLabel;
    QDoubleSpinBox *SpecularMultiplier;
    QLabel *normalMultLabel;
    QDoubleSpinBox *NormalMultiplier;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1376, 857);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        settingsBox = new QGroupBox(centralWidget);
        settingsBox->setObjectName(QString::fromUtf8("settingsBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsBox->sizePolicy().hasHeightForWidth());
        settingsBox->setSizePolicy(sizePolicy);
        settingsBox->setMinimumSize(QSize(220, 0));
        settingsBox->setMaximumSize(QSize(220, 16777215));
        verticalLayout_3 = new QVBoxLayout(settingsBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        selectedLabel = new QLabel(settingsBox);
        selectedLabel->setObjectName(QString::fromUtf8("selectedLabel"));

        verticalLayout_3->addWidget(selectedLabel);

        selectedObjectLabel = new QLabel(settingsBox);
        selectedObjectLabel->setObjectName(QString::fromUtf8("selectedObjectLabel"));

        verticalLayout_3->addWidget(selectedObjectLabel);

        verticalGroupBox = new QGroupBox(settingsBox);
        verticalGroupBox->setObjectName(QString::fromUtf8("verticalGroupBox"));
        verticalLayout_9 = new QVBoxLayout(verticalGroupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        animationCheckBox = new QCheckBox(verticalGroupBox);
        animationCheckBox->setObjectName(QString::fromUtf8("animationCheckBox"));

        verticalLayout_9->addWidget(animationCheckBox);

        resetAnimationButton = new QPushButton(verticalGroupBox);
        resetAnimationButton->setObjectName(QString::fromUtf8("resetAnimationButton"));

        verticalLayout_9->addWidget(resetAnimationButton);


        verticalLayout_3->addWidget(verticalGroupBox);

        rotationBox = new QGroupBox(settingsBox);
        rotationBox->setObjectName(QString::fromUtf8("rotationBox"));
        sizePolicy.setHeightForWidth(rotationBox->sizePolicy().hasHeightForWidth());
        rotationBox->setSizePolicy(sizePolicy);
        rotationBox->setMinimumSize(QSize(205, 0));
        rotationBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout = new QVBoxLayout(rotationBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        RotationDialX = new QDial(rotationBox);
        RotationDialX->setObjectName(QString::fromUtf8("RotationDialX"));
        RotationDialX->setMaximum(359);
        RotationDialX->setWrapping(true);
        RotationDialX->setNotchTarget(12.000000000000000);
        RotationDialX->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialX);

        RotationDialY = new QDial(rotationBox);
        RotationDialY->setObjectName(QString::fromUtf8("RotationDialY"));
        RotationDialY->setMaximum(359);
        RotationDialY->setWrapping(true);
        RotationDialY->setNotchTarget(12.000000000000000);
        RotationDialY->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialY);

        RotationDialZ = new QDial(rotationBox);
        RotationDialZ->setObjectName(QString::fromUtf8("RotationDialZ"));
        RotationDialZ->setMaximum(359);
        RotationDialZ->setWrapping(true);
        RotationDialZ->setNotchTarget(12.000000000000000);
        RotationDialZ->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialZ);


        verticalLayout->addLayout(horizontalLayout_2);

        ResetRotationButton = new QPushButton(rotationBox);
        ResetRotationButton->setObjectName(QString::fromUtf8("ResetRotationButton"));

        verticalLayout->addWidget(ResetRotationButton);


        verticalLayout_3->addWidget(rotationBox);

        scalingBox = new QGroupBox(settingsBox);
        scalingBox->setObjectName(QString::fromUtf8("scalingBox"));
        sizePolicy.setHeightForWidth(scalingBox->sizePolicy().hasHeightForWidth());
        scalingBox->setSizePolicy(sizePolicy);
        scalingBox->setMinimumSize(QSize(205, 0));
        scalingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_4 = new QVBoxLayout(scalingBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ScaleSlider = new QSlider(scalingBox);
        ScaleSlider->setObjectName(QString::fromUtf8("ScaleSlider"));
        ScaleSlider->setMinimum(1);
        ScaleSlider->setMaximum(600);
        ScaleSlider->setValue(100);
        ScaleSlider->setOrientation(Qt::Horizontal);
        ScaleSlider->setInvertedAppearance(false);
        ScaleSlider->setInvertedControls(false);
        ScaleSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_4->addWidget(ScaleSlider);

        ResetScaleButton = new QPushButton(scalingBox);
        ResetScaleButton->setObjectName(QString::fromUtf8("ResetScaleButton"));

        verticalLayout_4->addWidget(ResetScaleButton);


        verticalLayout_3->addWidget(scalingBox);

        shadingBox = new QGroupBox(settingsBox);
        shadingBox->setObjectName(QString::fromUtf8("shadingBox"));
        sizePolicy.setHeightForWidth(shadingBox->sizePolicy().hasHeightForWidth());
        shadingBox->setSizePolicy(sizePolicy);
        shadingBox->setMinimumSize(QSize(205, 0));
        shadingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_2 = new QVBoxLayout(shadingBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        PhongButton = new QRadioButton(shadingBox);
        PhongButton->setObjectName(QString::fromUtf8("PhongButton"));
        PhongButton->setChecked(true);

        verticalLayout_2->addWidget(PhongButton);

        NormalButton = new QRadioButton(shadingBox);
        NormalButton->setObjectName(QString::fromUtf8("NormalButton"));

        verticalLayout_2->addWidget(NormalButton);

        GouraudButton = new QRadioButton(shadingBox);
        GouraudButton->setObjectName(QString::fromUtf8("GouraudButton"));

        verticalLayout_2->addWidget(GouraudButton);

        WaterButton = new QRadioButton(shadingBox);
        WaterButton->setObjectName(QString::fromUtf8("WaterButton"));

        verticalLayout_2->addWidget(WaterButton);


        verticalLayout_3->addWidget(shadingBox);

        verticalGroupBox1 = new QGroupBox(settingsBox);
        verticalGroupBox1->setObjectName(QString::fromUtf8("verticalGroupBox1"));
        verticalLayout_5 = new QVBoxLayout(verticalGroupBox1);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBox = new QCheckBox(verticalGroupBox1);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_5->addWidget(checkBox);

        showFiltersButton = new QPushButton(verticalGroupBox1);
        showFiltersButton->setObjectName(QString::fromUtf8("showFiltersButton"));

        verticalLayout_5->addWidget(showFiltersButton);


        verticalLayout_3->addWidget(verticalGroupBox1);

        moreOptionsButton = new QPushButton(settingsBox);
        moreOptionsButton->setObjectName(QString::fromUtf8("moreOptionsButton"));

        verticalLayout_3->addWidget(moreOptionsButton);


        horizontalLayout->addWidget(settingsBox);

        filterGroupBox = new QGroupBox(centralWidget);
        filterGroupBox->setObjectName(QString::fromUtf8("filterGroupBox"));
        filterGroupBox->setMaximumSize(QSize(300, 16777215));
        filterOptionsGroupBox = new QVBoxLayout(filterGroupBox);
        filterOptionsGroupBox->setSpacing(6);
        filterOptionsGroupBox->setContentsMargins(11, 11, 11, 11);
        filterOptionsGroupBox->setObjectName(QString::fromUtf8("filterOptionsGroupBox"));
        anisotropicFilter = new QCheckBox(filterGroupBox);
        anisotropicFilter->setObjectName(QString::fromUtf8("anisotropicFilter"));

        filterOptionsGroupBox->addWidget(anisotropicFilter);

        wrappingBox = new QGroupBox(filterGroupBox);
        wrappingBox->setObjectName(QString::fromUtf8("wrappingBox"));
        verticalLayout_6 = new QVBoxLayout(wrappingBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        wrapRepeat = new QRadioButton(wrappingBox);
        wrapRepeat->setObjectName(QString::fromUtf8("wrapRepeat"));
        wrapRepeat->setChecked(true);

        verticalLayout_6->addWidget(wrapRepeat);

        wrapMirror = new QRadioButton(wrappingBox);
        wrapMirror->setObjectName(QString::fromUtf8("wrapMirror"));

        verticalLayout_6->addWidget(wrapMirror);

        wrapEdgeClamp = new QRadioButton(wrappingBox);
        wrapEdgeClamp->setObjectName(QString::fromUtf8("wrapEdgeClamp"));

        verticalLayout_6->addWidget(wrapEdgeClamp);

        wrapBorderClamp = new QRadioButton(wrappingBox);
        wrapBorderClamp->setObjectName(QString::fromUtf8("wrapBorderClamp"));

        verticalLayout_6->addWidget(wrapBorderClamp);


        filterOptionsGroupBox->addWidget(wrappingBox);

        maxFilterBox = new QGroupBox(filterGroupBox);
        maxFilterBox->setObjectName(QString::fromUtf8("maxFilterBox"));
        verticalLayout_8 = new QVBoxLayout(maxFilterBox);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        maxNearest = new QRadioButton(maxFilterBox);
        maxNearest->setObjectName(QString::fromUtf8("maxNearest"));
        maxNearest->setChecked(true);

        verticalLayout_8->addWidget(maxNearest);

        maxLinear = new QRadioButton(maxFilterBox);
        maxLinear->setObjectName(QString::fromUtf8("maxLinear"));

        verticalLayout_8->addWidget(maxLinear);


        filterOptionsGroupBox->addWidget(maxFilterBox);

        minFilterBox = new QGroupBox(filterGroupBox);
        minFilterBox->setObjectName(QString::fromUtf8("minFilterBox"));
        verticalLayout_7 = new QVBoxLayout(minFilterBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        minNearest = new QRadioButton(minFilterBox);
        minNearest->setObjectName(QString::fromUtf8("minNearest"));
        minNearest->setChecked(true);

        verticalLayout_7->addWidget(minNearest);

        minLinear = new QRadioButton(minFilterBox);
        minLinear->setObjectName(QString::fromUtf8("minLinear"));

        verticalLayout_7->addWidget(minLinear);

        minMipNearestNearest = new QRadioButton(minFilterBox);
        minMipNearestNearest->setObjectName(QString::fromUtf8("minMipNearestNearest"));

        verticalLayout_7->addWidget(minMipNearestNearest);

        minMipNearestLinear = new QRadioButton(minFilterBox);
        minMipNearestLinear->setObjectName(QString::fromUtf8("minMipNearestLinear"));

        verticalLayout_7->addWidget(minMipNearestLinear);

        minMipLinearNearest = new QRadioButton(minFilterBox);
        minMipLinearNearest->setObjectName(QString::fromUtf8("minMipLinearNearest"));

        verticalLayout_7->addWidget(minMipLinearNearest);

        minMipLinearLinear = new QRadioButton(minFilterBox);
        minMipLinearLinear->setObjectName(QString::fromUtf8("minMipLinearLinear"));

        verticalLayout_7->addWidget(minMipLinearLinear);


        filterOptionsGroupBox->addWidget(minFilterBox);


        horizontalLayout->addWidget(filterGroupBox);

        mainView = new MainView(centralWidget);
        mainView->setObjectName(QString::fromUtf8("mainView"));
        mainView->setMinimumSize(QSize(580, 0));

        horizontalLayout->addWidget(mainView);

        settingsBox2 = new QGroupBox(centralWidget);
        settingsBox2->setObjectName(QString::fromUtf8("settingsBox2"));
        settingsBox2->setMaximumSize(QSize(240, 16777215));
        shadingSettings = new QVBoxLayout(settingsBox2);
        shadingSettings->setSpacing(6);
        shadingSettings->setContentsMargins(11, 11, 11, 11);
        shadingSettings->setObjectName(QString::fromUtf8("shadingSettings"));
        lightingBox = new QGroupBox(settingsBox2);
        lightingBox->setObjectName(QString::fromUtf8("lightingBox"));
        lightBox = new QVBoxLayout(lightingBox);
        lightBox->setSpacing(6);
        lightBox->setContentsMargins(11, 11, 11, 11);
        lightBox->setObjectName(QString::fromUtf8("lightBox"));
        ambientLabel = new QLabel(lightingBox);
        ambientLabel->setObjectName(QString::fromUtf8("ambientLabel"));

        lightBox->addWidget(ambientLabel);

        AmbientSlider = new QSlider(lightingBox);
        AmbientSlider->setObjectName(QString::fromUtf8("AmbientSlider"));
        AmbientSlider->setMaximum(100);
        AmbientSlider->setValue(30);
        AmbientSlider->setOrientation(Qt::Horizontal);

        lightBox->addWidget(AmbientSlider);

        diffuseLabel = new QLabel(lightingBox);
        diffuseLabel->setObjectName(QString::fromUtf8("diffuseLabel"));

        lightBox->addWidget(diffuseLabel);

        DiffuseSlider = new QSlider(lightingBox);
        DiffuseSlider->setObjectName(QString::fromUtf8("DiffuseSlider"));
        DiffuseSlider->setMaximum(100);
        DiffuseSlider->setValue(70);
        DiffuseSlider->setOrientation(Qt::Horizontal);

        lightBox->addWidget(DiffuseSlider);

        specularLabel = new QLabel(lightingBox);
        specularLabel->setObjectName(QString::fromUtf8("specularLabel"));

        lightBox->addWidget(specularLabel);

        SpecularSlider = new QSlider(lightingBox);
        SpecularSlider->setObjectName(QString::fromUtf8("SpecularSlider"));
        SpecularSlider->setMaximum(100);
        SpecularSlider->setValue(99);
        SpecularSlider->setOrientation(Qt::Horizontal);

        lightBox->addWidget(SpecularSlider);

        specularExpLabel = new QLabel(lightingBox);
        specularExpLabel->setObjectName(QString::fromUtf8("specularExpLabel"));

        lightBox->addWidget(specularExpLabel);

        SpecExpSlider = new QSlider(lightingBox);
        SpecExpSlider->setObjectName(QString::fromUtf8("SpecExpSlider"));
        SpecExpSlider->setMinimum(1);
        SpecExpSlider->setMaximum(256);
        SpecExpSlider->setValue(32);
        SpecExpSlider->setOrientation(Qt::Horizontal);

        lightBox->addWidget(SpecExpSlider);

        lightColorBox = new QGroupBox(lightingBox);
        lightColorBox->setObjectName(QString::fromUtf8("lightColorBox"));
        LightColorBox = new QHBoxLayout(lightColorBox);
        LightColorBox->setSpacing(6);
        LightColorBox->setContentsMargins(11, 11, 11, 11);
        LightColorBox->setObjectName(QString::fromUtf8("LightColorBox"));
        red = new QSpinBox(lightColorBox);
        red->setObjectName(QString::fromUtf8("red"));
        red->setMaximum(255);
        red->setValue(255);

        LightColorBox->addWidget(red);

        green = new QSpinBox(lightColorBox);
        green->setObjectName(QString::fromUtf8("green"));
        green->setMaximum(255);
        green->setValue(255);

        LightColorBox->addWidget(green);

        blue = new QSpinBox(lightColorBox);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setMaximum(255);
        blue->setValue(255);

        LightColorBox->addWidget(blue);


        lightBox->addWidget(lightColorBox);

        lightPosLabel = new QLabel(lightingBox);
        lightPosLabel->setObjectName(QString::fromUtf8("lightPosLabel"));

        lightBox->addWidget(lightPosLabel);

        lightPosLabelBox = new QHBoxLayout();
        lightPosLabelBox->setSpacing(6);
        lightPosLabelBox->setObjectName(QString::fromUtf8("lightPosLabelBox"));
        xLabel = new QLabel(lightingBox);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));
        xLabel->setMinimumSize(QSize(12, 0));
        xLabel->setMaximumSize(QSize(8, 16777215));

        lightPosLabelBox->addWidget(xLabel);

        yLabel = new QLabel(lightingBox);
        yLabel->setObjectName(QString::fromUtf8("yLabel"));
        yLabel->setMaximumSize(QSize(12, 16777215));

        lightPosLabelBox->addWidget(yLabel);

        zLabel = new QLabel(lightingBox);
        zLabel->setObjectName(QString::fromUtf8("zLabel"));
        zLabel->setMaximumSize(QSize(12, 16777215));

        lightPosLabelBox->addWidget(zLabel);


        lightBox->addLayout(lightPosLabelBox);

        lightPosBox = new QHBoxLayout();
        lightPosBox->setSpacing(6);
        lightPosBox->setObjectName(QString::fromUtf8("lightPosBox"));
        XSLider = new QSlider(lightingBox);
        XSLider->setObjectName(QString::fromUtf8("XSLider"));
        XSLider->setMinimum(-100);
        XSLider->setMaximum(100);
        XSLider->setOrientation(Qt::Vertical);

        lightPosBox->addWidget(XSLider);

        YSLider = new QSlider(lightingBox);
        YSLider->setObjectName(QString::fromUtf8("YSLider"));
        YSLider->setMinimum(-100);
        YSLider->setMaximum(100);
        YSLider->setOrientation(Qt::Vertical);

        lightPosBox->addWidget(YSLider);

        ZSLider = new QSlider(lightingBox);
        ZSLider->setObjectName(QString::fromUtf8("ZSLider"));
        ZSLider->setMinimumSize(QSize(0, 50));
        ZSLider->setMinimum(-100);
        ZSLider->setMaximum(100);
        ZSLider->setValue(100);
        ZSLider->setOrientation(Qt::Vertical);

        lightPosBox->addWidget(ZSLider);


        lightBox->addLayout(lightPosBox);


        shadingSettings->addWidget(lightingBox);

        materialBox = new QGroupBox(settingsBox2);
        materialBox->setObjectName(QString::fromUtf8("materialBox"));
        box = new QVBoxLayout(materialBox);
        box->setSpacing(6);
        box->setContentsMargins(11, 11, 11, 11);
        box->setObjectName(QString::fromUtf8("box"));
        DiffuseTex = new QCheckBox(materialBox);
        DiffuseTex->setObjectName(QString::fromUtf8("DiffuseTex"));

        box->addWidget(DiffuseTex);

        SpecularTex = new QCheckBox(materialBox);
        SpecularTex->setObjectName(QString::fromUtf8("SpecularTex"));

        box->addWidget(SpecularTex);

        NormalTex = new QCheckBox(materialBox);
        NormalTex->setObjectName(QString::fromUtf8("NormalTex"));

        box->addWidget(NormalTex);

        multiplierBox = new QGroupBox(materialBox);
        multiplierBox->setObjectName(QString::fromUtf8("multiplierBox"));
        normalIntensityBox = new QVBoxLayout(multiplierBox);
        normalIntensityBox->setSpacing(6);
        normalIntensityBox->setContentsMargins(11, 11, 11, 11);
        normalIntensityBox->setObjectName(QString::fromUtf8("normalIntensityBox"));
        specularMultLabel = new QLabel(multiplierBox);
        specularMultLabel->setObjectName(QString::fromUtf8("specularMultLabel"));

        normalIntensityBox->addWidget(specularMultLabel);

        SpecularMultiplier = new QDoubleSpinBox(multiplierBox);
        SpecularMultiplier->setObjectName(QString::fromUtf8("SpecularMultiplier"));
        SpecularMultiplier->setValue(1.000000000000000);

        normalIntensityBox->addWidget(SpecularMultiplier);

        normalMultLabel = new QLabel(multiplierBox);
        normalMultLabel->setObjectName(QString::fromUtf8("normalMultLabel"));

        normalIntensityBox->addWidget(normalMultLabel);

        NormalMultiplier = new QDoubleSpinBox(multiplierBox);
        NormalMultiplier->setObjectName(QString::fromUtf8("NormalMultiplier"));
        NormalMultiplier->setMinimum(0.000000000000000);
        NormalMultiplier->setMaximum(5.000000000000000);
        NormalMultiplier->setSingleStep(0.100000000000000);
        NormalMultiplier->setValue(1.000000000000000);

        normalIntensityBox->addWidget(NormalMultiplier);


        box->addWidget(multiplierBox);


        shadingSettings->addWidget(materialBox);


        horizontalLayout->addWidget(settingsBox2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        settingsBox->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        selectedLabel->setText(QApplication::translate("MainWindow", "Selected Object: ", nullptr));
        selectedObjectLabel->setText(QApplication::translate("MainWindow", "Nothing selected..", nullptr));
        verticalGroupBox->setTitle(QApplication::translate("MainWindow", "Animation", nullptr));
        animationCheckBox->setText(QApplication::translate("MainWindow", "Enabled", nullptr));
        resetAnimationButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        rotationBox->setTitle(QApplication::translate("MainWindow", "Rotation", nullptr));
#ifndef QT_NO_TOOLTIP
        RotationDialX->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the X-axis</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialY->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Y-axis</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialZ->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Z-axis</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ResetRotationButton->setText(QApplication::translate("MainWindow", "Reset Rotation", nullptr));
        scalingBox->setTitle(QApplication::translate("MainWindow", "Scaling", nullptr));
        ResetScaleButton->setText(QApplication::translate("MainWindow", "Reset Scaling", nullptr));
        shadingBox->setTitle(QApplication::translate("MainWindow", "Shading", nullptr));
        PhongButton->setText(QApplication::translate("MainWindow", "Pho&ng", nullptr));
        NormalButton->setText(QApplication::translate("MainWindow", "Nor&mal", nullptr));
        GouraudButton->setText(QApplication::translate("MainWindow", "&Gouraud", nullptr));
        WaterButton->setText(QApplication::translate("MainWindow", "Water", nullptr));
        verticalGroupBox1->setTitle(QApplication::translate("MainWindow", "Texturing", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        showFiltersButton->setText(QApplication::translate("MainWindow", "Show Filter Options", nullptr));
        moreOptionsButton->setText(QApplication::translate("MainWindow", "More Options..", nullptr));
        anisotropicFilter->setText(QApplication::translate("MainWindow", "Anisotropic  Filtering", nullptr));
        wrappingBox->setTitle(QApplication::translate("MainWindow", "Wrapping Method", nullptr));
        wrapRepeat->setText(QApplication::translate("MainWindow", "GL_REPEAT", nullptr));
        wrapMirror->setText(QApplication::translate("MainWindow", "GL_MIRRORED_REPEAT", nullptr));
        wrapEdgeClamp->setText(QApplication::translate("MainWindow", "GL_CLAMP_TO_EDGE", nullptr));
        wrapBorderClamp->setText(QApplication::translate("MainWindow", "GL_CLAMP_TO_BORDER", nullptr));
        maxFilterBox->setTitle(QApplication::translate("MainWindow", "Magnifying Method", nullptr));
        maxNearest->setText(QApplication::translate("MainWindow", "GL_NEAREST", nullptr));
        maxLinear->setText(QApplication::translate("MainWindow", "GL_LINEAR", nullptr));
        minFilterBox->setTitle(QApplication::translate("MainWindow", "Minifying Method", nullptr));
        minNearest->setText(QApplication::translate("MainWindow", "GL_NEAREST", nullptr));
        minLinear->setText(QApplication::translate("MainWindow", "GL_LINEAR", nullptr));
        minMipNearestNearest->setText(QApplication::translate("MainWindow", "GL_NEAREST_MIPMAP_NEAREST", nullptr));
        minMipNearestLinear->setText(QApplication::translate("MainWindow", "GL_NEAREST_MIPMAP_LINEAR", nullptr));
        minMipLinearNearest->setText(QApplication::translate("MainWindow", "GL_LINEAR_MIPMAP_NEAREST", nullptr));
        minMipLinearLinear->setText(QApplication::translate("MainWindow", "GL_LINEAR_MIPMAP_LINEAR", nullptr));
        lightingBox->setTitle(QApplication::translate("MainWindow", "Lighting", nullptr));
        ambientLabel->setText(QApplication::translate("MainWindow", "Ambient", nullptr));
        diffuseLabel->setText(QApplication::translate("MainWindow", "Diffuse", nullptr));
        specularLabel->setText(QApplication::translate("MainWindow", "Specular", nullptr));
        specularExpLabel->setText(QApplication::translate("MainWindow", "Specular Exponent", nullptr));
        lightColorBox->setTitle(QApplication::translate("MainWindow", "Light Color", nullptr));
        lightPosLabel->setText(QApplication::translate("MainWindow", "Light Position", nullptr));
        xLabel->setText(QApplication::translate("MainWindow", "x", nullptr));
        yLabel->setText(QApplication::translate("MainWindow", "y", nullptr));
        zLabel->setText(QApplication::translate("MainWindow", "z", nullptr));
        materialBox->setTitle(QApplication::translate("MainWindow", "Material", nullptr));
        DiffuseTex->setText(QApplication::translate("MainWindow", "Diffuse Texture", nullptr));
        SpecularTex->setText(QApplication::translate("MainWindow", "Specular Map", nullptr));
        NormalTex->setText(QApplication::translate("MainWindow", "Normal Map", nullptr));
        specularMultLabel->setText(QApplication::translate("MainWindow", "Specular Multiplier", nullptr));
        normalMultLabel->setText(QApplication::translate("MainWindow", "Normal Multiplier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
