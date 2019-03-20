/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
using std::array;


//==============================================================================
/**
*/

// OriginalFxAudioProcessorEditor
class OriginalFxAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer
{
public:
    explicit OriginalFxAudioProcessorEditor (OriginalFxAudioProcessor&);
    ~OriginalFxAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider *slider) override;
    void timerCallback() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    // creating a slider array of size 6 for the following
    /*
    room size (0, 1)
    damping (0, 1)
    wet level (0, 1)
    dry level (0, 1)
    width (0, 1)
    freeze mode (0, 1)
    */
    std::array<Slider, 6> reverbSliderArray;

    std::array<Slider, 2> filterSliders;

    OriginalFxAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OriginalFxAudioProcessorEditor)
};
