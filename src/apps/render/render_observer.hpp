#pragma once

#include "observer.hpp"
#include "snapshot.hpp"

#include "hex_grid.hpp"
#include "render_utils.hpp"
    
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class RenderObserver : public myrmo::Observer {
    public:
        explicit RenderObserver();
        ~RenderObserver() override;

        void observe(const myrmo::snapshot::Snapshot &snapshot) override;
        void generateVideo(const RenderSettings &render_settings, const std::string &base_name = "output");
        void generateVideo(const std::vector<RenderSettings> &render_settings);

    private:
        enum class FoodIntensity;
        struct AntVisual;
        struct Board;

        void renderFrames();
        void createStepFrames(const HexGrid &grid);
        void drawAnts(sf::RenderTexture &frame_texture, sf::Sprite &ant_sprite, float t) const;

        static float getCellsRadiusFromQuality(const RenderQuality &quality);

        static std::set<sf::Vector2u, Vector2uCompare> getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) noexcept;
        static std::map<sf::Vector2u, FoodIntensity, Vector2uCompare> getTileFoodIntensity(const myrmo::snapshot::Snapshot &snapshot) noexcept;

        std::set<unsigned int> updateAntsCoords(const myrmo::snapshot::Snapshot &snapshot) const noexcept;
        void updateAntsOffsets(const std::set<unsigned int> &new_ants, const HexGrid &grid) const noexcept;


        std::string framePath(size_t index) const noexcept;
        void encodeVideo(const std::string &name) const;
        void clean() const noexcept;


        sf::Texture ant_image;
        std::pair<unsigned int, unsigned int> resolution;

        std::map<unsigned int, std::unique_ptr<Board>> boards_by_id;

        RenderSettings settings;
        Board* current_board = nullptr;
        myrmo::snapshot::Snapshot* previous_snapshot = nullptr;
        myrmo::snapshot::Snapshot* current_snapshot = nullptr;
};