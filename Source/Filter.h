/*
  ==============================================================================

    Filter.h
    Created: 5 Nov 2020 3:57:01pm
    Author:  preod

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(SynthoAudioProcessor& p);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SynthoAudioProcessor& audioProcessor;
    juce::Slider filterCutoff;
    juce::Slider filterRes;

    juce::ComboBox filterMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
