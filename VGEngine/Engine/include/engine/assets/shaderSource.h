
#pragma once

#include "engine\assets\asset.h"

/// @todo Fix comments in this file

namespace vg
{
	/**
		<description>
	*/
    class ShaderSource : public Asset
    {
    public:
		/**
			<description>
		*/
        ShaderSource();

        ~ShaderSource();

		/**
			<description>
            @todo get FileManger instance
			@return <description>
		*/
        bool load();

		/**
			<description>
            @todo get AssetManager instance
			@return <description>
		*/
        bool unLoad();
    private:
    };
}