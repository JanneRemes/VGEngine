
#pragma once

namespace vg
{
	/**
	Contains red, green, blue and alpha values in a range of 0-255.
	*/
	class Color
	{
	public:
		/**
		Initializes with default value, opaque black
		*/
		Color();

		Color(const Color& other);

		/**
		0 for all color values result black. 255 for all color values results white.
		@param _alpha 0 is fully transparent, 255 is opaque
		*/
		Color(unsigned char _red, unsigned char _green, unsigned char _blue, unsigned char _alpha = 255);

		~Color() = default;

		/**
		@return random opaque color
		*/
		static vg::Color random();

		unsigned char red;		///< red value 
		unsigned char green;	///< green value
		unsigned char blue;		///< blue value
		unsigned char alpha;	///< alpha value
	private:

	};
}