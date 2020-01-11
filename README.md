# ConvNeuralNet
Graphical Visualization of a Convolutional Neural Network in C++

![](images/ConvNeuralNet.gif)

Terminal simulation of a Convolutional Neural Network in C++

![](images/terminal.png)

# **About**
	This project is split up into two forms: Graphical (using openFrameworks) and Terminal (shell)
# **Requires (Graphical)** 
  	-OpenFrameworks v0.10.1+ <b>openframeworks.cc/download/</b> (Or look into <b>OF_install.sh</b> thats provided)
	-Unzip and place in your home directory ~/ with name OF/ or edit the <b>OF_ROOT</b> in the Makefile
	-Run the internal script inside **OF/scripts/linux** or similarly for the windows/MacOS installation
# **Requires (Terminal)** 
  	g++ with a bash terminal
# **INSTALL: (Graphical)**
  	-FIRST, you will need openframeworks and there is an automated script (<b>OF_install.sh</b>)
	  that will download everything and setup the OF directory as required by the program.
	-The script was written on a Ubuntu derivative, however to run on Arch/fedora/Debian there
	  are similar install_dependencies scripts in the OF directory (refer to the OF_install.sh script). 
	-run <b>./graphical.sh</b> in the project directory, then enter bin/ to run <b>/graphical</b>
# **INSTALL: (terminal)**
	run <b>./terminal.sh</b> in the project directory, then enter bin/ to run <b>/terminal</b>

# **HOW TO USE:**
  	To use custom datasets simply modify/replace the <b>data.txt</b> file in data/.
**REQUIREMENTS:**
	-The format of the dataset should be "x1 x2 ... x**n** ; y1 y2 ... y**m** " on every line\
	  (**m** dosent have to equal **n**)
	-Where spaces are used to divide the individual data entries and the semicolon (;) divides\
	  inputs against outputs.
	-Make sure to use the same number of inputs for all data entries (as would a normal function mapping). 

# **Controls: (Graphical)**
**PRESS (H) (h) (?) to see this from the terminal**
**SPACE:**\
	Iterate through dataset and run into model.\
**BACKSPACE:**\
	Compute total average cost, where cost function is the difference in squares\
**RT_SHIFT:**\
	Begin training on dataset\
**ENTER:**\
	Randomize weights on entire Neural Net\
**ESC:**\
	Exit application
# **Controls: (Terminal)**
  	All the information for input commands should be presented upon program launch
	Or simply type 'help', 'H', or '?'