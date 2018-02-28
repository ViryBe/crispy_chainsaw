#ifndef ACFTMODEL_H
#define ACFTMODEL_H

#include <QString>

/** Describes a model of aircraft */
class AcftModel
{
public:
    AcftModel();

    /** Gives the maximum number of flights per day for this model of
     * aircraft */
    int getFreqMax();

    /** @returns name of the model */
    QString getName();
private:
    enum class AvailableModels { B727, B737 };

    AvailableModels m_name;
    int m_freqMax;
    int m_nbOp;
    int m_nbTot;
};

#endif // ACFTMODEL_H
