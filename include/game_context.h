#pragma once

namespace rgp {
    class RendererEngine;
    class TextureEngine;
    class TextEngine;
    class InputEngine;
    class FontFactory;
    class TextFactory;

    struct GameContext {
        RendererEngine& renderer;
        TextureEngine& textureEngine;
        TextEngine& textEngine;
        InputEngine& inputEngine;
        FontFactory& fontFactory;
        TextFactory& textFactory;
    };
}

