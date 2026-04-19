#include "render_observer.hpp"

#include <SFML/Graphics/Color.hpp>
#include <stdexcept>
#include <string>

#include <SFML/Graphics/Image.hpp>

const std::string FRAMES_DIR = "/frames";
const std::string OUTPUT_DIR = "/output";

// Public

RenderObserver::RenderObserver() : frames_dir(save_dir + FRAMES_DIR), output_dir(save_dir + OUTPUT_DIR) {
}

void RenderObserver::observe(const myrmo::snapshot::Snapshot &snapshot) {
    snapshots.push_back(snapshot);
}

void RenderObserver::generateVideo() const {
    try {
        renderFrames();
        encodeVideo();
    } catch (const std::exception& e) {
        clean();
        throw;
    }
    clean();
}

// Private

void RenderObserver::renderFrames() const {
    std::filesystem::create_directories(frames_dir);

    for (size_t i = 0; i < snapshots.size(); ++i) {
        sf::Image frame = createFrame(snapshots[i]);
        
        if (!frame.saveToFile(framePath(i))) {
            throw std::runtime_error("Can't save the frame");
        }
    }
}

sf::Image RenderObserver::createFrame(const myrmo::snapshot::Snapshot &snapshot) const {
    sf::Image img{{dimensions.first, dimensions.second}, sf::Color::Black};
    return img;
}

std::string RenderObserver::framePath(size_t index) const noexcept {
    return std::format("{}/frame_{:06d}.png", frames_dir, index);
}

void RenderObserver::encodeVideo() const {

}

void RenderObserver::clean() const noexcept {
    if (std::filesystem::exists(frames_dir)) {
        std::filesystem::remove_all(frames_dir);
    }
}