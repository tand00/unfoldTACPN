#ifndef SMCEXPRESSIONS_H
#define SMCEXPRESSIONS_H

#include "Expressions.h"

namespace unfoldtacpn::PQL {

    struct SMCSettings {
        enum SMCBoundType { TimeBound, StepBound };
        enum SMCSemantics { Weak, Strong };
        SMCBoundType boundType;
        int bound;
        float falsePositives;
        float falseNegatives;
        float indifferenceRegionUp;
        float indifferenceRegionDown;
        float confidence;
        float estimationIntervalWidth;
        bool compareToFloat;
        float geqThan;
        SMCSemantics semantics;
    };

    class ProbaCondition : public SimpleQuantifierCondition {
    public:
        ProbaCondition(SMCSettings settings, Condition_ptr cond)
        : SimpleQuantifierCondition(cond) {
            _settings = settings;
        }
        void analyze(NamingContext& context) override;
        virtual const SMCSettings settings() const { return _settings; }
    protected:
        SMCSettings _settings;
    };

    class PFCondition : public ProbaCondition {
    public:
        using ProbaCondition::ProbaCondition;
        void visit(Visitor&) const override;
    };

    class PGCondition : public ProbaCondition {
    public:
        using ProbaCondition::ProbaCondition;
        void visit(Visitor&) const override;
    };

}

#endif