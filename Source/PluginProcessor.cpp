/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthoAudioProcessor::SynthoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, "Parameters", createParameters())
#endif
{

    mySynth.clearVoices();
    
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
    

}

SynthoAudioProcessor::~SynthoAudioProcessor()
{
}

//==============================================================================
const juce::String SynthoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthoAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


//==============================================================================
void SynthoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    lastSampleRate = sampleRate; //Em caso de mudar de interface
    juce::ignoreUnused(samplesPerBlock); //Ignora samples não usadas do ultimo key press
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    stateVariableFilter.reset();
    stateVariableFilter.prepare(spec);
    reverb.setSampleRate(sampleRate);
    
    updateFilter();
    
    
}

void SynthoAudioProcessor::setReverbParams(std::atomic<float>* roomSize, std::atomic<float>* damping, std::atomic<float>* wetLevel, std::atomic<float>* dryLevel, std::atomic<float>* width, std::atomic<float>* freezeMode)
{
    
    reverbParams.roomSize = *roomSize;
    reverbParams.damping = *damping;
    reverbParams.wetLevel = *wetLevel;
    reverbParams.dryLevel = *dryLevel;
    reverbParams.width = *width;
    reverbParams.freezeMode = *freezeMode;
    reverb.setParameters(reverbParams);

}

void SynthoAudioProcessor::updateFilter()
{
    int menuChoice = *apvts.getRawParameterValue("FILTERTYPE");
    int freq = *apvts.getRawParameterValue("FILTERCUTOFF");
    int res = *apvts.getRawParameterValue("FILTERRES");

    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    
    if (menuChoice == 1) 
    {
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }

    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    } 

}

void SynthoAudioProcessor::updateVoices()
{
    int index = (int)*apvts.getRawParameterValue("NUMVOICES");
   
    if (mySynth.getNumVoices() != index) {
        mySynth.clearVoices();
        for (int i = 0; i < index; i++) {
            mySynth.addVoice(new SynthVoice());
        }
    }
    
}

void SynthoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->setCurrentPlaybackSampleRate(lastSampleRate);
            myVoice->setADSRSampleRate(lastSampleRate);
            myVoice->setDetune(apvts.getRawParameterValue("DETUNE"));
            setReverbParams(apvts.getRawParameterValue("ROOMSIZE"),
                apvts.getRawParameterValue("DAMPING"),
                apvts.getRawParameterValue("WETLEVEL"),
                apvts.getRawParameterValue("DRYLEVEL"),
                apvts.getRawParameterValue("WIDTH"),
                apvts.getRawParameterValue("FREEZEMODE"));

            myVoice->setParam(apvts.getRawParameterValue("ATTACK"),
                apvts.getRawParameterValue("DECAY"),
                apvts.getRawParameterValue("SUSTAIN"), 
                apvts.getRawParameterValue("RELEASE"));

            myVoice->setOscType(apvts.getRawParameterValue("WAVETYPE"),apvts.getRawParameterValue("WAVETYPE2"),apvts.getRawParameterValue("OSC2LEVEL"));   
            myVoice->setVolume(apvts.getRawParameterValue("LEVEL"));

        }
    }
    buffer.clear();
    

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
   
    
    updateFilter();
    updateVoices();
   
    float* const firstChannel = buffer.getWritePointer(0, 0);

    if (buffer.getNumChannels() > 1)
    {
        reverb.processStereo(firstChannel,
            buffer.getWritePointer(1, 0),
              buffer.getNumSamples());
    }
    else
    {
        reverb.processMono(firstChannel, buffer.getNumSamples());
    }

   

    juce::dsp::AudioBlock<float> block(buffer);
    stateVariableFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool SynthoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthoAudioProcessor::createEditor()
{
    return new SynthoAudioProcessorEditor (*this);
}

//==============================================================================
void SynthoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthoAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout SynthoAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters; 

    //CONTROLS
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("LEVEL", "Level", juce::NormalisableRange<float>(0.0f, 1.0f), 0.2f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("NUMVOICES", "NumVoices", juce::NormalisableRange<float>(1, 10), 5));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DETUNE", "Detune", juce::NormalisableRange<float>(0.0f, 3000.0f), 0.0f));
    
    //ADSR
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>(0.1f, 1.0f), 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>(0.1f, 2.0f), 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>(0.1f, 5.0f), 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>(0.1f, 5.0f), 0.8f));
    
    //FILTER
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERTYPE", "FilterType", juce::NormalisableRange<float>(0, 2), 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "FilterCutOff", juce::NormalisableRange<float>(20.0f,10000.0f), 400.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "FilterRes", juce::NormalisableRange<float>(1.0f, 10.0f), 1.0f));
   
    //OSCI
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("WAVETYPE", "WaveType", juce::NormalisableRange<float>(0, 2), 1));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("WAVETYPE2", "WaveType2", juce::NormalisableRange<float>(0, 3), 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2LEVEL", "Osc2Level", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f));
     
    //REVERB 
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ROOMSIZE", "RoomSize", juce::NormalisableRange<float>(0.0f, 1.0f), 0.6f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DAMPING", "Damping", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("WETLEVEL", "WetLevel", juce::NormalisableRange<float>(0.0f, 1.0f), 0.2f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DRYLEVEL", "DryLevel", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("WIDTH", "Width", juce::NormalisableRange<float>(0.0f, 1.0f), 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FREEZEMODE", "FreezeMode", juce::NormalisableRange<float>(0, 1), 0));
    
    return { parameters.begin(), parameters.end() };
}
    

