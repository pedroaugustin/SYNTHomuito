/*
  ==============================================================================

    SynthSound.h
    Created: 29 Oct 2020 3:55:56pm
    Author:  preod

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*MidiNoteNumber*/) {
        return true;
    }

    bool appliesToChannel(int /*midiChanell*/) {
        return true; 
    }

};