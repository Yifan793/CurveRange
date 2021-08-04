#include "CurveItem.h"
#include "CurveResInfoItem.h"

CurvePaintItem::CurvePaintItem(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo)
    : m_pResInfo(pResInfo), m_dX(dX), m_dY(dY)
{

}

double CurvePaintItem::getPositionX() const
{
    double nWidth = m_pResInfo->getWindowWidth() - lineBorderLeft - lineBorderRight;
    return nWidth / (m_pResInfo->getMaxX() - m_pResInfo->getMinX()) * ( m_dX - m_pResInfo->getMinX()) + lineBorderLeft;
}

double CurvePaintItem::getPositionY() const
{
    double nHeight = m_pResInfo->getWindowHeight() - lineBorderTop - lineBorderBottom;
    double dY = 1.0 * nHeight / (m_pResInfo->getMaxY() - m_pResInfo->getMinY()) * ( m_dY - m_pResInfo->getMinY());
    return m_pResInfo->getWindowHeight() - dY - lineBorderBottom;
}
