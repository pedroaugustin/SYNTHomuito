/*
  ==============================================================================

    levelGUI.h
    Created: 10 Nov 2020 2:08:37pm
    Author:  preod

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class levelGUI  : public juce::Component
{
public:
    levelGUI(SynthoAudioProcessor &p);
    ~levelGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SynthoAudioProcessor& audioProcessor;

    juce::Slider levelSlider;
    juce::Slider detuneSlider;
    juce::ComboBox voicesBox;
  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (levelGUI)
};
