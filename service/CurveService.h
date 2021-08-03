#ifndef CURVESERVICE_H
#define CURVESERVICE_H

#include <memory>

class CurveViewer;
class CurveService
{
public:
    CurveService();

    void setViewer(std::shared_ptr<CurveViewer> pViewer) { m_pViewer = pViewer; }
    std::shared_ptr<CurveViewer> getViewer() const { return m_pViewer.lock(); }

protected:
    std::weak_ptr<CurveViewer> m_pViewer;
};

#endif
