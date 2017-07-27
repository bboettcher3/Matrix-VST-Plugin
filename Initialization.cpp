//#include "Initialization.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "customLookAndFeel.h"

//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class FirstPluginAudioProcessorEditor::ParameterSlider : public Slider,
	private Timer
{
public:
	ParameterSlider(AudioProcessorParameter& p)
		: Slider(p.getName(256)), param(p)
	{
		setRange(0.0, 1.0, 0.0);
		startTimerHz(30);
		updateSliderPos();
	}

	void valueChanged() override
	{
		if (isMouseButtonDown())
			param.setValueNotifyingHost((float)Slider::getValue());
		else
			param.setValue((float)Slider::getValue());
	}

	void timerCallback() override { updateSliderPos(); }

	void startedDragging() override { param.beginChangeGesture(); }
	void stoppedDragging() override { param.endChangeGesture(); }

	double getValueFromText(const String& text) override { return param.getValueForText(text); }
	String getTextFromValue(double value) override { return param.getText((float)value, 1024); }

	void updateSliderPos()
	{
		const float newValue = param.getValue();

		if (newValue != (float)Slider::getValue() && !isMouseButtonDown())
			Slider::setValue(newValue);
	}

	AudioProcessorParameter& param;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
};

void FirstPluginAudioProcessorEditor::initOscillators() {
	addAndMakeVisible(oscillatorSliders[0].amplitude = new ParameterSlider(*processor.amp1Param));
	addAndMakeVisible(oscillatorSliders[1].amplitude = new ParameterSlider(*processor.amp2Param));
	addAndMakeVisible(oscillatorSliders[2].amplitude = new ParameterSlider(*processor.amp3Param));
	addAndMakeVisible(oscillatorSliders[0].octave = new ParameterSlider(*processor.octave1Param));
	addAndMakeVisible(oscillatorSliders[1].octave = new ParameterSlider(*processor.octave2Param));
	addAndMakeVisible(oscillatorSliders[2].octave = new ParameterSlider(*processor.octave3Param));
	//addAndMakeVisible(oscillatorSliders[0].wave = new ParameterSlider(*processor.wave1Param));
	//addAndMakeVisible(oscillatorSliders[1].wave = new ParameterSlider(*processor.wave2Param));
	//addAndMakeVisible(oscillatorSliders[2].wave = new ParameterSlider(*processor.wave3Param));
	addAndMakeVisible(oscillatorSliders[0].semi = new ParameterSlider(*processor.semi1Param));
	addAndMakeVisible(oscillatorSliders[1].semi = new ParameterSlider(*processor.semi2Param));
	addAndMakeVisible(oscillatorSliders[2].semi = new ParameterSlider(*processor.semi3Param));
	addAndMakeVisible(oscillatorSliders[0].fine = new ParameterSlider(*processor.fine1Param));
	addAndMakeVisible(oscillatorSliders[1].fine = new ParameterSlider(*processor.fine2Param));
	addAndMakeVisible(oscillatorSliders[2].fine = new ParameterSlider(*processor.fine3Param));
	for (int i = 0; i < 3; i++) {
		//set osc1 amplitude parameters
		oscillatorSliders[i].amplitude->setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].amplitude->setRange(0, 1, .008);
		oscillatorSliders[i].amplitude->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].amplitude->setPopupDisplayEnabled(false, this);
		oscillatorSliders[i].amplitude->setValue(1);
		oscillatorSliders[i].amplitude->setLookAndFeel(&customLookAndFeel);
		//set osc1 octave parameters
		oscillatorSliders[i].octave->setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].octave->setRange(-3, 3, 1);
		oscillatorSliders[i].octave->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].octave->setPopupDisplayEnabled(true, this);
		oscillatorSliders[i].octave->setValue(0);
		oscillatorSliders[i].octave->setLookAndFeel(&customLookAndFeel);
		//set osc1 wave parameters
		oscillatorSliders[i].wave.addItem("sine", 1);
		oscillatorSliders[i].wave.addItem("saw", 2);
		oscillatorSliders[i].wave.addItem("square", 3);
		oscillatorSliders[i].wave.addItem("noise", 4);
		oscillatorSliders[i].wave.addItem("triangle", 5);
		oscillatorSliders[i].wave.setSelectedId(1);
		//set osc1 semitone parameters
		oscillatorSliders[i].semi->setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].semi->setRange(-11, 11, 1);
		oscillatorSliders[i].semi->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].semi->setPopupDisplayEnabled(true, this);
		oscillatorSliders[i].semi->setValue(0);
		oscillatorSliders[i].semi->setLookAndFeel(&customLookAndFeel);
		//set osc1 fine parameters
		oscillatorSliders[i].fine->setSliderStyle(Slider::RotaryHorizontalDrag);
		oscillatorSliders[i].fine->setRange(-1, 1, .016);
		oscillatorSliders[i].fine->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		oscillatorSliders[i].fine->setPopupDisplayEnabled(true, this);
		oscillatorSliders[i].fine->setValue(0);
		oscillatorSliders[i].fine->setLookAndFeel(&customLookAndFeel);
		//add listener to slider
		oscillatorSliders[i].amplitude->addListener(this);
		oscillatorSliders[i].octave->addListener(this);
		oscillatorSliders[i].semi->addListener(this);
		oscillatorSliders[i].fine->addListener(this);
		oscillatorSliders[i].wave.addListener(this);

		//initialize osc values
		processor.masterOsc[i].amplitude = oscillatorSliders[i].amplitude->getValue();
		processor.masterOsc[i].octave = oscillatorSliders[i].octave->getValue();
		processor.masterOsc[i].semi = oscillatorSliders[i].semi->getValue();
		processor.masterOsc[i].fine = oscillatorSliders[i].fine->getValue();
		processor.masterOsc[i].wave = processor.SINE;


		addAndMakeVisible(debug);
		debug.setColour(Label::textColourId, Colours::black);
	}


}

void FirstPluginAudioProcessorEditor::initBounds() {
	oscillatorSliders[0].wave.setBounds(10, 75, 100, 35);
	oscillatorSliders[0].octave->setBounds(115, 75, 35, 35);
	oscillatorSliders[0].semi->setBounds(165, 75, 35, 35);
	oscillatorSliders[0].fine->setBounds(215, 75, 35, 35);
	oscillatorSliders[0].amplitude->setBounds(265, 75, 35, 35);

	oscillatorSliders[1].wave.setBounds(10, 175, 100, 35);
	oscillatorSliders[1].octave->setBounds(115, 175, 35, 35);
	oscillatorSliders[1].semi->setBounds(165, 175, 35, 35);
	oscillatorSliders[1].fine->setBounds(215, 175, 35, 35);
	oscillatorSliders[1].amplitude->setBounds(265, 175, 35, 35);

	oscillatorSliders[2].wave.setBounds(10, 275, 100, 35);
	oscillatorSliders[2].octave->setBounds(115, 275, 35, 35);
	oscillatorSliders[2].semi->setBounds(165, 275, 35, 35);
	oscillatorSliders[2].fine->setBounds(215, 275, 35, 35);
	oscillatorSliders[2].amplitude->setBounds(265, 275, 35, 35);

	envelopeSliders[0].enabled.setBounds(340, 265, 25, 25);
	envelopeSliders[0].attack->setBounds(380, 260, 35, 35);
	envelopeSliders[0].decay->setBounds(430, 260, 35, 35);
	envelopeSliders[0].sustain->setBounds(480, 260, 35, 35);
	envelopeSliders[0].release->setBounds(530, 260, 35, 35);

	envelopeSliders[1].enabled.setBounds(340, 345, 25, 25);
	envelopeSliders[1].attack->setBounds(380, 340, 35, 35);
	envelopeSliders[1].decay->setBounds(430, 340, 35, 35);
	envelopeSliders[1].sustain->setBounds(480, 340, 35, 35);
	envelopeSliders[1].release->setBounds(530, 340, 35, 35);

	envelopeSliders[2].enabled.setBounds(340, 425, 25, 25);
	envelopeSliders[2].attack->setBounds(380, 420, 35, 35);
	envelopeSliders[2].decay->setBounds(430, 420, 35, 35);
	envelopeSliders[2].sustain->setBounds(480, 420, 35, 35);
	envelopeSliders[2].release->setBounds(530, 420, 35, 35);
}

void FirstPluginAudioProcessorEditor::initLFO() {

}
void FirstPluginAudioProcessorEditor::initEnvelopes() {
	addAndMakeVisible(envelopeSliders[0].attack = new ParameterSlider(*processor.attack1Param));
	addAndMakeVisible(envelopeSliders[1].attack = new ParameterSlider(*processor.attack2Param));
	addAndMakeVisible(envelopeSliders[2].attack = new ParameterSlider(*processor.attack3Param));
	addAndMakeVisible(envelopeSliders[0].decay = new ParameterSlider(*processor.decay1Param));
	addAndMakeVisible(envelopeSliders[1].decay = new ParameterSlider(*processor.decay2Param));
	addAndMakeVisible(envelopeSliders[2].decay = new ParameterSlider(*processor.decay3Param));
	addAndMakeVisible(envelopeSliders[0].sustain = new ParameterSlider(*processor.sustain1Param));
	addAndMakeVisible(envelopeSliders[1].sustain = new ParameterSlider(*processor.sustain2Param));
	addAndMakeVisible(envelopeSliders[2].sustain = new ParameterSlider(*processor.sustain3Param));
	addAndMakeVisible(envelopeSliders[0].release = new ParameterSlider(*processor.release1Param));
	addAndMakeVisible(envelopeSliders[1].release = new ParameterSlider(*processor.release2Param));
	addAndMakeVisible(envelopeSliders[2].release = new ParameterSlider(*processor.release3Param));
	for (int i = 0; i < 3; i++) {
		//set env1 attack parameters
		envelopeSliders[i].attack->setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].attack->setRange(1, 2000, 8);
		envelopeSliders[i].attack->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].attack->setPopupDisplayEnabled(false, this);
		envelopeSliders[i].attack->setValue(100);
		envelopeSliders[i].attack->setLookAndFeel(&customLookAndFeel);

		//set env1 decay parameters
		envelopeSliders[i].decay->setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].decay->setRange(1, 2000, 8);
		envelopeSliders[i].decay->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].decay->setPopupDisplayEnabled(false, this);
		envelopeSliders[i].decay->setValue(10);
		envelopeSliders[i].decay->setLookAndFeel(&customLookAndFeel);

		//set env1 sustain parameters
		envelopeSliders[i].sustain->setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].sustain->setRange(0, 1, .008);
		envelopeSliders[i].sustain->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].sustain->setPopupDisplayEnabled(false, this);
		envelopeSliders[i].sustain->setValue(.8);
		envelopeSliders[i].sustain->setLookAndFeel(&customLookAndFeel);

		//set env1 release parameters
		envelopeSliders[i].release->setSliderStyle(Slider::RotaryHorizontalDrag);
		envelopeSliders[i].release->setRange(1, 2000, 8);
		envelopeSliders[i].release->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
		envelopeSliders[i].release->setPopupDisplayEnabled(false, this);
		envelopeSliders[i].release->setValue(200);
		envelopeSliders[i].release->setLookAndFeel(&customLookAndFeel);

		//swet env1 enabled parameters

		//addAndMakeVisible(envelopeSliders[i].enabled);
		//envelopeSliders[i].enabled.setColour(ToggleButton::ColourIds::tickColourId, Colours::black);
		//envelopeSliders[i].enabled.setColour(ToggleButton::ColourIds::tickDisabledColourId, Colours::black);
		if (i == 0) {
			//envelopeSliders[i].enabled.setToggleState(true, false);
		}

			//add listener to slider
		envelopeSliders[i].attack->addListener(this);
		envelopeSliders[i].decay->addListener(this);
		envelopeSliders[i].sustain->addListener(this);
		envelopeSliders[i].release->addListener(this);
		envelopeSliders[i].enabled.addListener(this);

		//initialize env values
		processor.masterEnv.env.setAttack(envelopeSliders[i].attack->getValue());
		processor.masterEnv.env.setDecay(envelopeSliders[i].decay->getValue());
		processor.masterEnv.env.setSustain(envelopeSliders[i].sustain->getValue());
		processor.masterEnv.env.setRelease(envelopeSliders[i].release->getValue());
	}
}
void FirstPluginAudioProcessorEditor::initVolume() {

}
void FirstPluginAudioProcessorEditor::initFilters() {

}

void FirstPluginAudioProcessor::addParameters() {
	//osc params
	addParameter(octave1Param = new AudioParameterInt("octave1", "octave1", -3, 3, 0));
	addParameter(octave2Param = new AudioParameterInt("octave2", "octave2", -3, 3, 0));
	addParameter(octave3Param = new AudioParameterInt("octave3", "octave3", -3, 3, 0));
	addParameter(semi1Param = new AudioParameterInt("semi1", "semi1", -11, 11, 0));
	addParameter(semi2Param = new AudioParameterInt("semi2", "semi2", -11, 11, 0));
	addParameter(semi3Param = new AudioParameterInt("semi3", "semi3", -11, 11, 0));
	addParameter(fine1Param = new AudioParameterFloat("fine1", "fine1", -1, 1, 0));
	addParameter(fine2Param = new AudioParameterFloat("fine2", "fine2", -1, 1, 0));
	addParameter(fine3Param = new AudioParameterFloat("fine3", "fine3", -1, 1, 0));
	addParameter(amp1Param = new AudioParameterFloat("amp1", "amp1", 0, 1, 1));
	addParameter(amp2Param = new AudioParameterFloat("amp2", "amp2", 0, 1, 0));
	addParameter(amp3Param = new AudioParameterFloat("amp3", "amp3", 0, 1, 0));
	addParameter(wave1Param = new AudioParameterInt("wave1", "wave1", 0, 1, 1));
	addParameter(wave2Param = new AudioParameterInt("wave2", "wave2", 0, 1, 0));
	addParameter(wave3Param = new AudioParameterInt("wave3", "wave3", 0, 1, 0));
	//env params
	addParameter(attack1Param = new AudioParameterFloat("attack1", "attack1", -1, 1, 0));
	addParameter(attack2Param = new AudioParameterFloat("attack2", "attack2", -1, 1, 0));
	addParameter(attack3Param = new AudioParameterFloat("attack3", "attack3", -1, 1, 0));
	addParameter(decay1Param = new AudioParameterFloat("decay1", "decay1", -1, 1, 0));
	addParameter(decay2Param = new AudioParameterFloat("decay2", "decay2", -1, 1, 0));
	addParameter(decay3Param = new AudioParameterFloat("decay3", "decay3", -1, 1, 0));
	addParameter(sustain1Param = new AudioParameterFloat("sustain1", "sustain1", -1, 1, 0));
	addParameter(sustain2Param = new AudioParameterFloat("sustain2", "sustain2", -1, 1, 0));
	addParameter(sustain3Param = new AudioParameterFloat("sustain3", "sustain3", -1, 1, 0));
	addParameter(release1Param = new AudioParameterFloat("release1", "release1", -1, 1, 0));
	addParameter(release2Param = new AudioParameterFloat("release2", "release2", -1, 1, 0));
	addParameter(release3Param = new AudioParameterFloat("release3", "release3", -1, 1, 0));
}