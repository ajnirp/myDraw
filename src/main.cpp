#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <GL/glut.h>

#include "required.hpp"

using namespace std;

/* Global vars */

// Window Parameters
int win_width = 800;
int win_height = 640;
int window_id;

// Drawing modes
bool line_drawing_mode = true;
bool fill_mode = false;
bool polygon_drawing_mode = false;

int num_points = 0;
point_t first_point;
list<point_t> polygon_points;
list<fragment_t> fill_points;

color_t black(0, 0, 0);
pen_t pen(black, 3, false);
fill_t fill_object(black, black, false);

canvas_t* canvas = NULL;

/* Function declarations */
void make_new_canvas();
void save_drawing();
void load_drawing();
color_t read_rgb();

/* Callbacks */
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);

/* Functions */
void make_new_canvas() {
	if (!canvas) {
		color_t bg_c = read_rgb();

		canvas = new canvas_t(win_width, win_height, bg_c, NULL);

		int r = bg_c.red;
		int g = bg_c.green;
		int b = bg_c.blue;

		glClearColor(r/255.0, g/255.0, b/255.0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glutPostRedisplay();
		cout << "Initialized new canvas\n";
	}
	else {
		cerr << "A canvas already exists\n";
	}
}

// Save the drawing object pointed to by d
// Assumes that d is a valid drawing, so it
// does not error handle for the case when d
// is NULL
void save_drawing(drawing_t* d) {
	cout << "Enter filename to save to (no spaces): ";
	string filename; cin >> filename;
	// add code to check for invalid filename characters like '/'
	filename = "drw/" + filename;
	ofstream save_file;
	save_file.open(filename.c_str());

	// Save the lines
	list<line_t>::iterator l_itr;
	for (l_itr = d->lines.begin(); l_itr != d->lines.end(); l_itr++) {
		save_file << "L "
		          << (int)l_itr->pen.color.red << " "
		          << (int)l_itr->pen.color.green << " "
		          << (int)l_itr->pen.color.blue << " "
		          << l_itr->pen.size << " "
		          << l_itr->v0.x << " "
		          << l_itr->v0.y << " "
		          << l_itr->v1.x << " "
		          << l_itr->v1.y << "\n";
	}

	// Save the polygons
	list<polygon_t>::iterator pgn_itr;
	for (pgn_itr = d->polygons.begin() ; pgn_itr != d->polygons.end() ; pgn_itr++) {
		save_file << "P ";
		save_file << (int)pgn_itr->border.color.red << " "
		          << (int)pgn_itr->border.color.green << " "
		          << (int)pgn_itr->border.color.blue << " "
				  << pgn_itr->border.size << " ";
		// Print each point to the file
		list<point_t>::iterator itr;
		list<point_t>::iterator itr_next = pgn_itr->vertices.begin();
		for (itr = pgn_itr->vertices.begin() ; itr != pgn_itr->vertices.end() ; itr++) {
			itr_next++;
			save_file << itr->x << " "
			          << itr->y << (itr_next == pgn_itr->vertices.end() ? "\n" : " ");
		}
	}

	// Save the fill fragments
	list<fragment_t>::iterator f_itr;
	for (f_itr = fill_points.begin() ; f_itr != fill_points.end() ; f_itr++) {
		save_file << "F "
		          << (f_itr->fill.checker_mode ? "C " : "N ") // C = checkermode, N = normal
		          << f_itr->point.x << " " << f_itr->point.y << " "
		          << (int)f_itr->fill.color_1.red << " "
		          << (int)f_itr->fill.color_1.green << " "
		          << (int)f_itr->fill.color_1.blue;
		if (f_itr->fill.checker_mode) {
			save_file << " "
			          << (int)f_itr->fill.color_2.red << " "
			          << (int)f_itr->fill.color_2.green << " "
			          << (int)f_itr->fill.color_2.blue;
		}
		save_file << "\n";
	}

	save_file.close();

	cout << "Saved to file '" << filename << "'\n";
}

// Load a drawing object into d
// When passed to the function, d is NULL
void load_drawing(canvas_t* canvas) {
	cout << "Enter drawing file to load: ./drw/";
	string filename; cin >> filename;
	filename = "drw/" + filename;

	canvas->drawing = new drawing_t(canvas);

	string line;
	ifstream load_file;
	try {
		load_file.open(filename.c_str());
		if (load_file.is_open()) {
			// list<fragment_t> fill_pts;
			fill_points.clear();
			while (load_file.good()) {
				getline(load_file, line); // read a line
				vector<string> tokens;    // vector to store the space-split tokens
				string buffer;
				stringstream ss(line);
				if (line[0] == 'L' or line[0] == 'P' or line[0] == 'F') {
					while (ss >> buffer) tokens.push_back(buffer);
					// read the pen color and size
					color_t c(atoi(tokens[1].c_str()),
						      atoi(tokens[2].c_str()),
						      atoi(tokens[3].c_str()));
					float s = atoi(tokens[4].c_str());
					pen_t p(c, s, false);

					// Load the lines
					if (line[0] == 'L') {
						line_t l(atoi(tokens[5].c_str()),
							     atoi(tokens[6].c_str()),
							     atoi(tokens[7].c_str()),
							     atoi(tokens[8].c_str()),
							     p);
						canvas->drawing->lines.push_back(l);
					}

					// Load polygons
					else if (line[0] == 'P') {
						list<point_t> verts;
						for (unsigned int i = 5 ; i+1 < tokens.size() ; i += 2) {
							point_t pt(atoi(tokens[i].c_str()),
							          atoi(tokens[i+1].c_str()));
							verts.push_back(pt);
						}
						polygon_t poly(verts, p);
						canvas->drawing->polygons.push_back(poly);
					}

					// Load fill fragments
					else if (line[0] == 'F') {
						
						point_t pt(atoi(tokens[2].c_str()),
							       atoi(tokens[3].c_str()));

						color_t c1(atoi(tokens[4].c_str()),
							      atoi(tokens[5].c_str()),
							      atoi(tokens[6].c_str()));

						string fill_type = tokens[1];
						fragment_t frag;
						if (fill_type == "C") {
							color_t c2(atoi(tokens[7].c_str()),
									   atoi(tokens[8].c_str()),
									   atoi(tokens[9].c_str()));
							fill_t checker_fill(c1, c2, true);
							frag.fill = checker_fill;
						}
						else {
							color_t black(0, 0, 0);
							fill_t normal_fill(c1, black, false);
							frag.fill = normal_fill;
						}
						frag.point = pt;
						fill_points.push_back(frag);
					}
				}
			}
			glClear(GL_COLOR_BUFFER_BIT);
			canvas->drawing->draw();
			list<fragment_t>::iterator fr_itr;
			for (fr_itr = fill_points.begin() ; fr_itr != fill_points.end() ; fr_itr++) {
				fill_object = fr_itr->fill;
				fill_object.draw(fr_itr->point, canvas->array, canvas->width, canvas->height, canvas->bg_color);
			}
		}

		// if the file does not exist, throw an error
		else {
			throw "File not found";
		}
		cout << "Loaded drawing from file '" << filename << "'\n";
		load_file.close();

		if (fill_mode) canvas->drawing->draw_array();
	}
	catch (const char* err) {
		cerr << "ERROR: " << err << "\n";
	}
	glFlush();
}

color_t read_rgb() {
	ifstream canvas_file("cfg/canvas.cfg");
	string line;
	int r, g, b;
	if (canvas_file.is_open()) {
		while (canvas_file.good()) {
			getline(canvas_file, line);
			if (line[0] == 'R') r = atoi(line.substr(2).c_str());
			else if (line[0] == 'G') g = atoi(line.substr(2).c_str());
			else if (line[0] == 'B') b = atoi(line.substr(2).c_str());
		}
	}
	color_t bg_c(r, g, b);
	return bg_c;
}

/* Callbacks */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	/* Test code here */
	glFlush();
}

void reshape(int w, int h) {
	if (h == 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1., 1.);
	glViewport(0, 0, w, h);

	win_width = w;
	win_height = h;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		// Create new canvas
		case 'n': { make_new_canvas(); }
		break;

		// Initialize new drawing
		case 'd': {
			if (!canvas) {
				cerr << "ERROR: No canvas to draw on. Make a new canvas by pressing 'n'\n";
			}
			else {
				if (canvas->drawing) {
					canvas->drawing = NULL;
				}
				canvas->drawing = new drawing_t(canvas);
				cout << "Initialized new drawing\n";
			}
		}
		break;

		// Save drawing
		case 's': {
			if (canvas and canvas->drawing) {
				save_drawing(canvas->drawing);
			}
			else {
				cerr << "ERROR: No canvas exists or no drawing has been initialized\n";
			}
		}
		break;

		// Load drawing
		case 'l': {
			if (canvas) {
				if (canvas->drawing) canvas->drawing = NULL;
				load_drawing(canvas);
			}
			else {
				cerr << "ERROR: No canvas to load to. Make a new canvas by pressing 'n'\n";
			}
		}
		break;

		//Toggle fill mode
		case 'f': {
			cout << "Fill mode is now " << (fill_mode ? "off" : "on") << "\n";
			fill_mode = not fill_mode;

			if(fill_mode) {
				polygon_drawing_mode = false;
				line_drawing_mode = false;
			}
			else {
				line_drawing_mode = true;
				polygon_drawing_mode = false;
			}

			glClear(GL_COLOR_BUFFER_BIT);
			if (fill_mode) canvas->drawing->draw_array();
			else canvas->drawing->draw();
			glFlush();
		}
		break;

		// Toggle line drawing mode
		case '1': {
			if (canvas) {
				if (canvas->drawing) {
					line_drawing_mode = true;
					polygon_drawing_mode = false;
					fill_mode = false;

					// Draw the polygon, then clear polygon_points
					if (polygon_points.size() > 2) {
						polygon_t poly(polygon_points, pen);
						canvas->drawing->polygons.push_back(poly);
						poly.draw(canvas->array, canvas->width, canvas->height);
						polygon_points.clear();
						glFlush();
					}
				}
				
				line_drawing_mode = true;
				cout << "Line drawing mode on\n";
			}
		}
		break;

		// Toggle polygon drawing mode
		case '2': {
			if (canvas) {
				line_drawing_mode = false;
				polygon_drawing_mode = true;
				fill_mode = false;
				cout << "Polygon drawing mode on\n";	
			}
		}
		break;

		// Exit the program using Esc
		case 27: {
			cout << "Exiting myDraw...\n";
			glutDestroyWindow(window_id);
			exit(0);
		}
		break;

		// Toggle fill mode or pen attributes
		// depending on whether fill mode is
		// active or not
		case 'c': {
			if (fill_mode) {
				cout << "Enter new fill attributes\n";
				cout<<"Mode (Checker = 0 or normal = 1): ";
				int mode; cin >> mode;
				if (mode == 1) {
					int r; cout << "R: "; cin >> r;
					int g; cout << "G: "; cin >> g;
					int b; cout << "B: "; cin >> b;
					color_t fill_c(r, g, b);
					fill_object.color_1 = fill_c;
					fill_object.checker_mode = false;
					cout << "Fill attributes modified\n";
				}
				else if (mode == 0) {
					cout<<"First color"<<endl;
					int r; cout << "R: "; cin >> r;
					int g; cout << "G: "; cin >> g;
					int b; cout << "B: "; cin >> b;
					color_t fill_c(r, g, b);
					fill_object.color_1 = fill_c;
					cout<<"Second color"<<endl;
					cout << "R: "; cin >> r;
					cout << "G: "; cin >> g;
					cout << "B: "; cin >> b;
					color_t fill_b(r,g,b);
					fill_object.color_2 = fill_b;
					fill_object.checker_mode = true;
					cout << "Fill attributes modified\n";
				}
			}
			else {
				cout << "Mode (Eraser = 0 or normal = 1): ";
				int pen_mode; cin >> pen_mode;

				if (pen_mode == 1) {
					cout << "Enter new pen attributes\n";
					int r; cout << "R: "; cin >> r;
					int g; cout << "G: "; cin >> g;
					int b; cout << "B: "; cin >> b;
					color_t pen_c(r, g, b);
					float s; cout << "Size: "; cin >> s;
					pen_t new_pen(pen_c, s, false);
					pen = new_pen;
					cout << "Pen attributes modified\n";
				}
				else {
					int er_size; cout << "Enter eraser size: "; cin >> er_size;
					pen_t new_pen(canvas->bg_color, er_size, true);
					pen = new_pen;
					cout << "Pen attributes modified\n";
				}
			}
		}
		break;

		// Clear the canvas
		case 'r': {
			if (canvas) {
				canvas->drawing = NULL;
				canvas->clear();
				fill_points.clear();
				polygon_points.clear();
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				cout << "Cleared the canvas\n";
			}
		}
	}
}

void mouse(int button, int state, int x, int y) {
	if (canvas and canvas->drawing) {
		if (state == GLUT_DOWN) {
			if (button == GLUT_DOWN) { // Line drawing mode active
				if (line_drawing_mode) {
					if (num_points == 0) {
						first_point.set(x, win_height-y);
					}
					else if (num_points == 1) {
						line_t curr_line(first_point.x, first_point.y, x, win_height-y, pen);
						canvas->drawing->lines.push_back(curr_line);
						curr_line.draw(canvas->array, canvas->width, canvas->height);
					}
					num_points = 1 - num_points;				
				}
				else if (polygon_drawing_mode) { // Polygon drawing mode active
					point_t clicked(x, win_height-y);
					polygon_points.push_back(clicked);
				}
				else {
					point_t clicked(x, win_height-y);
					fragment_t frag; frag.point = clicked; frag.fill = fill_object;
					fill_points.push_back(frag);
					fill_object.draw(clicked, canvas->array, canvas->width, canvas->height, canvas->bg_color);
					canvas->drawing->draw_array();
				}
			}
		}
	}
	glFlush();
}

int main(int argc, char* argv[]) {
	cout << "Welcome to myDraw!\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-win_width)/2, (glutGet(GLUT_SCREEN_HEIGHT)-win_height)/2);

	window_id = glutCreateWindow("myDraw");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}