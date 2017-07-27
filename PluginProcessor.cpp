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
                       ),
#endif 
	octave1Param(nullptr), octave2Param(nullptr), octave3Param(nullptr),
 semi1Param(nullptr), semi2Param(nullptr), semi3Param(nullptr),
 fine1Param(nullptr), fine2Param(nullptr), fine3Param(nullptr),
 amp1Param(nullptr), amp2Param(nullptr), amp3Param(nullptr),
 wave1Param(nullptr), wave2Param(nullptr), wave3Param(nullptr),
 attack1Param(nullptr), attack2Param(nullptr), attack3Param(nullptr),
 decay1Param(nullptr), decay2Param(nullptr), decay3Param(nullptr),
 sustain1Param(nullptr), sustain2Param(nullptr), sustain3Param(nullptr),
 release1Param(nullptr), release2Param(nullptr), release3Param(nullptr) 
{
	addParameters();
	
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

	buffer.clear();
	int time;
	MidiMessage m;
	float curSampleVal = 0;

	int numSamples = buffer.getNumSamples();
	int curSample = 0;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {
		if (m.isNoteOn()) {
			if (numVoices <= 10) {
				//add voice, set trigger
				addVoice(m);

			}
			
		}
		else if (m.isNoteOff()) {
			//remove voice based on freq

			for (int i = 0; i < 10; i++) {
				if (m.getNoteNumber() == voices[i].midiNum && !voices[i].isFree) {
					voices[i].env.trigger = 0;
					//debugInt = true;
					break;
				}
				//debugInt = false;
			}
			
		}
	}
	//get rid of voices with a tiny amplitude
	eraseStragglers();

	while (--numSamples >= 0)
	{
		curSampleVal = 0;

		curSampleVal += processVoices(curSampleVal);
		
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
	// Here's an example of how you can use XML to make it easy and more robust:

	// Create an outer XML element..
	XmlElement xml("MYPLUGINSETTINGS");

	// Store the values of all our parameters, using their param ID as the XML attribute
	for (int i = 0; i < getNumParameters(); ++i)
		if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
			xml.setAttribute(p->paramID, p->getValue());

	// then use this helper function to stuff it into the binary blob and return it..
	copyXmlToBinary(xml, destData);
}

void FirstPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		// make sure that it's actually our type of XML object..
		if (xmlState->hasTagName("MYPLUGINSETTINGS"))
		{

			// Now reload our parameters..
			for (int i = 0; i < getNumParameters(); ++i)
				if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
					p->setValue((float)xmlState->getDoubleAttribute(p->paramID, p->getValue()));
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstPluginAudioProcessor();
}

void FirstPluginAudioProcessor::eraseStragglers() {
	for (int i = 0; i < 10; i++) {
		if ((voices[i].env.trigger == 0) && (voices[i].env.amplitude < .01) && !(voices[i].isFree)) {

			voices[i].isFree = true;
			numVoices--;
		}
	}
}

void FirstPluginAudioProcessor::addVoice(MidiMessage m) {
	bool isDuplicate = false;
	for (int i = 0; i < 10; i++) {
		if (voices[i].midiNum == m.getNoteNumber() && !voices[i].isFree) {
			voices[i].env.trigger = 1;
			isDuplicate = true;
			break;
		}
	}
	if (!isDuplicate) {
		for (int i = 0; i < 10; i++) {
			if (voices[i].isFree) {
				voices[i].isFree = false;
				voices[i].env.amplitude = 0;
				voices[i].env.setAttack(masterEnv.env.attackms);
				voices[i].env.setDecay(masterEnv.env.decayms);
				voices[i].env.setSustain(masterEnv.env.sustain);
				voices[i].env.setRelease(masterEnv.env.releasems);
				voices[i].env.trigger = 1;
				voices[i].midiNum = m.getNoteNumber();
				for (int j = 0; j < 3; j++) {
					//set freq of voice
					voices[i].osc[j].freq = m.getMidiNoteInHertz(m.getNoteNumber() + masterOsc[j].semi + 12 * masterOsc[j].octave) + 20 * masterOsc[j].fine;
					voices[i].osc[j].osc.phaseReset(0);
				}
				numVoices++;
				break;
			}
		}
			
		
	}
	
}

float FirstPluginAudioProcessor::processVoices(float curSampleVal) {
	float innerSampleVal = 0;
	for (int i = 0; i < 10; i++) {
		if (!voices[i].isFree) {
			innerSampleVal = 0;
			for (int j = 0; j < 3; j++) {
				switch (masterOsc[j].wave) {
				case SINE: innerSampleVal += voices[i].osc[j].osc.sinewave(voices[i].osc[j].freq) * masterOsc[j].amplitude;
					break;
				case SAW: innerSampleVal += voices[i].osc[j].osc.saw(voices[i].osc[j].freq) * masterOsc[j].amplitude;
					break;
				case NOISE: innerSampleVal += voices[i].osc[j].osc.noise() * masterOsc[j].amplitude;
					break;
				case SQUARE: innerSampleVal += voices[i].osc[j].osc.square(voices[i].osc[j].freq) * masterOsc[j].amplitude;
					break;
				case TRIANGLE: innerSampleVal += voices[i].osc[j].osc.triangle(voices[i].osc[j].freq) * masterOsc[j].amplitude;
					break;
				}
			}
			innerSampleVal *= voices[i].env.adsr(1, voices[i].env.trigger);
			curSampleVal += innerSampleVal;
		}
		
	}
	return curSampleVal;
}