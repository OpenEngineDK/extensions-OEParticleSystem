#ifndef _POSITION_PARTICLE_
#define _POSITION_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Position : T {
        Vector<3,float> position;
    };
}
}

#endif
