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
			bool isFree;
		} mtxVoice;

	//mtxVoice voices[10];
	//std::vector<mtxVoice> voices;

	mtxVoice voices[10];

	int numVoices;
	bool debugInt;
	
	//mtxEnv envArray[3]; //hard copy envelopes
	mtxOsc masterOsc[3]; //hard copy oscillators
	mtxEnv masterEnv;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

	void addVoice(MidiMessage m);
	float processVoices(float curSampleVal);
	void eraseStragglers();


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

	// Parameters to save
		//osc params
	AudioParameterInt* octave1Param; AudioParameterInt* octave2Param; AudioParameterInt* octave3Param;
	AudioParameterInt* semi1Param; AudioParameterInt* semi2Param; AudioParameterInt* semi3Param;
	AudioParameterFloat* fine1Param, fine2Param, fine3Param;
	AudioParameterFloat* amp1Param, amp2Param, amp3Param;
	AudioParameterInt* wave1Param, wave2Param, wave3Param;
		//env params
	AudioParameterFloat* attack1Param, attack2Param, attack3Param;
	AudioParameterFloat* decay1Param, decay2Param, decay3Param;
	AudioParameterFloat* sustain1Param, sustain2Param, sustain3Param;
	AudioParameterFloat* release1Param, release2Param, release3Param;


private:
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FirstPluginAudioProcessor)

		
	//maxiOsc osc1;
	//float osc1Freq;

};
