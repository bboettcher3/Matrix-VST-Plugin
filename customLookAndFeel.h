#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class customLookAndFeel : public LookAndFeel_V4
{
public:
	customLookAndFeel();
	~customLookAndFeel();
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
};

