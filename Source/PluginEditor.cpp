/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthoAudioProcessorEditor::SynthoAudioProcessorEditor (SynthoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGUI(p), envGUI(p), filterGUI(p), levelGUI(p), reverbGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be

    setSize (600, 400);

    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI); 
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&levelGUI);
    addAndMakeVisible(&reverbGUI);


      
}

SynthoAudioProcessorEditor::~SynthoAudioProcessorEditor()
{
}

//==============================================================================
void SynthoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.setFont (30.0f);
    //g.drawFittedText ("SYNTHo", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthoAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(area.getX(), area.getY(), componentWidth, componentHeight);
    envGUI.setBounds(area.getX() + componentWidth, area.getY() , componentWidth, componentHeight);
    filterGUI.setBounds(area.getX() + componentWidth * 2, area.getY() , componentWidth, componentHeight);
    levelGUI.setBounds(area.getX(), area.getY() + componentHeight, componentWidth, componentHeight);
    reverbGUI.setBounds(area.getX() + componentWidth, area.getY() + componentHeight, componentWidth + 100, componentHeight);
    
    
    
}


