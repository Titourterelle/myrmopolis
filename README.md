# Myrmopolis
> [!WARNING]
> This project is under construction. If you are not a developer, please wait the first release.
> Of course, if you are curious, you can explore the repository.

A simulation of ant colonies on a 2D board.  
The goal is to model the collective behavior of ants as accurately as possible.
Then, Myrmopolis is an educational project with a scientific focus.  
However, Myrmopolis remains a personal project (to which you can contribute)

<!-- TABLE OF CONTENTS -->
## Table of Content
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
    * [First steps](#first-steps)
    * [System installation](#system-installation)
    * [Run](#run)
* [Usage](#usage)
  * [Architecture](#architecture)
  * [Configuration](#configuration)
    * [How to use it](#how-to-use-it)
    * [Examples](#examples)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites
This project use C++ 23 and [SFML](https://www.sfml-dev.org/fr/) but to build and use this project, you only need :
* Cmake 3.28
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
#### First steps
First, **clone** the repo
```sh
git clone https://github.com/Titourterelle/myrmopolis.git
cd myrmopolis
```
Then, **build** the executable
```sh
cmake --preset release
cmake --build --preset release --target myrmopolis-render
```
You can now **test** the simulation with the default config
```sh
cd build/release
./myrmopolis-render
```

#### System installation
Finally, if you want to **install** the project
```sh
sudo cmake --install build/release/
```

#### Run
You must give a **[configuration](#configuration) file** to the executable
```sh
myrmopolis-render path/to/your/config/file.json
```

<!-- USAGE EXAMPLES -->
## Usage

### Architecture
<!-- TODO: explain the architecture -->
The project is divided into two section...

### Configuration
All the settings must take place in the `config.json` file.

#### How to use it

_For the **simulation core**:_

| Field                              | Type                         | Required | Default | Description                                       |
|------------------------------------|------------------------------|----------|---------|---------------------------------------------------|
| simulation.number_of_boards        | Positive integer             | Yes      |         | The number of simulations with this configuration |
| simulation.board.row               | Positive integer             | Yes      |         | Number of rows in the boards                      |
| simulation.board.column            | Positive integer             | Yes      |         | Number of columns in the boards                   |
| _simulation.colonies[]_            | Array of "Colonies Settings" | Yes      |         | Add each colony with its own settings (see below) |
| simulation.colonies[].name         | String                       | Yes      |         | Use a different name for each colony              |
| simulation.colonies[].initial_ants | Positive integer             | Yes      |         | Set the number of ants for the first step         |

_For the **rendering**:_

| Field                        | Type                          | Required (only for the rendering) | Default | Description                                                    |
|------------------------------|-------------------------------|-----------------------------------|---------|----------------------------------------------------------------|
| _rendering[]_                | Array of "Rendering Settings" | Yes                               |         | Each block creates a distinct output video                     |
| rendering[].fps              | Positive integer              | Yes                               |         | Number of frames per second (change the fluidity)              |
| rendering[].frames_per_step  | Positive integer              | Yes                               |         | Number of frames used to visualize one step (change the speed) |
| rendering[].quality          | "low", "medium" or "high"     | Yes                               |         | Set the rendering quality                                      |
| rendering[].output_directory | String                        | Yes                               |         | Set the directory where the video is created                   |

#### Examples
<details>
  <summary>Minimal configuration</summary>

```json
{
    "simulation": {
        "number_of_boards": 1,
        "board": {
            "row": 4,
            "column": 5
        },
        "colonies": [
            {
                "name":"The Seventh Company",
                "anthill":[2, 2],
                "initial_ants": 10
            }
        ]
    },
  
    "rendering": [
        {
            "fps": 30,
            "frames_per_step": 15,
            "quality": "medium",
            "output_directory": "./render_save"
        }
    ]
}
```

</details>

<details>
  <summary>Advanced configuration</summary>

```json
{
  "simulation": {
    "number_of_boards": 3,
    "board": {
      "row": 5,
      "column": 5
    },
    "colonies": [
      {
        "name":"The Seventh Company",
        "anthill":[2, 2],
        "initial_ants": 20
      },
      {
        "name":"The Fellowship of the Ring",
        "anthill":[0, 4],
        "initial_ants": 15
      }
    ]
  },

  "rendering": [
    {
      "fps": 30,
      "frames_per_step": 15,
      "quality": "medium",
      "output_directory": "./render_save"
    },
    {
      "fps": 15,
      "frames_per_step": 15,
      "quality": "low",
      "output_directory": "./render_save"
    }
  ]
}
```

</details>

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
Titourterelle - [GitHub](https://github.com/Titourterelle) - titourterelle@gmail.com