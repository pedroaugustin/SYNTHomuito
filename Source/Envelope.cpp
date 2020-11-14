/*
  ==============================================================================

    Envelope.cpp
    Created: 5 Nov 2020 3:07:03pm
    Author:  preod

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"
 

//==============================================================================
Envelope::Envelope(SynthoAudioProcessor& p): audioProcessor(p)
{
    setSize(200, 200);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 1.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&attackSlider);
    auto attackAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "ATTACK", attackSlider);


    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 2.0f);
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&decaySlider);
    auto decayAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "DECAY", decaySlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 5.0f);
    sustainSlider.setValue(0.5f);
    sustainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&sustainSlider);
    auto sustainAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "SUSTAIN", sustainSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&releaseSlider);
    auto releaseAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "RELEASE", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.drawText("Envelope", titleArea, juce::Justification::centredTop);
    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    

    juce::Rectangle<float> area(25, 25, 150, 150);
    g.setColour(juce::Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);

}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;
     
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight));

}
