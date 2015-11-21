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

	static Color getColor(std::string color, GLfloat alpha = 0.5f)
	{
		if (color == "god")
			return Color(1, 1, 1, alpha);

		if (color == "damn")
			return Color(0.56f, 0.25f, 0.80f, alpha);

		if (color == "wtf")
			return Color(0.70f, 0.90f, 0.20f, alpha);

		if (color == "hey")
			return Color(0.20f, 0.30f, 0.50f, alpha);

		return Color(0, 0, 0, alpha);
	}
};