#ifndef ACFTMODEL_H
#define ACFTMODEL_H

#include <QString>

/** Describes a model of aircraft */
class AcftModel
{
public:
    AcftModel() = default;
    /** New aircraft model, quite poor, but enough to make a schedule
     * @param n name of the model
     * @param f frequency, number of flights per day
     * @param c number of members in a crew */
    AcftModel(const QString& n, const int f, const int c);

    /** Creates a new Acftmodel from an instance returned by the database */
    //AcftModel(AcftModelDb amdb);

    /** Gives the maximum number of flights per day for this model of
     * aircraft */
    int getFreqMax();

    /** @returns name of the model */
    QString getName();
private:
    enum class AvailableModels { a, B727, B737 };

    AvailableModels m_name;

    /** Converts string to AvailableModels */
    void setName(const QString& n);
    int m_freqMax;
    int m_nbOp;
    int m_nbTot;
    int m_crew;
};

#endif // ACFTMODEL_H
