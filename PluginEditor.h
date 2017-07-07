/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "customLookAndFeel.h"


//==============================================================================
/**
*/
class FirstPluginAudioProcessorEditor : public AudioProcessorEditor, 
										public Slider::Listener, 
										private Timer
{
public:
    FirstPluginAudioProcessorEditor (FirstPluginAudioProcessor&);
    ~FirstPluginAudioProcessorEditor();

	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;
private:	
	
	void sliderValueChanged(Slider* slider) override;
	void updateGUI();

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstPluginAudioProcessor& processor;

	Slider osc1Amp;
	Slider osc1Octave;
	Slider osc1Wave;
	Slider osc1Semi;
	Slider osc1Fine;

	customLookAndFeel customLookAndFeel;
	Image logo;
	Label debug;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstPluginAudioProcessorEditor)
};
