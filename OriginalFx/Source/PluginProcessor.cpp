/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
OriginalFxAudioProcessor::OriginalFxAudioProcessor()
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
    addParameter(highPassFilterCutOff = new AudioParameterFloat("FilterCutoffHighPass", "Filter Cutoff High Pass", 50.0f, 20000.0f, 50.0f));
    addParameter(lowPassFilterCutOff = new AudioParameterFloat("FilterQHighPass", "Filter Q High Pass", 50.0f, 20000.0f, 50.0f));

    // for (auto itr=reverbSliderArray)
    // default are applied
    float damping, roomSize, dryLevel, wetLevel, width, freezeMode;
    damping = 1.0;
    roomSize = 0.5;
    dryLevel = 0.3;
    wetLevel = 0.2;
    width = 0.6;
    freezeMode = 0.5;

    theReverbParameters.damping = damping;
    theReverbParameters.roomSize = roomSize;
    theReverbParameters.dryLevel = dryLevel;
    theReverbParameters.wetLevel = wetLevel;
    theReverbParameters.width = width;
    theReverbParameters.freezeMode = freezeMode;

    theReverb.setParameters(theReverbParameters);

}

OriginalFxAudioProcessor::~OriginalFxAudioProcessor()
{
}

//==============================================================================
const String OriginalFxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OriginalFxAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool OriginalFxAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool OriginalFxAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double OriginalFxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OriginalFxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int OriginalFxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OriginalFxAudioProcessor::setCurrentProgram (int index)
{
}

const String OriginalFxAudioProcessor::getProgramName (int index)
{
    return {};
}

void OriginalFxAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OriginalFxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..


}

void OriginalFxAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OriginalFxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void OriginalFxAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    // for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        theReverb.setParameters(theReverbParameters);
        theReverb.processMono(channelData, buffer.getNumSamples());

//        // High pass filter
//        IIRCoefficients highCoefficients = IIRCoefficients::makeHighPass(getSampleRate(), *highPassFilterCutOff);
//        filter.setCoefficients(highCoefficients);
//        filter.processSamples(buffer.getWritePointer(channel), buffer.getNumSamples());
//
//        // Low Pass filter
//        IIRCoefficients lowCoefficients = IIRCoefficients::makeLowPass(getSampleRate(), *lowPassFilterCutOff);
//        filter.setCoefficients(lowCoefficients);
//
//        filter.processSamples(channelData, buffer.getNumSamples());


        // ..do something to the data...
    } // OriginalFxAudioProcessor

    for (int channel = totalNumInputChannels; channel < getTotalNumOutputChannels(); ++channel) {
        buffer.clear(channel, 0, buffer.getNumSamples());
    }
}

void OriginalFxAudioProcessor::shrinkBuffer(float* buffer) {


}


//==============================================================================
bool OriginalFxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OriginalFxAudioProcessor::createEditor()
{
    return new OriginalFxAudioProcessorEditor (*this);
}

//==============================================================================
void OriginalFxAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OriginalFxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OriginalFxAudioProcessor();
}
