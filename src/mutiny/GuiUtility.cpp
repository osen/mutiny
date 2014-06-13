#include "GuiUtility.h"
#include "Gui.h"
#include "Matrix4x4.h"
#include "Vector3.h"

namespace mutiny
{

namespace engine
{

void GuiUtility::rotateAroundPivot(float angle, Vector2 pivotPoint)
{
  Matrix4x4 rotMat = Matrix4x4::getTrs(Vector3(0, 0, 0),
    Vector3(0, 0, angle), Vector3(1, 1, 1));

  Matrix4x4 pivotMat = Matrix4x4::getTrs(Vector3(pivotPoint.x, pivotPoint.y, 0),
    Vector3(0, 0, 0), Vector3(1, 1, 1));

  Gui::setMatrix(Gui::getMatrix() * pivotMat * rotMat * pivotMat.inverse());
}

}

}

