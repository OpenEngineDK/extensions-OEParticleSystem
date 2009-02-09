#ifndef _PREVIOUS_POSITION_PARTICLE_
#define _PREVIOUS_POSITION_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct PreviousPosition : T {
        Vector<3,float> previousPosition;
    };
}
}

#endif
