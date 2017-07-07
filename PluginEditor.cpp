/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FirstPluginAudioProcessorEditor::FirstPluginAudioProcessorEditor(FirstPluginAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 500);

	//set osc1 amplitude parameters
	osc1Amp.setSliderStyle(Slider::RotaryHorizontalDrag);
	osc1Amp.setRange(0, 127, 1);
	osc1Amp.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	osc1Amp.setPopupDisplayEnabled(false, this);
	osc1Amp.setValue(1);
	addAndMakeVisible(&osc1Amp);
	osc1Amp.setLookAndFeel(&customLookAndFeel);
	//set osc1 octave parameters
	osc1Octave.setSliderStyle(Slider::RotaryHorizontalDrag);
	osc1Octave.setRange(-3, 3, 1);
	osc1Octave.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	osc1Octave.setPopupDisplayEnabled(true, this);
	osc1Octave.setValue(0);
	addAndMakeVisible(&osc1Octave);
	osc1Octave.setLookAndFeel(&customLookAndFeel);
	//set osc1 wave parameters
	osc1Wave.setSliderStyle(Slider::RotaryHorizontalDrag);
	osc1Wave.setRange(0, 3, 1);
	osc1Wave.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	osc1Wave.setPopupDisplayEnabled(false, this);
	osc1Wave.setValue(0);
	addAndMakeVisible(&osc1Wave);
	osc1Wave.setLookAndFeel(&customLookAndFeel);
	//set osc1 semitone parameters
	osc1Semi.setSliderStyle(Slider::RotaryHorizontalDrag);
	osc1Semi.setRange(-11, 11, 1);
	osc1Semi.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	osc1Semi.setPopupDisplayEnabled(true, this);
	osc1Semi.setValue(0);
	addAndMakeVisible(&osc1Semi);
	osc1Semi.setLookAndFeel(&customLookAndFeel);
	//set osc1 fine parameters
	osc1Fine.setSliderStyle(Slider::RotaryHorizontalDrag);
	osc1Fine.setRange(-99, 99, 1);
	osc1Fine.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	osc1Fine.setPopupDisplayEnabled(true, this);
	osc1Fine.setValue(0);
	addAndMakeVisible(&osc1Fine);
	osc1Fine.setLookAndFeel(&customLookAndFeel);

	addAndMakeVisible(debug);
	debug.setText("TESTINGGGG", dontSendNotification);
	debug.setColour(Label::textColourId, Colours::black);
	osc1Amp.addListener(this);
	

	//set matrix logo parameters
	File logoPath = "C:/Users/Asus1/Documents/JUCE/projects/FirstPlugin/Resources/logoCrop.png";
	logo = ImageFileFormat::loadFrom(logoPath);

	//add listener to slider
	osc1Amp.addListener(this);

	//timer for updating GUI
	startTimerHz(30);
}

FirstPluginAudioProcessorEditor::~FirstPluginAudioProcessorEditor()
{
}

void FirstPluginAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	//debug.setText((String)processor.osc1Env.trigger, dontSendNotification);
}

//==============================================================================
void FirstPluginAudioProcessorEditor::paint (Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);
	g.drawImage(logo, 30, 0, 110, 44, 0, 0, 125, 50);

    g.setColour (Colours::midnightblue);
	//g.setOpacity(.7f);

	g.setFont(15.0f);
	g.drawFittedText("Amp", 135, 75, 100, 30, Justification::centred, 1);
	g.drawFittedText("Wave", -25, 75, 100, 30, Justification::centred, 1);
	g.drawFittedText("Octave", 20, 75, 100, 30, Justification::centred, 1);
	g.drawFittedText("Semi", 60, 75, 100, 30, Justification::centred, 1);
	g.drawFittedText("Fine", 98, 75, 100, 30, Justification::centred, 1);

	//g.drawFittedText(osc1EnvVal.toString(), 98, 75, 100, 30, Justification::centred, 1);

	g.setFont(15.0f);
	g.drawFittedText("File Management", 250, 10, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(210, 5, 400, 35, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Randomization", 650, 10, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(615, 5, 180, 35, 10.0f, 2.0f);

	//g.setFont (15.0f);
	//g.drawFittedText ("Oscillators", 100, 50, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(5, 45, 200, 300, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Oscilloscope", 220, 50, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(210, 45, 400, 200, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Filters", 100, 355, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(5, 350, 305, 145, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Envelopes", 350, 360, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(315, 250, 480, 245, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("LFO", 200, 255, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(210, 250, 100, 95, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Volume Controls", 620, 50, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(615, 45, 180, 200, 10.0f, 2.0f);

}

void FirstPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	osc1Fine.setBounds(130, 50, 35, 35);
	osc1Octave.setBounds(50, 50, 35, 35);
	osc1Wave.setBounds(10, 50, 35, 35);
	osc1Semi.setBounds(90, 50, 35, 35);
	osc1Amp.setBounds(170, 50, 35, 35);
	debug.setBounds(250, 200, 200, 200);
}

void FirstPluginAudioProcessorEditor::updateGUI() {
	debug.setText((String)(processor.osc1Val), dontSendNotification);
}

//==============================================================================
void FirstPluginAudioProcessorEditor::timerCallback()
{
	updateGUI();
}
