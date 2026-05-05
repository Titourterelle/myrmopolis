#pragma once

#include "observer.hpp"
#include "snapshot.hpp"

#include "hex_grid.hpp"
    
#include <set>
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
        std::string framePath(size_t index) const noexcept;

        sf::Image createFrame(const myrmo::snapshot::Snapshot &snapshot, const HexGrid &grid) const;
        std::set<std::pair<int, int>> getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        std::set<std::pair<int, int>> getAntsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept;

        void encodeVideo() const;

        void clean() const noexcept;


        std::pair<unsigned int, unsigned int> resolution;
        
        const unsigned int fps{1};
        const std::string save_dir{"./render_save"};
        const std::string frames_dir;
};