/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
OriginalFxAudioProcessorEditor::OriginalFxAudioProcessorEditor (OriginalFxAudioProcessor& p)
        : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    /*
    room size
    damping
    wet level
    dry level
    width
    freeze mode
    */

    /*
     * all the following sliders have the same range (0-1) hence they can be created in a loop
     */
    for (auto itr = reverbSliderArray.begin(); itr != reverbSliderArray.end(); itr++) {

        addAndMakeVisible(itr);
        itr->setSliderStyle(Slider::LinearVertical);
        itr->addListener(this);
        itr->setRange(0.01f, 1.0f, 0.01f);
    }

    /*
     * filters have the same ranges so they are created in a loop
     */
    for (auto &filterSlider : filterSliders) {
        addAndMakeVisible(filterSlider);
        filterSlider.setSliderStyle(Slider::Rotary);
        filterSlider.addListener(this);
        filterSlider.setRange(50.0f, 20000.0f, 50.0f);
    }

    setSize(1000, 400);
    startTimer(50);
}

OriginalFxAudioProcessorEditor::~OriginalFxAudioProcessorEditor() = default;

//==============================================================================
void OriginalFxAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::grey);
}


void OriginalFxAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


    int x, y, width, height;
    height = 100;
    width = 150;
    x = 10;
    y = 20;

    for (auto &itr : reverbSliderArray) {
        itr.setBounds(x, y, width, height);
        x += 150;
    }

    y += height + 10;
    x = 10;
    for (auto &filterSlider : filterSliders) {
        filterSlider.setBounds(x, y, width, height);
        x += 150;
    }
}

void OriginalFxAudioProcessorEditor::sliderValueChanged(Slider *slider) {

    //for (Slider &thisSlider: reverbSliderArray) {
    //	if (slider == &thisSlider) {
    //		processor.theReverbParameters.damping = 1.0;
    //	}
    //}

    if (slider == &reverbSliderArray[0]) {
        processor.theReverbParameters.roomSize = static_cast<float>(slider->getValue());
    }
    else if (slider == &reverbSliderArray[1]) {
        processor.theReverbParameters.damping = static_cast<float>(slider->getValue());
    }
    else if (slider == &reverbSliderArray[2]) {
        processor.theReverbParameters.wetLevel = static_cast<float>(slider->getValue());
    }
    else if (slider == &reverbSliderArray[3]) {
        processor.theReverbParameters.dryLevel = static_cast<float>(slider->getValue());
    }
    else if (slider == &reverbSliderArray[4]) {
        processor.theReverbParameters.width = static_cast<float>(slider->getValue());
    }
    else if (slider == &reverbSliderArray[5]) {
        processor.theReverbParameters.freezeMode = static_cast<float>(slider->getValue());
    }
    else if (slider == &filterSliders[0]) {
        *processor.highPassFilterCutOff = slider->getValue();
    }
    else if (slider == &filterSliders[1]) {
        *processor.lowPassFilterCutOff = slider->getValue();
    }

}

void OriginalFxAudioProcessorEditor::timerCallback() {
}