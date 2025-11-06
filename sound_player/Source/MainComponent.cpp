
#include "MainComponent.h"

MainComponent::MainComponent()
{
    
    addAndMakeVisible(g1);
	addAndMakeVisible(g2);
    

    setAudioChannels(0, 2);
    
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
   g1.P1.prepareToPlay(samplesPerBlockExpected, sampleRate);
   
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    g1.P1.getNextAudioBlock(bufferToFill);
    
}

void MainComponent::releaseResources()
{
    g1.P1.transportSource.releaseResources();
}
void MainComponent::resized()
{
    g1.setBounds(0,0,getWidth()*0.5,getHeight());
	g2.setBounds(getWidth() * 0.5, 0, getWidth() * 0.5, getHeight());
}


void MainComponent::buttonClicked(juce::Button* button)
{
    g1.buttonClicked(button);
    
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    g1.sliderValueChanged(slider);
}
