#include "NoRender.h"
#include "../pch.h"

using namespace std;
NoRender::NoRender() : IModule(0, Category::VISUAL, "Un-Rendering or un-image synthesis is the process of removing a photorealistic or non-photorealistic image from a 2D or 3D model by means of a computer program. The resulting image is referred to as the render.") {
    registerBoolSetting("BlockEntities", &blockEntities, blockEntities);
    registerBoolSetting("Particles", &particles, particles);
    registerBoolSetting("Entities", &entities, entities);
}

const char* NoRender::getRawModuleName() {
    return "NoRender";
}

const char* NoRender::getModuleName() {
    return "NoRender";
}