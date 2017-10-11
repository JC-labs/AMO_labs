#ifndef ABSTRACTINTERPOLATEDFUNCTION_H
#define ABSTRACTINTERPOLATEDFUNCTION_H

class DifferentSizesException {};

class AbstractInterpolatedFunction {

public:
    virtual float operator()(const float& arg) =0;
};

#endif // ABSTRACTINTERPOLATEDFUNCTION_H
