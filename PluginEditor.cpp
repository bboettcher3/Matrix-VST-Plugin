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

	initOscillators();
	initEnvelopes();

	//set matrix logo parameters
	File logoPath = "C:/Users/Asus1/Documents/JUCE/projects/FirstPlugin/Resources/logoCrop.png";
	logo = ImageFileFormat::loadFrom(logoPath);

	//timer for updating GUI
	startTimerHz(30);

}

FirstPluginAudioProcessorEditor::~FirstPluginAudioProcessorEditor()
{
}

void FirstPluginAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox) {

		for (int i = 0; i < 3; i++) {
			if (comboBox == &oscillatorSliders[i].wave) {
				switch (oscillatorSliders[i].wave.getSelectedId()) {
				case 1: 
					processor.masterOsc[i].wave = processor.SINE;
					break;
				case 2: 
					processor.masterOsc[i].wave = processor.SAW;
					break;
				case 3: 
					processor.masterOsc[i].wave = processor.SQUARE;
					break;
				case 4: 
					processor.masterOsc[i].wave = processor.NOISE;
					break;
				case 5:
					processor.masterOsc[i].wave = processor.TRIANGLE;
					break;
				}
			}
			processor.masterOsc[i].osc.phaseReset(0);
		}
	
}

void FirstPluginAudioProcessorEditor::sliderValueChanged(Slider* slider) {

		for (int i = 0; i < 3; i++) {
			if (slider == (Slider*)&oscillatorSliders[i].amplitude) {
				processor.masterOsc[i].amplitude = oscillatorSliders[i].amplitude->getValue();
			}
			else if (slider == (Slider*)&oscillatorSliders[i].octave) {
				processor.masterOsc[i].octave = oscillatorSliders[i].octave->getValue();
			}
			else if (slider == (Slider*)&oscillatorSliders[i].semi) {
				processor.masterOsc[i].semi = oscillatorSliders[i].semi->getValue();
			}
			else if (slider == (Slider*)&oscillatorSliders[i].fine) {
				processor.masterOsc[i].fine = oscillatorSliders[i].fine->getValue();
			}
			else if (slider == (Slider*)&envelopeSliders[i].attack) {
				processor.masterEnv.env.setAttack(envelopeSliders[i].attack->getValue());
			}
			else if (slider == (Slider*)&envelopeSliders[i].decay) {
				processor.masterEnv.env.setDecay(envelopeSliders[i].decay->getValue());
			}
			else if (slider == (Slider*)&envelopeSliders[i].sustain) {
				processor.masterEnv.env.setSustain(envelopeSliders[i].sustain->getValue());
			}
			else if (slider == (Slider*)&envelopeSliders[i].release) {
				processor.masterEnv.env.setRelease(envelopeSliders[i].release->getValue());
			}
		}

	

}

void FirstPluginAudioProcessorEditor::buttonClicked(Button *button) {
	for (int i = 0; i < 3; i++) {
		if (button == &envelopeSliders[i].enabled) {
			processor.masterEnv.enabled = envelopeSliders[i].enabled.getState();
			break;
		}
		
	}
}

//==============================================================================
void FirstPluginAudioProcessorEditor::paint (Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);
	g.drawImage(logo, 30, 0, 110, 44, 0, 0, 125, 50);

    g.setColour (Colours::midnightblue);
	//g.setOpacity(.7f);

	//oscillator text
	g.setFont(15.0f);
	g.drawFittedText("Octave", 85, 100, 100, 30, Justification::centred, 1);
	g.drawFittedText("Semi", 135, 100, 100, 30, Justification::centred, 1);
	g.drawFittedText("Fine", 185, 100, 100, 30, Justification::centred, 1);
	g.drawFittedText("Amp", 235, 100, 100, 30, Justification::centred, 1);
	g.drawFittedText("Octave", 85, 200, 100, 30, Justification::centred, 1);
	g.drawFittedText("Semi", 135, 200, 100, 30, Justification::centred, 1);
	g.drawFittedText("Fine", 185, 200, 100, 30, Justification::centred, 1);
	g.drawFittedText("Amp", 235, 200, 100, 30, Justification::centred, 1);
	g.drawFittedText("Octave", 85, 300, 100, 30, Justification::centred, 1);
	g.drawFittedText("Semi", 135, 300, 100, 30, Justification::centred, 1);
	g.drawFittedText("Fine", 185, 300, 100, 30, Justification::centred, 1);
	g.drawFittedText("Amp", 235, 300, 100, 30, Justification::centred, 1);

	//envelope text
	g.drawFittedText("A", 350, 295, 100, 30, Justification::centred, 1);
	g.drawFittedText("D", 400, 295, 100, 30, Justification::centred, 1);
	g.drawFittedText("S", 450, 295, 100, 30, Justification::centred, 1);
	g.drawFittedText("R", 500, 295, 100, 30, Justification::centred, 1);
	g.drawFittedText("Amplitude Envelope", 580, 265, 140, 30, Justification::centred, 1);

	//envelope text
	g.drawFittedText("A", 350, 375, 100, 30, Justification::centred, 1);
	g.drawFittedText("D", 400, 375, 100, 30, Justification::centred, 1);
	g.drawFittedText("S", 450, 375, 100, 30, Justification::centred, 1);
	g.drawFittedText("R", 500, 375, 100, 30, Justification::centred, 1);
	//g.drawFittedText("Amplitude Envelope", 580, 265, 140, 30, Justification::centred, 1);

	//envelope text
	g.drawFittedText("A", 350, 455, 100, 30, Justification::centred, 1);
	g.drawFittedText("D", 400, 455, 100, 30, Justification::centred, 1);
	g.drawFittedText("S", 450, 455, 100, 30, Justification::centred, 1);
	g.drawFittedText("R", 500, 455, 100, 30, Justification::centred, 1);
	//g.drawFittedText("Amplitude Envelope", 580, 265, 140, 30, Justification::centred, 1);

	g.setFont(15.0f);
	g.drawFittedText("File Management", 250, 10, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(210, 5, 400, 35, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Randomization", 650, 10, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(615, 5, 180, 35, 10.0f, 2.0f);

	//draw rounded rect (oscillators)
	g.drawRoundedRectangle(5, 45, 305, 300, 10.0f, 2.0f);

	//draw rounded rect
	//g.drawRoundedRectangle(210, 45, 400, 200, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Filters", 100, 355, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(5, 350, 305, 145, 10.0f, 2.0f);

	g.setFont(15.0f);
	//g.drawFittedText("Envelopes", 350, 360, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(315, 250, 480, 245, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("LFO", 3350, 60, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(315, 45, 295, 200, 10.0f, 2.0f);

	g.setFont(15.0f);
	g.drawFittedText("Volume Controls", 620, 50, 100, 30, Justification::centred, 1);
	//draw rounded rect
	g.drawRoundedRectangle(615, 45, 180, 200, 10.0f, 2.0f);

}

void FirstPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	initBounds();
	
	debug.setBounds(350, 300, 200, 200);
}

void FirstPluginAudioProcessorEditor::updateGUI() {

}

//==============================================================================
void FirstPluginAudioProcessorEditor::timerCallback()
{
	updateGUI();
}
