#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class ParameterSlider : public Slider,
	private Timer
{
public:
	ParameterSlider(AudioProcessorParameter& p) : Slider(p.getName(256)), param(p) {

	}

	void valueChanged();

	void timerCallback() override { updateSliderPos(); }

	void startedDragging();
	void stoppedDragging();

	double getValueFromText(const String& text);
	String getTextFromValue(double value);

	void updateSliderPos();

	AudioProcessorParameter& param;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
};