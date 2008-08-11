#ifndef _ORIENTATION_PARTICLE_
#define _ORIENTATION_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Orientation : T {
        Vector<3,float> orientation;
    };
}
}

#endif
