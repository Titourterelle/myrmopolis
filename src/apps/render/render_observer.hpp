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
        struct AntVisual {
            sf::Vector2i previous_tile;
            sf::Vector2i current_tile;

            sf::Vector2f previous_offset;
            sf::Vector2f current_offset;
        };

        void renderFrames(RenderQuality quality);
        void createStepFrames(const HexGrid &grid);
        void drawAnts(sf::RenderTexture &frame_texture, sf::Sprite &ant_sprite, float t) const;
        
        std::set<sf::Vector2i, Vector2iCompare> getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        std::map<sf::Vector2i, FoodIntesity, Vector2iCompare> getTileFoodIntensity(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        std::set<unsigned int> updateAntsCoords(const myrmo::snapshot::Snapshot &snapshot) noexcept;
        void updateAntsOffsets(std::set<unsigned int> new_ants, const HexGrid &grid) noexcept;

        std::string framePath(size_t index) const noexcept;
        void encodeVideo() const;
        void clean() const noexcept;


        std::pair<unsigned int, unsigned int> resolution;
        const unsigned int fps{30};
        const unsigned int frame_per_step{15};
        const std::string save_dir{"./render_save"};
        const std::string frames_dir;

        sf::Texture ant_image;
        myrmo::snapshot::Snapshot previous_snapshot;
        myrmo::snapshot::Snapshot current_snapshot;
        std::map<unsigned int, AntVisual> ants_by_id;
};