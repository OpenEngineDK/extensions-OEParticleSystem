// A general particle renderer using OpenGL
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include <Renderers/IRenderingView.h>
#include <ParticleSystem/ParticleCollection.h>
#include <ParticleSystem/SimpleEmitter.h>
#include <Math/Quaternion.h>
#include <Math/Vector.h>
#include <Scene/EmitterNode.h>
#include <Resources/ITexture2D.h>
#include <Meta/OpenGL.h>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

using Math::Quaternion;
using Math::Vector;
using Scene::EmitterNode;
using ParticleSystem::SimpleEmitter;

// ParticleType must include at least the same template particle
// arguments as RenderParticle
template <class ParticleType>
class ParticleRenderer: public IRenderingView {
private:
    // ParticleSystem::ParticleCollection<ParticleType>* particles;
    IRenderer* renderer;
    Vector<3,float> campos;
public:
    // ParticleRenderer(ParticleSystem::ParticleCollection<ParticleType>* particles) 
    // : particles(particles)
    ParticleRenderer(): renderer(NULL)
    {}

    virtual ~ParticleRenderer() {
    }

    void Handle(RenderingEventArg arg) {
        renderer = arg.canvas.GetRenderer();
        campos = arg.canvas.GetViewingVolume()->GetPosition();
        arg.canvas.GetScene()->Accept(*this);
    }

    void VisitEmitterNode(EmitterNode* node) {
        SimpleEmitter* emitter = node->GetEmitter();
        ParticleSystem::ParticleCollection<ParticleType>* particles = emitter->GetParticles();

        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFunc(GL_ONE,GL_ONE); // additive blending
        glBlendFunc(GL_SRC_ALPHA,GL_ONE); // additive blending
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);

        //Set texture
        ITexture2DPtr texr = emitter->GetTexture();
        if (texr.get() != NULL) {
            if (texr->GetID() == 0) {
                // maybe only load texture on intialize
                renderer->LoadTexture(texr);
            }
            glBindTexture(GL_TEXTURE_2D, texr->GetID());
        }
        else {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        for (particles->iterator.Reset(); 
             particles->iterator.HasNext(); 
             particles->iterator.Next()) {
            
            ParticleType& particle = particles->iterator.Element();

            Vector<3,float> lookat(0.0,0.0,1.0);
            Vector<3,float> up(1.0, 0.0, 0.0);
            Vector<3,float> right(0.0,1.0,0.0);

            Vector<3,float> parToCam = campos - particle.position;
            parToCam.Normalize();

            const float dot = parToCam * lookat;
            const float angle = acosf(dot);
            Quaternion<float> rot(angle, lookat % parToCam);

            // logger.info << "dot: " << dot << logger.end;
            // logger.info << "angle: " << angle << logger.end;
            // logger.info << "cross: " << lookat % parToCam << logger.end;

            // face the cam
            lookat = rot.RotateVector(lookat);
            up     = rot.RotateVector(up);
            right  = rot.RotateVector(right);

            // rotate billboard
            rot = Quaternion<float>(particle.rotation, lookat);
            up     = rot.RotateVector(up);
            right  = rot.RotateVector(right);

            // scale 
            up = up * particle.size;
            right = right * particle.size;
            
            // glPushMatrix();
            // glTranslatef(particle.position[0], particle.position[1], particle.position[2]);
                
            // // billboard
            // float modelview[16];
            // glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
            // modelview[0] = modelview[5] = modelview[10] = 1.0;
            // modelview[1] = modelview[2] = modelview[4] = 
            //     modelview[6] = modelview[8] = modelview[9] = 0.0; 
            // glLoadMatrixf(modelview);
                
            // // apply quad transformations
            // glRotatef(particle.rotation, 0,0,1);
            // float scale = particle.size;
            // glScalef(scale,scale,scale);
            float c[4];
            particle.color.ToArray(c);
            glColor4fv(c);
                
            // glBegin(GL_QUADS);
            // glTexCoord2f(0.0, 0.0);
            // glVertex3f(-1.0, -1.0, 0.0);
            // glTexCoord2f(0.0, 1.0);
            // glVertex3f(-1.0, 1.0, 0);
            // glTexCoord2f(1.0, 1.0);
            // glVertex3f(1, 1, 0);
            // glTexCoord2f(1.0, 0.0);
            // glVertex3f(1, -1, 0);
            // glEnd();

            const Vector<3,float> start = particle.position - (up*0.5) - (right*0.5);
            Vector<3,float> p;

            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            p = start + up;
            glVertex3f(p[0], p[1], p[2]);
            glTexCoord2f(0.0, 1.0);
            p += right;
            glVertex3f(p[0], p[1], p[2]);
            glTexCoord2f(1.0, 1.0);
             p = start + right;
            glVertex3f(p[0], p[1], p[2]);
            glTexCoord2f(1.0, 0.0);
            p = start;
            glVertex3f(p[0], p[1], p[2]);
            glEnd();
            // glPopMatrix();

        }
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        CHECK_FOR_GL_ERROR();

        node->VisitSubNodes(*this);
    }

};

}
}
}
