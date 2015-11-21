#pragma once

class KeyHandler {

private:
	char keys[256];

	KeyHandler() {}

	KeyHandler(const KeyHandler&);
	void operator=(const KeyHandler&);

public:
	static KeyHandler& getInstance()
	{
		static KeyHandler keyHandler;

		return keyHandler;
	}

	void keyPressed(unsigned char key);
};
