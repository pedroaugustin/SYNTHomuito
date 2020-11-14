/*
  ==============================================================================

    Filter.cpp
    Created: 5 Nov 2020 3:57:01pm
    Author:  preod

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"


//==============================================================================
Filter::Filter(SynthoAudioProcessor& p):  audioProcessor(p)
{
    setSize(200, 200);

    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterMenu);


    auto filterType = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.apvts, "FILTERTYPE", filterMenu);
    auto filterVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "FILTERCUTOFF", filterCutoff);
    auto resVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "FILTERRES", filterRes);

    filterCutoff.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 10000.0);
    filterCutoff.setValue(400.0);
    filterCutoff.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    filterCutoff.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);

    filterRes.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1.0, 10.0);
    filterRes.setValue(1.0);
    filterRes.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    filterRes.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterRes);
}

Filter::~Filter()
{
    

}

void Filter::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);
    g.drawText("Cutoff", 35, 90, 60, 100, juce::Justification::centredTop);
    g.drawText("Res", 105, 90, 60, 100, juce::Justification::centredTop);

    juce::Rectangle<float> area (25, 25, 150, 150);
    g.setColour(juce::Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);
}
