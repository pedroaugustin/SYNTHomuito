/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Oct 2020 3:55:06pm
    Author:  preod

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "C:\Development\Maximilian\src\maximilian.h"

class SynthVoice : public juce::SynthesiserVoice 
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    //=======================================================================================


    void setADSRSampleRate(double sampleRate)
    {
        adsr.setSampleRate(sampleRate);
    }

    //=======================================================================================

    void setParam(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        adsrParams.attack = *attack;
        adsrParams.decay = *decay;
        adsrParams.sustain = *sustain;
        adsrParams.release = *release;
    }

    //=======================================================================================

    
    void setOscType(std::atomic<float>* selection, std::atomic<float>* selection2, std::atomic<float>* selection3)
    {
        theWave = (int)*selection;
        theWave2 = (int)*selection2;
        osc2Level = *selection3;

    }

    //=======================================================================================

    void setVolume(std::atomic<float>* level) {

        volume = *level;
    }
    
    
    //=======================================================================================

    void setDetune(std::atomic<float>* detune) {   
        centsOff = (double)*detune;
    }


    double getOscType()
    {
        sampleAdjusted = log2(getSampleRate() / 44100) * 1200;
        double sample1, sample2; 

        if (theWave == 0) {
            sample1 = osc1.sinewave(frequency / std::pow(2.0, (sampleAdjusted + centsOff)/ 1200));
        }
        else if (theWave == 1) {
            sample1 = osc1.saw(frequency / std::pow(2.0, (sampleAdjusted + centsOff) / 1200));
        }
        else if (theWave == 2) {
            sample1 = osc1.square(frequency / std::pow(2.0, (sampleAdjusted + centsOff) / 1200));
        }
        else {
            sample1 = osc1.sinewave(frequency / std::pow(2.0, (sampleAdjusted + centsOff) / 1200));
        }

        if (theWave2 == 0) {
            sample2 = 0;
        }
        else if (theWave2 == 1) {
            sample2 = osc2.sinewave((frequency / std::pow(2.0, (sampleAdjusted + centsOff) / 1200)) / 2);
        }
        else if (theWave2 == 2) {
            sample2 = osc2.saw((frequency / std::pow(2.0, (sampleAdjusted + centsOff) / 1200)) / 2);
        }
        else if (theWave2 == 3) {
            sample2 = osc2.square((frequency / std::pow(2.0, (sampleAdjusted + centsOff) / 1200)) / 2);
        }
        else {
            sample2 = 0;
        }

        return sample1 + sample2 * osc2Level;
    }


    //=======================================================================================

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {

        adsr.noteOn();
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
        //juce::Logger::outputDebugString(std::to_string(frequency));
        //juce::Logger::outputDebugString(std::to_string(getSampleRate()));
        //juce::Logger::outputDebugString(std::to_string(sampleAdjusted));


    }

    //=======================================================================================

    void stopNote(float velocity, bool allowTailOff)
    {   
        adsr.noteOff();
        allowTailOff = true;

        if(velocity == 0)
            clearCurrentNote();
    }

    //=======================================================================================

    void pitchWheelMoved(int newPitchWheelValue)
    {
      

    }

    //=======================================================================================

    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }

    //=======================================================================================

    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        adsr.setParameters(adsrParams);
        for (int sample = 0; sample < numSamples; ++sample)
        {

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {   
                sampleToAdd = adsr.getNextSample() * getOscType() * level * volume;
                outputBuffer.addSample(channel, startSample, sampleToAdd);
             
                
            }
            
            ++startSample;
        }
    }

    //=======================================================================================

private:
    double frequency;
    double sampleAdjusted; 
    double centsOff;
    float level;
    float osc2Level;
    float sampleToAdd;
    float* samplePointer = &sampleToAdd;
    int theWave, theWave2;
    maxiOsc osc1;
    maxiOsc osc2;
    float volume;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
     
   
};