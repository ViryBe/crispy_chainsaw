#ifndef ACFTMODEL_H
#define ACFTMODEL_H


class AcftModel
{
public:
    AcftModel();
private:
    enum class AvailableModels { B727, B737 };

    AvailableModels name;
    int freqMax;
    int nop;
    int ntot;
};

#endif // ACFTMODEL_H
