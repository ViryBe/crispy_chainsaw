#include "acftmodel.h"

AcftModel::AcftModel()
{
}

AcftModel::AcftModel(const QString& name, const int freq, const int crew)
{
    if (name == "b727" || name == "B727") {
        m_name = AvailableModels::B727;
    }
    else if (name == "b737" || name == "B737") {
        m_name = AvailableModels::B737;
    }
    else if (name == "a") {
        m_name = AvailableModels::a;
    }

    m_freqMax = freq;
    m_crew = crew;
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
