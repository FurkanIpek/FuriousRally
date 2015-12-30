#pragma once

#include <string>

typedef enum {YELLOW, RED, GRAY, WHITE, BLACK, PURPLE, BLUE, GREEN, BROWN} COLORS;

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

	void operator = (Color& rhs)
	{
		red = rhs.getRed();
		green = rhs.getGreen();
		blue = rhs.getBlue();
		alpha = rhs.getAlpha();
	}

	static Color getColor(COLORS color_code, GLfloat alpha = 1.0f)
	{
		Color color;

		switch (color_code)
		{
		case YELLOW: color = Color(0.98f, 0.98f, 0.0f, alpha);
			break;

		case RED: color = Color(0.70f, 0.10f, 0.10f, alpha);
			break;

		case GRAY: color = Color(0.62f, 0.62f, 0.62f, alpha);
			break;

		case WHITE: color = Color(0.98f, 0.98f, 0.98f, alpha);
			break;

		case BLACK: color = Color(0.0f, 0.0f, 0.0f, alpha);
			break;

		case PURPLE: color = Color(0.39f, 0.0f, 0.78f, alpha);
			break;

		case BLUE: color = Color(0.0f, 0.01f, 0.2f, alpha);
			break;

		case GREEN: color = Color(0.49f, 0.98f, 0.0f, alpha);
			break;

		case BROWN: color = Color(0.40f, 0.20f, 0.0f, alpha);
			break;

		default: color = Color(0.70f, 0.65f, 0.0f, alpha);
		}

		return color;
	}
};