ADD_LIBRARY(Extensions_ParticleSystem
  ParticleSystem/ParticleSystem.cpp
)

TARGET_LINK_LIBRARIES (Extensions_ParticleSystem
		       OpenEngine_Core
		       OpenEngine_Display
		       OpenEngine_Resources
		       OpenEngine_Scene
		       OpenEngine_Logging
		       OpenEngine_Devices
		       OpenEngine_Scene
		       OpenEngine_Utils
		       OpenEngine_Geometry
		       OpenEngine_Renderers_OpenGL)
