#ifndef _FORCES_PARTICLE_
#define _FORCES_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Forces : T {
        Vector<3,float> forces;
    };
}
}

#endif
