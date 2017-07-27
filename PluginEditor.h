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
										public ComboBox::Listener,
										public Button::Listener,
										private Timer
{
public:
    FirstPluginAudioProcessorEditor (FirstPluginAudioProcessor&);
    ~FirstPluginAudioProcessorEditor();

	class ParameterSlider;

	void initOscillators();
	void initLFO();
	void initEnvelopes();
	void initVolume();
	void initFilters();
	void initBounds();

	typedef struct _oscSlider {
		ScopedPointer<ParameterSlider> amplitude;
		ScopedPointer<ParameterSlider> octave;
		ComboBox wave;
		ScopedPointer<ParameterSlider> semi;
		ScopedPointer<ParameterSlider> fine;
	} oscSlider;

	typedef struct _envSlider {
		ScopedPointer<ParameterSlider> attack;
		ScopedPointer<ParameterSlider> decay;
		ScopedPointer<ParameterSlider> sustain;
		ScopedPointer<ParameterSlider> release;
		ToggleButton enabled;
	} envSlider;

	oscSlider oscillatorSliders[3];
	envSlider envelopeSliders[3];

	customLookAndFeel customLookAndFeel;
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;
private:	
	
	void sliderValueChanged(Slider* slider) override;
	void comboBoxChanged(ComboBox* comboBox) override;
	void buttonClicked(Button *button) override;
	void updateGUI();

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstPluginAudioProcessor& processor;

	
	Image logo;
	Label debug;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstPluginAudioProcessorEditor)
};
