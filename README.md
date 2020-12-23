# ConvNeuralNet
Graphical Visualization of a Convolutional Neural Network in C++

![](images/ConvNeuralNet.gif)

Terminal simulation of a Convolutional Neural Network in C++

```sh
Current working dir: ./bin
  Reading from "./bin/../data/data.txt
There are 3 inputs
There are 3 outputs

Building Convolutional Neural Net with 3 networks
Starting setup...Current working dir: ./bin
  Reading from "./bin/../data/data.txt

 Read file successfully
  ..Initializing network: 0... SUCCESS!
  ..Initializing network: 1... SUCCESS!
  ..Initializing network: 2... SUCCESS!
 Network: 0 is built with: 
  -- 3 -- 3 -- 4 -- 1 neurons 
 Network: 1 is built with: 
  -- 3 -- 2 -- 2 -- 2 -- 1 neurons 
 Network: 2 is built with: 
  -- 3 -- 2 -- 2 -- 1 neurons 
setup complete.
Welcome to Convolutional Neural Net v1.0.0
Type (Help) or (H) or (?) to see all options and input commands (Ignore parens)
Inputs:
  (test)   ===> input new data and compare
  (save)   ===> save current network data to output.txt
  (cost)   ===> print average network cost
  (train)  ===> begin training of neural net
  (multi)  ===> use multithreading computation
  (single) ===> use single-core computation
  (reset)  ===> reset network and randomize all weights
  (exit)   ===> exit from program(1)Next Command:
>>
```

### Prerequisites (graphical)
- OpenFrameworks v0.10.1+ openframeworks.cc/download/ (Or look into OF_install.sh thats provided)
- Unzip and place in your home directory ~/ with name OF/ or edit the OF_ROOT in the Makefile
- Run the internal script inside OF/scripts/linux or similarly for the windows/MacOS installation
### Prerequisites (tty)
- g++ with a bash terminal
## Installation: (graphical)
For the graphical interface you will need OpenFrameworks and there is an automated script (OF_install.sh) that will download everything and setup the OF directory as required by the program. The script was written on a Ubuntu derivative, however to run on Arch/fedora/Debian there are similar install_dependencies scripts in the OF directory (refer to the OF_install.sh script). Then run `graphical.sh` in the project directory, then enter `bin` to run the `graphical` executable.
## Installation (tty)
Execute `terminal.sh` in the project directory to create the binary and enter `bin` to run `terminal`

## Usage
To use custom datasets simply modify/replace the data.txt file in `data/`.

**Things to note:**
- The format of the dataset should be "x1 x2 ... x**n** ; y1 y2 ... y**m** " on every line (**m** dosent have to equal **n**)\
- Spaces are used to divide the individual data entries and the semicolon (;) separates the inputs against outputs.
- Make sure to use the same number of inputs for all data entries (as would a normal function mapping). 

## **Controls: (Graphical)**
PRESS (H) (h) or (?) to see this from the terminal
- **SPACE:** Iterate through dataset and run into model.
- **BACKSPACE:** Compute total average cost, where cost function is the difference in squares
- **RT_SHIFT:**	Begin training on dataset
- **ENTER:** Randomize weights on entire Neural Net\
- **ESC:** Exit application
## **Controls: (Terminal)**
- All the information for input commands should be presented upon program launch. Or simply type 'help', 'H', or '?'
