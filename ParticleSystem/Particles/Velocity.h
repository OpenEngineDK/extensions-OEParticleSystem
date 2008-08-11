#ifndef _VELOCITY_PARTICLE_
#define _VELOCITY_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Velocity : T {
        Vector<3,float> velocity;
    };
}
}

#endif
