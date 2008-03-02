#ifndef _POINT_EMITTER_H_
#define _POINT_EMITTER_H_

#include "IEmitter.h"

namespace OpenEngine {
namespace ParticleSystem {

class PointEmitter : public IEmitter {
private:
    Vector<3,float> point;

public:
    PointEmitter(Vector<3,float> point) { this->point = point; }

    Vector<3,float> GetParticlePosition() {
        return point;
    }
};

} //NS ParticleSystem
} //NS OpenEngine

#endif

