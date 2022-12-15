#include <CanvasTriangle.h>
#include "../render/RasterisedRenderer.h"
#include <algorithm>

uint32_t textureMap(const glm::vec3 &bary, const TextureMap &textureMap, const std::array<CanvasPoint, 3> &vertices, double zInv) {
#ifdef DISABLE_PERSPECTIVE_CORRECTION
    auto pix = (int32_t) round(idx * textureMap.width);
    auto piy = (int32_t) round(idy * textureMap.height);
    auto idx = bary[0] * vertices[0].texturePoint.x + bary[1] * vertices[1].texturePoint.x + bary[2] * vertices[2].texturePoint.x;
    auto idy = bary[0] * vertices[0].texturePoint.y + bary[1] * vertices[1].texturePoint.y + bary[2] * vertices[2].texturePoint.y;
    return textureMap.get_pixel(pix, piy);
#else

    auto u = (bary[0] * vertices[0].texturePoint.x / vertices[0].depth) +
            (bary[1] * vertices[1].texturePoint.x / vertices[1].depth) +
            (bary[2] * vertices[2].texturePoint.x / vertices[2].depth);
    auto v = (bary[0] * vertices[0].texturePoint.y / vertices[0].depth) +
            (bary[1] * vertices[1].texturePoint.y / vertices[1].depth) +
            (bary[2] * vertices[2].texturePoint.y / vertices[2].depth);

    auto pix = (int32_t) round(u * textureMap.width / zInv);
    auto piy = (int32_t) round(v * textureMap.height / zInv);
    return textureMap.getPixel(pix, piy);
#endif
}

void RasterisedRenderer::draw(DrawingWindow &window, Camera &camera, const std::vector<ModelTriangle> &triangles,
                              LightingConfiguration &lighting) {
    auto buffer = DepthBufferedWindow(window);
    for (auto &triangle: triangles) {
        auto t = CanvasTriangle::fromModelTriangle(triangle, camera, (float) window.width, (float) window.height);

        if (!t.isInBox(0, (int32_t) buffer.getWidth(), 0, (int32_t) buffer.getHeight())) continue;
        if (t.getFillColour().has_value() || t.getTextureMap().has_value()) {
            auto &vertices = t.getVertices();
            auto minY = (int32_t) std::min({vertices[0].y, vertices[1].y, vertices[2].y});
            auto maxY = (int32_t) std::max({vertices[0].y, vertices[1].y, vertices[2].y});

            auto xs = t.mapYsToXs();
            std::map<int32_t, std::tuple<int32_t, int32_t>> map;
            for(const auto& i: xs) {
                int32_t min = *std::min_element( std::begin(i.second), std::end(i.second) );
                int32_t max = *std::max_element( std::begin(i.second), std::end(i.second) );
                map[i.first] = std::tuple(min, max);
            }

            auto cappedMinY = std::max(minY, 0);
            auto cappedMaxY = std::min(maxY, (int32_t) buffer.getHeight());

            for (int32_t y = cappedMinY; y < cappedMaxY; y++) {
                auto minX = std::get<0>(map[y]);
                auto maxX = std::get<1>(map[y]);
                auto cappedMinX = std::max(minX, 0);
                auto cappedMaxX = std::min(maxX, (int32_t) buffer.getWidth());
                for (int32_t x = cappedMinX; x < cappedMaxX; ++x) {
                    auto bary = t.computeBarycentricCoordinates((float) x, (float) y);
                    auto zInv = (1.0 / vertices[0].depth * bary[0]) + (1.0 / vertices[1].depth * bary[1]) + (1.0 / vertices[2].depth * bary[2]);

                    if (t.getTextureMap().has_value()) {
                        auto pidxel = textureMap(bary, t.getTextureMap().value(), vertices, zInv);
                        buffer.setPixelColour(x, y, zInv, pidxel);
                    } else if (t.getFillColour().has_value()) {
                        buffer.setPixelColour(x, y, zInv, t.getFillColour()->sdlValue());
                    }

                }
            }
        }
    }
}
