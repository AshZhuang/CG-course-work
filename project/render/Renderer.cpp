#include "../render/Renderer.h"
#include "../render/WireframeRenderer.h"
#include "../render/RasterisedRenderer.h"
#include "../render/RaytracedRenderer.h"

std::unique_ptr<Renderer> Renderer::getRenderer(ConcreteRenderer type) {
    switch (type) {
        case ConcreteRenderer::Wireframe:
            return std::make_unique<WireframeRenderer>();
        case ConcreteRenderer::Rasterised:
            return std::make_unique<RasterisedRenderer>();
        case ConcreteRenderer::Raytraced:
            return std::make_unique<RaytracedRenderer>();
        default:
            throw std::runtime_error("Invalid renderer");
    }
}
