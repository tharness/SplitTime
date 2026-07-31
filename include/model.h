#ifndef MODEL_H
#define MODEL_H

namespace Stopwatch {

class Model {
public:
    virtual void buildModelFromData(const float* x, const float* y, int count) = 0;
    virtual float predict(float x) = 0;
    virtual float predictInverse(float y) = 0;
    virtual float getConfidence() = 0;
};

}

#endif // MODEL_H