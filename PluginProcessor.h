/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Maximilian/maximilian.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>


//==============================================================================
/**
*/
class FirstPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    FirstPluginAudioProcessor();
    ~FirstPluginAudioProcessor();

	float noteOnVel;
	maxiEnv osc1Env;
	double masterEnvVal;
	typedef enum {
			SINE,
			SAW,
			NOISE,
			SQUARE,
			TRIANGLE
		} waveType;

		typedef struct _mtxOsc {
			maxiOsc osc;
			waveType wave;
			float freq;
			float octave;
			float semi;
			float fine;
			float amplitude;
		} mtxOsc;

		typedef struct _mtxEnv {
			maxiEnv env;
			Button::ButtonState enabled;
		} mtxEnv;

		typedef struct _mtxVoice {
			maxiEnv env;
			mtxOsc osc[3];
			int midiNum;
		} mtxVoice;

	//mtxVoice voices[10];
	std::vector<mtxVoice> voices;
	int numVoices;
	bool debugInt;
	
	//mtxEnv envArray[3]; //hard copy envelopes
	mtxOsc masterOsc[3]; //hard copy oscillators
	mtxEnv masterEnv;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

	void shiftArray();
	void addVoice(MidiMessage m);
	void processVoices(float curSampleVal);

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FirstPluginAudioProcessor)

		
	//maxiOsc osc1;
	//float osc1Freq;

};
