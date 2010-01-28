#ifndef _TEXTURE_PARTICLE_
#define _TEXTURE_PARTICLE_

#include <boost/shared_ptr.hpp>

//forward declartion
namespace OpenEngine {
    namespace Resources {
        class ITextureResource;
        typedef boost::shared_ptr<ITextureResource> ITextureResourcePtr;
    }
}

using OpenEngine::Resources::ITextureResourcePtr;

namespace OpenEngine {
namespace ParticleSystem {
    template <class T> struct Texture : T {
        ITextureResourcePtr texture;
        float rotation;
        float spin; // speed of the rotation
    };
}
}

#endif
