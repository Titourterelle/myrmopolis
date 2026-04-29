#pragma once

#include "observer.hpp"
#include "snapshot.hpp"

#include "hex_grid.hpp"
    
#include <utility>
#include <string>

#include <SFML/Graphics/Image.hpp>

enum class RenderQuality {
    Low,
    Medium,
    High
};

class RenderObserver : public myrmo::Observer {
    public:
        explicit RenderObserver();

        void observe(const myrmo::snapshot::Snapshot &snapshot) override;
        void generateVideo(RenderQuality quality);

    private:
        void renderFrames(RenderQuality quality);
        sf::Image createFrame(const myrmo::snapshot::Snapshot &snapshot, const HexGrid &grid) const;
        std::string framePath(size_t index) const noexcept;

        void encodeVideo() const;

        void clean() const noexcept;


        std::pair<unsigned int, unsigned int> resolution;
        
        const unsigned int fps{30};
        const std::string save_dir{"./render_save"};
        const std::string frames_dir;
};