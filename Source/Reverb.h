/*
  ==============================================================================

    Reverb.h
    Created: 11 Nov 2020 3:16:46pm
    Author:  preod

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Reverb  : public juce::Component
{
public:
    Reverb(SynthoAudioProcessor& p);
    ~Reverb() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SynthoAudioProcessor &audioProcessor;

    juce::Slider roomsizeSlider;
    juce::Slider dampingSlider;
    juce::Slider wetlevelSlider;
    juce::Slider drylevelSlider;
    juce::Slider widthSlider;
    juce::ToggleButton freezemodeButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Reverb)
};
