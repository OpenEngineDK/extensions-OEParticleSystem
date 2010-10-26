// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include <Renderers/OpenGL/ParticleRenderer.h>

#include <Meta/OpenGL.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {
    
    using namespace ParticleSystem;

    ParticleRenderer::ParticleRenderer(ParticleCollection<RenderParticle>* particles)
        : particles(particles)
    {}

    ParticleRenderer::~ParticleRenderer() {}

    void ParticleRenderer::Handle(RenderingEventArg arg) {
        // @todo: we need to move all this gl specific code into the renderer
        // @todo: also glpushmatrix is too expensive. let's make our own calculations 
        //        of the rotation and position of the quad.

        IRenderer* renderer = arg.canvas.GetRenderer();
        
        glPushAttrib(GL_LIGHTING);
        glDisable(GL_LIGHTING);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
    
        for (particles->iterator.Reset(); 
             particles->iterator.HasNext(); 
             particles->iterator.Next()) {
                
            RenderParticle& particle = particles->iterator.Element();
            ITexture2DPtr texr = particle.texture;
                
            //Set texture
            if (texr != NULL) {
                if (texr->GetID() == 0) {
                    renderer->LoadTexture(texr);
                    //logger.info << texr->GetID() << logger.end;
                }
                glBindTexture(GL_TEXTURE_2D, texr->GetID());
            }
                
            else {
                glBindTexture(GL_TEXTURE_2D, 0);
            }
                
            glPushMatrix();
            glTranslatef(particle.position[0], particle.position[1], particle.position[2]);
                
            // billboard
            float modelview[16];
            glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
            modelview[0] = modelview[5] = modelview[10] = 1.0;
            modelview[1] = modelview[2] = modelview[4] = 
                modelview[6] = modelview[8] = modelview[9] = 0.0; 
            glLoadMatrixf(modelview);
                
            // apply quad transformations
            glRotatef(particle.rotation, 0,0,1);
            float scale = particle.size;
            glScalef(scale,scale,scale);
            float c[4];
            particle.color.ToArray(c);
            glColor4fv(c);
                
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1.0, -1.0, 0.0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1.0, 1.0, 0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(1, 1, 0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1, -1, 0);
            glEnd();
                
            glPopMatrix();
        }
        glPopAttrib();
        glDisable(GL_BLEND);
        CHECK_FOR_GL_ERROR();
            
        // render subnodes
        // VisitSubNodes(v);      
    }
}
}
}
