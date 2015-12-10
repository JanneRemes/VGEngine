#include "systems/HighScoreSystem.h"
#include <engine/game/gameObject.h>
#include <engine/utility/string.h>
#include <engine/game/game.h>
#include <engine/assets/fileManager.h>
#include <engine/utility/logger.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <engine/game/textComponent.h>
#ifdef OS_WINDOWS
#include <engine/input/mouse.h>
#else
#include <engine/input/touch.h>
#endif
#include <algorithm>
using namespace vg;
using namespace vg::input;
HighScoreSystem::HighScoreSystem()
{
	srand(time(NULL));
	for (int i = 0; i < MAX_SCORE; i++)
	{
		Score doge;
		doge.name = "exampleData";
		doge.score = rand() % 1000;
		scores.push_back(doge);
	}
	

	loadData();
	saveData();
	actionText = "";
}


HighScoreSystem::~HighScoreSystem()
{
}
void HighScoreSystem::update(std::vector<vg::GameObject*> *gameObjects, float deltaTime)
{

	std::string objectName = "";
	for (auto it = gameObjects->begin(); it < gameObjects->end(); it++)
	{
		objectName = (*it)->getName();
		for (int i = 0; i < 10; i++)
		{
			if (objectName == "score" + toStringi(i))
			{
				TextComponent *comp = (*it)->getComponent<TextComponent>();
				if (scores.size() - 1 < i || scores.size() == 0)
				{
					comp->setText("");
					continue;
				}
				comp->setText(scores[i].name + ":" + toStringi(scores[i].score));
			}
		}
		if (objectName == "nappi")
		{
			TransformComponent * comp = (*it)->getComponent<TransformComponent>();
			if (isInputDown())
			{
				vg::Vec2f pos = getInputPos();
				std::string abc = "qwertyuiopasdfghjklzxcvbnm";
				if (comp->contains(pos))
				{
					std::string name;
					int max =  4+ rand() % 4;
					for (int i = 0; i < max; i++)
					{
						name = name + abc.at(rand() % (abc.size() -1));
					}
					int score = rand() % 1000;
					addScore(name.c_str(),score);
					actionText = std::string("Added: " +name + " " + toStringi(score));
				}
			}
		}
		if (objectName == "action")
		{
			TextComponent *comp = (*it)->getComponent<TextComponent>();
			comp->setText(actionText);
		}
	}
}
void HighScoreSystem::loadData()
{

	std::string fileContents; 

	Game::getInstance()->getFileManager()->readFile(
#ifdef OS_WINDOWS
		vg::core::FileManager::DataPath::File
#else
		vg::core::FileManager::DataPath::Internal
#endif
		
		, filePath, fileContents);
	string buf; // Have a buffer string
	stringstream ss(fileContents); // Insert the string into a stream

	vector<string> tokens; // Create vector to hold our words

	while (ss >> buf)
		tokens.push_back(buf);
	scores.clear();
	for (int i = 0; i < tokens.size(); i += 2)
	{
		addScore(tokens[i], toInt(tokens[i + 1]));
	}
	Log("vgengine", "File read");

}

void HighScoreSystem::saveData()
{

	std::string fileContents;
	for (int i = 0; i < scores.size(); i++)
	{
		fileContents = fileContents + scores[i].name + " " + toStringi(scores[i].score) + "\n";
	}
	Game::getInstance()->getFileManager()->writeFile(
#ifdef OS_WINDOWS
		vg::core::FileManager::DataPath::File
#else
		vg::core::FileManager::DataPath::Internal
#endif
		, filePath, fileContents);

}

void HighScoreSystem::addScore(std::string name, int score)
{
	Score doge;
	doge.name = name;
	doge.score = score;
	scores.push_back(doge);
	sort(scores.begin(), scores.end(),
		[](const Score & a, const Score & b) -> bool
	{
		return a.score > b.score;
	});
	if (scores.size() > MAX_SCORE)
	scores.erase(scores.end() - 1);
	saveData();
}

bool HighScoreSystem::isInputDown()
{
#ifdef OS_WINDOWS
	return Mouse::isKeyPressed(MOUSE_KEY::LEFT);
#else
	return Touch::getIsReleased();
#endif
}
vg::Vec2f HighScoreSystem::getInputPos()
{
#ifdef OS_WINDOWS
	return Mouse::getPos(false);
#else
	return Touch::getPos(false);
#endif
}