# Ukázka použití nástroje CMake

Konfigurační soubor nástroje [CMake](https://cmake.org/) může vypadat například
[takto](https://github.com/opencv/opencv/blob/master/CMakeLists.txt).

CMake umožňuje sestavení konfigurovat, tj. můžete si zvolit například:
 - jaké moduly knihovny chcete přeložit,
 - pro jakou platformu,
 - jakým překladačem,
 - statickou nebo dynamickou knihovnu,
 - knihovna pro každý modul nebo jeden velký soubor,
 - apod.

Možností jsou tisíce! Pro každý z nich je třeba vytvořit Makefile, podle kterého může
být sestavení uskutečněno.

## Postup překladu:
```bash
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=******* ..
make -j8
cmake -S ../src
```
