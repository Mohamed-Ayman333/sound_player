
#include "MainComponent.h"

MainComponent::MainComponent()
{
    
    addAndMakeVisible(g1);

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
    g1.P1.transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    g1.P1.transportSource.releaseResources();
}
//screen color
void MainComponent::paint(juce::Graphics& g)
{
    g1.paint(g);
}
//button Size And Location
void MainComponent::resized()
{
    g1.resized();
}

void MainComponent::buttonClicked(juce::Button* button)
{
    g1.buttonClicked(button);
    
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    g1.sliderValueChanged(slider);
}
