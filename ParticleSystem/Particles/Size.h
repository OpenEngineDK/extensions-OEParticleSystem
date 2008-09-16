#ifndef _SIZE_PARTICLE_
#define _SIZE_PARTICLE_

#include<Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Size : T {
        float size;
        float startsize;
    };
}
}

#endif
