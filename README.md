# G-Code Generator
## Overview
This is a G-Code generation progra, created during my summer internship with SE3D. It receives user input and interpolates the data into G-Code compatible with SE3D's r3bEL X and r3bEL mini bioprinters. Use with other bioprinters is possible, but extrusion should only take place on appropriately sized petri dishes (at least 100mm), or the [Greiner 650161 96-Well Microplate](https://shop.gbo.com/en/row/products/bioscience/microplates/96-well-microplates/96-well-microplates-clear/650161.html).

### Supported Materials
* Calcium Chloride Solution
* Biomolecule in a 1% Alginate Solution
* Substrate Solutions

The GUI is built with Qt Creator and written entirely in C++. Example screenshots:


Template Selection:
![Screenshot of template selection](/screenshots/template-selection-v1.1.0.png)


Custom Print:
![Screenshot of custom print](/screenshots/custom-print-v1.1.0.png)


Selectable text with .gcode file output
![Screenshot of output page](/screenshots/output-v1.1.0.png)

## Dependencies
* Compiled program
	* The compiled program should contain all necessary frameworks
* Source code
	* Xcode
	* At least Qt 5.9.1
  
## How to run from the compiled program
1. Download the [latest release](https://github.com/brendanwong/gcg-gui/releases).
2. Extract the compressed file.
3. Double click the downloaded .exe or .app file. If this results in an error, run as administrator or open the application via Security & Privacy within System Preferences.
4. If issues persist, create an [issue](https://github.com/brendanwong/gcg-gui/issues).

## How to run from the source code
1. Make sure all required dependencies are installed
2. Clone the repository using https://github.com/brendanwong/gcg-gui.git
3. Use Qt Creator to open [gcg-gui.pro](gcg-gui.pro)
4. Run the program using Qt
