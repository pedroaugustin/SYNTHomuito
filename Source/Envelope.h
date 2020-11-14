/*
  ==============================================================================

    Envelope.h
    Created: 5 Nov 2020 3:07:03pm
    Author:  preod

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(SynthoAudioProcessor& p);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:


    SynthoAudioProcessor& audioProcessor;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
