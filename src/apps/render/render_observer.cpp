#include "render_observer.hpp"

#include <SFML/Graphics/Color.hpp>

#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string>

#include <SFML/Graphics/Image.hpp>

const std::string FRAMES_DIR = "/frames";

// Public

RenderObserver::RenderObserver() : frames_dir(save_dir + FRAMES_DIR) {
    if (std::system("ffmpeg -version > /dev/null 2>&1") != 0) {
        throw std::runtime_error("FFmpeg not found, please install it");
    }
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
    const std::string command = std::format(
        "ffmpeg -r {} -i {}/frame_%06d.png -c:v libx264 -pix_fmt yuv420p {}/output.mp4 -loglevel error",
        fps,
        frames_dir,
        save_dir
    );

    const int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("FFmpeg failed with code : " + std::to_string(result));
    }
}

void RenderObserver::clean() const noexcept {
    if (std::filesystem::exists(frames_dir)) {
        std::filesystem::remove_all(frames_dir);
    }
}