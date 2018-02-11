#ifndef ACFTMODEL_H
#define ACFTMODEL_H


class AcftModel
{
public:
    AcftModel();
private:
    enum class AvailableModels { B727, B737 };

    AvailableModels m_name;
    int m_freqMax;
    int m_nbOp;
    int m_nbTot;
};

#endif // ACFTMODEL_H
