/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "levelGUI.h"
#include "Reverb.h"

//==============================================================================
/**
*/
class SynthoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthoAudioProcessorEditor (SynthoAudioProcessor&);
    ~SynthoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthoAudioProcessor& audioProcessor;
    
    Oscillator oscGUI;
    Envelope envGUI; 
    Filter filterGUI;
    levelGUI levelGUI;
    Reverb reverbGUI;
   
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthoAudioProcessorEditor)
};
