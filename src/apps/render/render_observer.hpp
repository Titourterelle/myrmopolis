#pragma once

#include "observer.hpp"
#include "snapshot.hpp"

#include "hex_grid.hpp"
#include "render_utils.hpp"
    
#include <map>
#include <set>
#include <utility>
#include <string>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

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
        enum class FoodIntesity;

        void renderFrames(RenderQuality quality);
        void createStepFrames(const myrmo::snapshot::Snapshot &snapshot, const HexGrid &grid) const;
        void drawAnts(sf::RenderTexture &frame_texture, sf::Sprite &ant_sprite, const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> &ants_deplacements, float t) const;
        
        std::set<sf::Vector2i, Vector2iCompare> getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        std::map<sf::Vector2i, FoodIntesity, Vector2iCompare> getTileFoodIntensity(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        std::vector<std::pair<sf::Vector2i, sf::Vector2i>> getAntsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        
        std::string framePath(size_t index) const noexcept;
        void encodeVideo() const;
        void clean() const noexcept;


        std::pair<unsigned int, unsigned int> resolution;
        
        const unsigned int fps{30};
        const unsigned int frame_per_step{15};
        const std::string save_dir{"./render_save"};
        const std::string frames_dir;

        sf::Texture ant_image;
};