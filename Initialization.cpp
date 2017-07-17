//#include "Initialization.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "customLookAndFeel.h"

void FirstPluginAudioProcessorEditor::initOscillators() {
	for (int i = 0; i < 3; i++) {
		//set osc1 amplitude parameters
		oscillatorSliders[i].amplitude.setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].amplitude.setRange(0, 1, .008);
		oscillatorSliders[i].amplitude.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].amplitude.setPopupDisplayEnabled(false, this);
		oscillatorSliders[i].amplitude.setValue(1);
		addAndMakeVisible(&oscillatorSliders[i].amplitude);
		oscillatorSliders[i].amplitude.setLookAndFeel(&customLookAndFeel);
		//set osc1 octave parameters
		oscillatorSliders[i].octave.setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].octave.setRange(-3, 3, 1);
		oscillatorSliders[i].octave.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].octave.setPopupDisplayEnabled(true, this);
		oscillatorSliders[i].octave.setValue(0);
		addAndMakeVisible(&oscillatorSliders[i].octave);
		oscillatorSliders[i].octave.setLookAndFeel(&customLookAndFeel);
		//set osc1 wave parameters
		oscillatorSliders[i].wave.addItem("sine", 1);
		oscillatorSliders[i].wave.addItem("saw", 2);
		oscillatorSliders[i].wave.addItem("square", 3);
		oscillatorSliders[i].wave.addItem("noise", 4);
		oscillatorSliders[i].wave.addItem("triangle", 5);
		oscillatorSliders[i].wave.setSelectedId(1);
		addAndMakeVisible(&oscillatorSliders[i].wave);

		//set osc1 semitone parameters
		oscillatorSliders[i].semi.setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].semi.setRange(-11, 11, 1);
		oscillatorSliders[i].semi.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].semi.setPopupDisplayEnabled(true, this);
		oscillatorSliders[i].semi.setValue(0);
		addAndMakeVisible(&oscillatorSliders[i].semi);
		oscillatorSliders[i].semi.setLookAndFeel(&customLookAndFeel);
		//set osc1 fine parameters
		oscillatorSliders[i].fine.setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].fine.setRange(-1, 1, .016);
		oscillatorSliders[i].fine.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].fine.setPopupDisplayEnabled(true, this);
		oscillatorSliders[i].fine.setValue(0);
		addAndMakeVisible(&oscillatorSliders[i].fine);
		oscillatorSliders[i].fine.setLookAndFeel(&customLookAndFeel);

		//add listener to slider
		oscillatorSliders[i].amplitude.addListener(this);
		oscillatorSliders[i].octave.addListener(this);
		oscillatorSliders[i].semi.addListener(this);
		oscillatorSliders[i].fine.addListener(this);
		oscillatorSliders[i].wave.addListener(this);

		//initialize osc values
		processor.masterOsc[i].amplitude = oscillatorSliders[i].amplitude.getValue();
		processor.masterOsc[i].octave = oscillatorSliders[i].octave.getValue();
		processor.masterOsc[i].semi = oscillatorSliders[i].semi.getValue();
		processor.masterOsc[i].fine = oscillatorSliders[i].fine.getValue();

		addAndMakeVisible(debug);
		debug.setColour(Label::textColourId, Colours::black);
	}

	for (int i = 0; i < 10; i++) {
		processor.voices[i].env.trigger = 0;
		processor.voices[i].env.amplitude = 0;
	}

}

void FirstPluginAudioProcessorEditor::initBounds() {
	oscillatorSliders[0].wave.setBounds(10, 75, 100, 35);
	oscillatorSliders[0].octave.setBounds(115, 75, 35, 35);
	oscillatorSliders[0].semi.setBounds(165, 75, 35, 35);
	oscillatorSliders[0].fine.setBounds(215, 75, 35, 35);
	oscillatorSliders[0].amplitude.setBounds(265, 75, 35, 35);

	oscillatorSliders[1].wave.setBounds(10, 175, 100, 35);
	oscillatorSliders[1].octave.setBounds(115, 175, 35, 35);
	oscillatorSliders[1].semi.setBounds(165, 175, 35, 35);
	oscillatorSliders[1].fine.setBounds(215, 175, 35, 35);
	oscillatorSliders[1].amplitude.setBounds(265, 175, 35, 35);

	oscillatorSliders[2].wave.setBounds(10, 275, 100, 35);
	oscillatorSliders[2].octave.setBounds(115, 275, 35, 35);
	oscillatorSliders[2].semi.setBounds(165, 275, 35, 35);
	oscillatorSliders[2].fine.setBounds(215, 275, 35, 35);
	oscillatorSliders[2].amplitude.setBounds(265, 275, 35, 35);

	envelopeSliders[0].enabled.setBounds(340, 265, 25, 25);
	envelopeSliders[0].attack.setBounds(380, 260, 35, 35);
	envelopeSliders[0].decay.setBounds(430, 260, 35, 35);
	envelopeSliders[0].sustain.setBounds(480, 260, 35, 35);
	envelopeSliders[0].release.setBounds(530, 260, 35, 35);

	envelopeSliders[1].enabled.setBounds(340, 345, 25, 25);
	envelopeSliders[1].attack.setBounds(380, 340, 35, 35);
	envelopeSliders[1].decay.setBounds(430, 340, 35, 35);
	envelopeSliders[1].sustain.setBounds(480, 340, 35, 35);
	envelopeSliders[1].release.setBounds(530, 340, 35, 35);

	envelopeSliders[2].enabled.setBounds(340, 425, 25, 25);
	envelopeSliders[2].attack.setBounds(380, 420, 35, 35);
	envelopeSliders[2].decay.setBounds(430, 420, 35, 35);
	envelopeSliders[2].sustain.setBounds(480, 420, 35, 35);
	envelopeSliders[2].release.setBounds(530, 420, 35, 35);
}

void FirstPluginAudioProcessorEditor::initLFO() {

}
void FirstPluginAudioProcessorEditor::initEnvelopes() {
	for (int i = 0; i < 3; i++) {
		//set env1 attack parameters
		envelopeSliders[i].attack.setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].attack.setRange(1, 2000, 8);
		envelopeSliders[i].attack.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].attack.setPopupDisplayEnabled(false, this);
		envelopeSliders[i].attack.setValue(100);
		addAndMakeVisible(&envelopeSliders[i].attack);
		envelopeSliders[i].attack.setLookAndFeel(&customLookAndFeel);

		//set env1 decay parameters
		envelopeSliders[i].decay.setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].decay.setRange(1, 2000, 8);
		envelopeSliders[i].decay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].decay.setPopupDisplayEnabled(false, this);
		envelopeSliders[i].decay.setValue(10);
		addAndMakeVisible(&envelopeSliders[i].decay);
		envelopeSliders[i].decay.setLookAndFeel(&customLookAndFeel);

		//set env1 sustain parameters
		envelopeSliders[i].sustain.setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].sustain.setRange(0, 1, .008);
		envelopeSliders[i].sustain.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].sustain.setPopupDisplayEnabled(false, this);
		envelopeSliders[i].sustain.setValue(.8);
		addAndMakeVisible(&envelopeSliders[i].sustain);
		envelopeSliders[i].sustain.setLookAndFeel(&customLookAndFeel);

		//set env1 release parameters
		envelopeSliders[i].release.setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].release.setRange(1, 2000, 8);
		envelopeSliders[i].release.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].release.setPopupDisplayEnabled(false, this);
		envelopeSliders[i].release.setValue(200);
		addAndMakeVisible(&envelopeSliders[i].release);
		envelopeSliders[i].release.setLookAndFeel(&customLookAndFeel);

		//swet env1 enabled parameters
		addAndMakeVisible(envelopeSliders[i].enabled);
		envelopeSliders[i].enabled.setColour(ToggleButton::ColourIds::tickColourId, Colours::black);
		envelopeSliders[i].enabled.setColour(ToggleButton::ColourIds::tickDisabledColourId, Colours::black);
		if (i == 0) {
			envelopeSliders[i].enabled.setToggleState(true, false);
		}

			//add listener to slider
		envelopeSliders[i].attack.addListener(this);
		envelopeSliders[i].decay.addListener(this);
		envelopeSliders[i].sustain.addListener(this);
		envelopeSliders[i].release.addListener(this);
		envelopeSliders[i].enabled.addListener(this);

		//initialize env values
		processor.masterEnv.env.setAttack(envelopeSliders[i].attack.getValue());
		processor.masterEnv.env.setDecay(envelopeSliders[i].decay.getValue());
		processor.masterEnv.env.setSustain(envelopeSliders[i].sustain.getValue());
		processor.masterEnv.env.setRelease(envelopeSliders[i].release.getValue());
	}
}
void FirstPluginAudioProcessorEditor::initVolume() {

}
void FirstPluginAudioProcessorEditor::initFilters() {

}