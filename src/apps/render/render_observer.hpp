#pragma once

#include "observer.hpp"
#include "snapshot.hpp"

#include <utility>
#include <string>

#include <SFML/Graphics/Image.hpp>

class RenderObserver : public myrmo::Observer {
    public:
        explicit RenderObserver();

        void observe(const myrmo::snapshot::Snapshot &snapshot) override;
        void generateVideo() const;

    private:
        void renderFrames() const;
        sf::Image createFrame(const myrmo::snapshot::Snapshot &snapshot) const;
        std::string framePath(size_t index) const noexcept;

        void encodeVideo() const;

        void clean() const noexcept;


        const std::pair<unsigned int, unsigned int> dimensions{100, 100};
        const unsigned int fps{30};
        const std::string save_dir{"./render_save"};
        const std::string frames_dir;
};