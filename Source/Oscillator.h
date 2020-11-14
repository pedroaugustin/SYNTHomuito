/*
  ==============================================================================

    Oscillator.h
    Created: 5 Nov 2020 10:57:48am
    Author:  preod

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator  : public juce::Component,
                    private juce::ComboBox::Listener
{
public:
    Oscillator(SynthoAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:
    juce::ComboBox oscMenu;
    juce::ComboBox osc2Menu;
    juce::Slider osc2Level;

    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>waveSelection;
    SynthoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
