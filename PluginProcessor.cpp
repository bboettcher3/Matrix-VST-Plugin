/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstPluginAudioProcessor::FirstPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	//envArray[0].env.amplitude = 0;
	numVoices = 0;
}

FirstPluginAudioProcessor::~FirstPluginAudioProcessor()
{
}

//==============================================================================
const String FirstPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double FirstPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String FirstPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FirstPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FirstPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif



void FirstPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	//editor.debug.setText("got em", dontSendNotification);

	//buffer.clear();
	int time;
	MidiMessage m;
	float curSampleVal = 0;
	

	int numSamples = buffer.getNumSamples();
	int curSample = 0;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
		if (m.isNoteOn()) {
			if (numVoices <= 10) {
				//add voice, set trigger
				voices[numVoices].env.amplitude = 0;
				voices[numVoices].env.setAttack(masterEnv.env.attackms); //like this but in MS
				voices[numVoices].env.setDecay(masterEnv.env.decayms); //like this but in MS
				voices[numVoices].env.setSustain(masterEnv.env.sustain); //like this but in MS
				voices[numVoices].env.setRelease(masterEnv.env.releasems); //like this but in MS
				voices[numVoices].env.trigger = 1; //TODO: Set universal envelope params
				voices[numVoices].midiNum = m.getNoteNumber();
				//old code
				//envArray[0].env.trigger = 1;
				for (int i = 0; i < 3; i++) {
					//set freq of voice
					voices[numVoices].osc[i].freq = m.getMidiNoteInHertz(m.getNoteNumber() + masterOsc[i].semi + 12 * masterOsc[i].octave) + 20 * masterOsc[i].fine;
					voices[numVoices].osc[i].wave = masterOsc[i].wave;
					voices[numVoices].osc[i].amplitude = masterOsc[i].amplitude;
					//old code
					//oscArray[j].freq = m.getMidiNoteInHertz(m.getNoteNumber() + oscArray[j].semi + 12*oscArray[j].octave) + 20*oscArray[j].fine;
				}
				numVoices++;
			}
			
		}
		else if (m.isNoteOff()) {
			//remove voice based on freq
			for (int i = 0; i < numVoices; i++) {
				if (m.getNoteNumber() == voices[i].midiNum) {
					voices[i].env.trigger = 0;
				}
			}
			shiftArray();
			numVoices--;
			
			//debugInt = m.getNoteNumber() == voices[0].mi;
			//envArray[0].env.trigger = 0;
		}
	}
	
	while (--numSamples >= 0)
	{
		curSampleVal = 0;
		//make for loop go through all voices outside of this one
		for (int i = 0; i < numVoices; i++) {
			for (int j = 0; j < 3; j++) { 
				switch (voices[i].osc[j].wave) { 
				case SINE: curSampleVal += voices[i].osc[j].osc.sinewave(voices[i].osc[j].freq) * voices[i].osc[j].amplitude;
					break;
				case SAW: curSampleVal += voices[i].osc[j].osc.saw(voices[i].osc[j].freq) * voices[i].osc[j].amplitude;
					break;
				case NOISE: curSampleVal += voices[i].osc[j].osc.noise() * voices[i].osc[j].amplitude;
					break;
				case SQUARE: curSampleVal += voices[i].osc[j].osc.square(voices[i].osc[j].freq) * voices[i].osc[j].amplitude;
					break;
				case TRIANGLE: curSampleVal += voices[i].osc[j].osc.triangle(voices[i].osc[j].freq) * voices[i].osc[j].amplitude;
					break;
				}
			}
			curSampleVal *= voices[i].env.adsr(1, voices[i].env.trigger);
		}
		
		//outside of osc loop but inside voice loop, mult env by curSample
		//masterEnvVal = envArray[0].env.adsr(1, envArray[0].env.trigger);
		//curSampleVal *= masterEnvVal;
		for (int i = buffer.getNumChannels(); --i >= 0;) {
			buffer.addSample(i, curSample, curSampleVal);
		}
		curSample++;
	}
	
}


//==============================================================================
bool FirstPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FirstPluginAudioProcessor::createEditor()
{
    return new FirstPluginAudioProcessorEditor(*this);
}

//==============================================================================
void FirstPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FirstPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstPluginAudioProcessor();
}

void FirstPluginAudioProcessor::shiftArray() 
{
	mtxVoice tempVoice;
	for (int i = 0; i < numVoices; i++) {
		voices[i] = voices[i + 1];
	}
}