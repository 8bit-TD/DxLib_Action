#pragma once

class System {
	
public:
	std::string cursor;
	int gh;
	int mx, my;
	System();
	~System();
	void Update();
	void Draw();
};
