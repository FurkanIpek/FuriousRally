#pragma once

#include <string>

class Color {
private:
	double red, green, blue;
	double alpha;

public:
	Color() : red(0.5), green(0.5), blue(0.5), alpha(0.5) {}
	Color (double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {}
	double getRed() { return red; }
	double getGreen() { return green; }
	double getBlue() { return blue; }
	double getAlpha() { return alpha; }
	
	void setRed(int redValue) { red = redValue; }
	void setGreen(int greenValue) { green = greenValue; }
	void setBlue(int blueValue) { blue = blueValue; }
	void setAlpha(double alphaValue) { alpha = alphaValue; }
};