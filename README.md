# Myrmopolis
A simulation of ant colonies on a 2D board.  
The goal is to model the collective behavior of ants as accurately as possible.
Then, Myrmopolis is an educational project with a scientific focus.  
However, Myrmopolis remains a personal project (to which you can contribute)

<!-- TABLE OF CONTENTS -->
## Table of Content
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Architecture](#architecture)
  * [Configuration file](#configuration-file)
    * [How to use it](#how-to-use-it)
    * [Exemples](#exemples)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites
This project use C++ 23 and [SFML](https://www.sfml-dev.org/fr/) but to build and use this project, you only need :
* Cmake
* [nlohmann json](https://github.com/nlohmann/json)
* FFmpeg (_only to execute the rendering_)

**Arch**:
```sh
sudo pacman -S --needed base-devel cmake nlohmann-json ffmpeg
```
**Debian**:
```sh
sudo apt update
sudo apt install build-essential cmake nlohmann-json3-dev ffmpeg
```

### Installation
<!-- TODO: explicit the installation steps -->
1. Clone the repo
   ```sh
   git clone https://github.com/Titourterelle/myrmopolis.git
   ```

<!-- USAGE EXAMPLES -->
## Usage

### Architecture
<!-- TODO: explain the architecture -->
The project is divided into two section...

### Configuration file
<!-- TODO: fill the configuration file area -->
All the settings must take place in the `config.json` file

#### How to use it

#### Exemples

### Documentation
For more informations, please refer to the [Documentation](doc/DOCUMENTATION.md)

<!-- ROADMAP -->
## Roadmap
See the [open issues](https://github.com/Titourterelle/myrmopolis/issues) for the full list of proposed features (and known issues).


<!-- CONTRIBUTING -->
## Contributing

**Contributions are welcome !**

If you have a suggestion that would make this better, please fork the repo and create a pull request.
You can also simply open an issue with the appropriate tag.

Before starting something, please read the directive in [CONTRIBUTING.md](doc/CONTRIBUTING.md)

<!-- LICENSE -->
## License
Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

<!-- CONTACT -->
## Contact
Titourterelle - [Github](https://github.com/Titourterelle) - titourterelle@gmail.com