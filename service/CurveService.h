#ifndef CURVESERVICE_H
#define CURVESERVICE_H

#include <memory>

class CurveViewer;
class CurveModel;
class CurveBox2D;
class CurveNotifier;
class CurveService
{
public:
    CurveService();

    void setViewer(std::shared_ptr<CurveViewer> pViewer) { m_pViewer = pViewer; }
    std::shared_ptr<CurveViewer> getViewer() const { return m_pViewer.lock(); }

    void setModel(std::shared_ptr<CurveModel> pModel) { m_pModel = pModel; }
    std::shared_ptr<CurveModel> getModel() const  { return m_pModel.lock(); }

    void setBox2D(std::shared_ptr<CurveBox2D> pBox2D) { m_pBox2D = pBox2D; }
    std::shared_ptr<CurveBox2D> getBox2D() const { return m_pBox2D.lock(); }

    void setNotifier(std::shared_ptr<CurveNotifier> pNotifier) { m_pNotifier = pNotifier; }
    std::shared_ptr<CurveNotifier> getNotifier() const { return m_pNotifier.lock(); }

protected:
    std::weak_ptr<CurveViewer> m_pViewer;
    std::weak_ptr<CurveModel> m_pModel;
    std::weak_ptr<CurveBox2D> m_pBox2D;
    std::weak_ptr<CurveNotifier> m_pNotifier;
};

#endif
