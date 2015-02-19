
#include "engine\assets\asset.h"

using namespace vg;

Asset::Asset(const std::string& path)
	: mPath(path)
{
}

bool Asset::isLoaded() const
{
	return mIsLoaded;
}
