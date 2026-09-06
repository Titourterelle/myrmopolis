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

class RenderObserver : public myrmo::Observer {
    public:
        explicit RenderObserver();

        void observe(const myrmo::snapshot::Snapshot &snapshot) override;
        void generateVideo(const RenderSettings &render_settings);

    private:
        enum class FoodIntensity;
        struct AntVisual {
            sf::Vector2i previous_tile;
            sf::Vector2i current_tile;

            sf::Vector2f previous_offset;
            sf::Vector2f current_offset;
        };

        void renderFrames();
        void createStepFrames(const HexGrid &grid);
        void drawAnts(sf::RenderTexture &frame_texture, sf::Sprite &ant_sprite, float t) const;

        static std::set<sf::Vector2i, Vector2iCompare> getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) noexcept;
        static std::map<sf::Vector2i, FoodIntensity, Vector2iCompare> getTileFoodIntensity(const myrmo::snapshot::Snapshot &snapshot) noexcept;
        std::set<unsigned int> updateAntsCoords(const myrmo::snapshot::Snapshot &snapshot) noexcept;
        void updateAntsOffsets(const std::set<unsigned int>& new_ants, const HexGrid &grid) noexcept;

        std::string framePath(size_t index) const noexcept;
        void encodeVideo() const;
        void clean() const noexcept;


        RenderSettings settings;

        std::pair<unsigned int, unsigned int> resolution;

        sf::Texture ant_image;
        myrmo::snapshot::Snapshot previous_snapshot;
        myrmo::snapshot::Snapshot current_snapshot;
        std::map<unsigned int, AntVisual> ants_by_id;
};