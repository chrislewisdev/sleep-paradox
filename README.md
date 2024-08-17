# Sleep Paradox

Sleep Paradox is an entry into GBA Jam 2024 by staticlinkage, Urigamiart, Nikku4211 and Locusbelmont.

## Compiling

Building Sleep Paradox has a couple prerequisites:

- A modified version of Butano that disables Butano's sound systems (Sleep Paradox uses a custom sound engine by Nikku4211). A Butano fork containing the required modifications can be found here.
- An installation of `slpx-map-tool` which produces all the map data sourced from `.tmx` files - available here

With those prerequisites met, you should be able to build the game from scratch by running `make LIBBUTANO=<butano-installation-directory>` where the Butano installation directory points to your modified Butano version.
