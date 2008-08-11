#ifndef _COLOR_PARTICLE_
#define _COLOR_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Color : T {
        Vector<4,float> color;
    };
}
}

#endif
