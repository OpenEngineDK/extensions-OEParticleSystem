#ifndef _TEXTURE_PARTICLE_
#define _TEXTURE_PARTICLE_

#include<Resources/ITextureResource.h>

using OpenEngine::Resources::ITextureResourcePtr;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Texture : T {
        ITextureResourcePtr texture;
        float rotation;
    };
}
}

#endif
