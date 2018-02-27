#include "acftmodel.h"

AcftModel::AcftModel()
{

}

int AcftModel::getFreqMax()
{
    return m_freqMax;
}

QString AcftModel::getName()
{
    QString name;
    if (m_name == AvailableModels::B727) {
        name = "b727";
    }
    else if (m_name == AvailableModels::B737) {
        name = "b737";
    }
    return name;
}
