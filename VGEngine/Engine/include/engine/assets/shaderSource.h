
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
			@return <description>
		*/
        bool load();

		/**
			<description>
			@return <description>
		*/
        bool unLoad();
    private:
    };
}