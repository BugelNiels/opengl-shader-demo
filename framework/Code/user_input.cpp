#include "mainview.h"
#include "math.h"

#include <QDebug>

// Triggered by pressing a key
void MainView::keyPressEvent(QKeyEvent *ev)
{
   switch(ev->key()) {
        case '1':
           currentSceneIndex = 0;
           window->updateUI(scenes[currentSceneIndex]);
           break;
        case '2':
           if(scenes.size() >= 2) {
               currentSceneIndex = 1;
               window->updateUI(scenes[currentSceneIndex]);
           }
           break;
        case 'W':
            isPressedW = true;
            break;
        case 'S':
            isPressedS = true;
            break;
        case 'A':
            isPressedA = true;
            break;
        case 'D':
            isPressedD = true;
            break;
        case 'E':
            isPressedE = true;
            break;
        case 'Q':
            isPressedQ = true;
            break;
        case 16777249: // cannot find the proper enum, ctrl key
            isPressedDown = true;
            break;
        case 32: // cannot find the proper enum, space key
            isPressedUp = true;
            break;
        case 'Z':
            toggleWireframe();
            break;
        case 16777248: // cannot find the proper enum, shift key
            isPressedShift = true;
            break;
        default:
            // ev->key() is an integer. For alpha numeric characters keys it equivalent with the char value ('A' == 65, '1' == 49)
            // Alternatively, you could use Qt Key enums, see http://doc.qt.io/qt-5/qt.html#Key-enum
            qDebug() << ev->key() << "pressed";
            break;
    }

}

// Triggered by releasing a key
void MainView::keyReleaseEvent(QKeyEvent *ev)
{
    if(!ev->isAutoRepeat()) {
        switch(ev->key()) {
            case 'W':
                isPressedW = false;
                break;
            case 'S':
                isPressedS = false;
                break;
            case 'A':
                isPressedA = false;
                break;
            case 'D':
                isPressedD = false;
                break;
            case 'E':
                isPressedE = false;
                break;
            case 'Q':
                isPressedQ = false;
                break;
            case 16777249:
                isPressedDown = false;
                break;
            case 32:
                isPressedUp = false;
                break;
            case 16777248:
                isPressedShift = false;
                break;
            default:
                // ev->key() is an integer. For alpha numeric characters keys it equivalent with the char value ('A' == 65, '1' == 49)
                // Alternatively, you could use Qt Key enums, see http://doc.qt.io/qt-5/qt.html#Key-enum
                break;
        }
    }
}

// Triggered by clicking two subsequent times on any mouse button
// It also fires two mousePress and mouseRelease events!
void MainView::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse double clicked:" << ev->button();

    update();
}

// Triggered when moving the mouse inside the window (only when the mouse is clicked!)
void MainView::mouseMoveEvent(QMouseEvent *ev)
{
    if(rotatingX) {
        this->dragRotateX(ev->x() - prevMouseX);
    } else if(rotatingY) {
        this->dragRotateY(ev->y() - prevMouseY);
    } else if(fabs(ev->x() - prevMouseX) >= fabs(ev->y() - prevMouseY)) {
        this->dragRotateX(ev->x() - prevMouseX);
        rotatingX = true;
    } else {
        this->dragRotateY(ev->y() - prevMouseY);
        rotatingY = true;
    }
    Scene s = scenes[currentSceneIndex];
    window->updateUI(s);

    update();
}

// Triggered when pressing any mouse button
void MainView::mousePressEvent(QMouseEvent *ev)
{
    prevMouseX = ev->x();
    prevMouseY = ev->y();


    qDebug() << "button pressed:" << ev->button();
    if (ev->button() == Qt::LeftButton) {
        isSelecting = true;
    }

    update();
    // Do not remove the line below, clicking must focus on this widget!
    this->setFocus();
}

// Triggered when releasing any mouse button
void MainView::mouseReleaseEvent(QMouseEvent *ev)
{
    rotatingX = false;
    rotatingY = false;
    qDebug() << "Mouse button released" << ev->button();

    update();
}

// Triggered when clicking scrolling with the scroll wheel on the mouse
void MainView::wheelEvent(QWheelEvent *ev)
{
    // Implement something
    qDebug() << "Mouse wheel:" << ev->delta();

    update();
}
