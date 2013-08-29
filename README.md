myDraw
======

Simple drawing tool using OpenGL and GLUT. Made by Anirudh Vemula and me for the first assignment of our Computer Graphics course. The exact problem statement can be found in the A1.pdf file.

Hostel Room Drawing
-------------------

The hostel room drawing is in "drw/hostelroom".


Saving and Loading
------------------

If you want to save the current drawing, press 's' and the drawing will be saved to a file. If you try to load a drawing by pressing 'l' the current drawing will be discarded and your unsaved work will be lost. Each time you save you will be asked to specify the file you want to save to. If the file already exists, it will be overwritten. If it doesn't, it will be created and stored in the 'drawings' folder. Whenever you type in a file to load, the path is relative to $(myDraw_directory)/drawings. For example, if you press 'l' and enter 'drawing1' myDraw searches for the file "$(myDraw_directory)/drawings/drawing1".

File Format
-----------

Given below is an example of a saved drawing