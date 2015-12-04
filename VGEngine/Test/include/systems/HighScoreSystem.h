#pragma once
#include <engine/game/system.h>
#include <engine/utility/vec2f.h>
#define filePath "Doge.txt"
#define MAX_SCORE 10
class HighScoreSystem : public vg::System
{
	struct Score
	{
		std::string name;
		int score;
	};
public:
	HighScoreSystem();
	~HighScoreSystem();
	void update(std::vector<vg::GameObject*> *gameObjects, float deltaTime);

private:
	void saveData();
	void loadData();
	std::vector<Score> scores;
	void addScore(std::string name, int score);
	bool isInputDown();
	vg::Vec2f getInputPos();
	std::string actionText;
};

