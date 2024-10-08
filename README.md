# Sleep Paradox

Sleep Paradox is an entry into GBA Jam 2024 by staticlinkage, Urigamiart, Nikku4211 and Locusbelmont.

## Credits

- Programming: staticlinkage
- Art: Urigamiart
- Music: Nikku4211

Locusbelmont also assisted with some sprite work.

Fonts used are the work of Sparklin Labs / Pixel-boy under Creative Commons

## Playing

The game can be downloaded from [its project page on itch.io](https://staticlinkage.itch.io/sleep-paradox).

As an honest-to-goodness GBA game, Sleep Paradox can be played in a GBA emulator such as mGBA, or on original hardware via a flash cart.

Controls:
- Arrows: movement
- A: interact
- B: attack
- L: change camera angle
- R: dash/dodge

## Compiling

Building Sleep Paradox has a couple prerequisites:

- A modified version of Butano that disables Butano's sound systems (Sleep Paradox uses a custom sound engine by Nikku4211). A Butano fork containing the required modifications can be found [here](https://github.com/chrislewisdev/butano).
- An installation of `slpx-map-tool` which produces all the map data sourced from `.tmx` files - available [here](https://github.com/chrislewisdev/slpx-map-tool)

With those prerequisites met, you should be able to build the game from scratch by running `make LIBBUTANO=<butano-installation-directory>` where the Butano installation directory points to your modified Butano version.

## Licensing

The code in this repo is released under the MIT license while the art assets are released under Creative Commons (see the licenses folder for further detail).
