myDraw
======

Simple drawing tool using OpenGL and GLUT. Made by [Anirudh Vemula](vvanirudh@gmail.com) and [Rohan Prinja](rohan.prinja@gmail.com) for the first assignment of our [Computer Graphics](http://www.cse.iitb.ac.in/~paragc/teaching/2013/cs475) course. The exact problem statement can be found in the `problem-statement.pdf` file in the root directory of this repo.

Hostel Room Drawing
-------------------

The hostel room drawing is in "drw/hostel-room".

Installation
------------

1 Download this repo
2 Unzip
3 `cd myDraw`

Running
-------

1 `make`
2 `./bin/myDraw`

Cleaning Up
-----------

1 `make clean`

Quick Walkthrough
-----------------

Once you've installed and run the program, press `n` to make a new canvas. Then initialize a new drawing with `d`. Note that all these keys must be pressed while the focus is on the window that opens when you run the executable. Read the `problem-statement.pdf` file for a detailed overview of the commands our program supports. Whenever you enter a command that requires some setting of parameters (e.g. `c`) the input is to be given on the terminal.

**Note** As of now, error handling is minimal to nonexistent. So, for example, the fill color expects RGB values between `0` and `255`. Entering values outside this range might cause the program to crash in entertaining ways.

Saving and Loading
------------------

If you want to save the current drawing, press `s` and the drawing will be saved to a file. If you try to load a drawing by pressing `l` the current drawing will be discarded and your unsaved work will be lost. Each time you save you will be asked to specify the file you want to save to. If the file already exists, it will be overwritten. If it doesn't, it will be created and stored in the `drw` folder.

Whenever you type in a file to load, the path is relative to `drw`. For example, typing `my-drawing` searches for a file in `drw/my-drawing`.

Configuration
-------------

To change the size of the drawing window:

1 Open `main.cpp` in any text editor
2 Change the lines

    int win_width = 1024;
    int win_height = 768;

to whatever values you want.
3 Re-compile with `make`

To change the default background color:

1 Open `cfg/canvas.cfg` in any text editor
2 Change the RGB values to whatever you want

License
-------

[WTFPL](http://www.wtfpl.net/about/)