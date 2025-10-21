#include "PlayerGUI.h"


using namespace juce;

playerGUI::playerGUI() {
    playerAudio P1;
    
    //buttons
    
    loadButton.addListener(this);
    addAndMakeVisible(loadButton);

    restartButton.addListener(this);
    addAndMakeVisible(restartButton);

    stopButton.addListener(this);
    addAndMakeVisible(stopButton);

    mute.addListener(this);
    addAndMakeVisible(mute);

    pauseAndPlay.addListener(this);
    addAndMakeVisible(pauseAndPlay);

    goToStart.addListener(this);
    addAndMakeVisible(goToStart);

    goToEnd.addListener(this);
    addAndMakeVisible(goToEnd);

    loop.addListener(this);
    addAndMakeVisible(loop);

    // Volume sliders
   
    volumeSlider.setRange(0, 100, 1);
    volumeSlider.setValue(50);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    setSize(1000, 1000);
    
   
}
//screen color
void playerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}
//button Size And Location
void playerGUI::resized()
{
    
    loadButton.setBounds(20, 20, 100, 40);
    restartButton.setBounds(140, 20, 80, 40);
    stopButton.setBounds(240, 20, 80, 40);
    mute.setBounds(340, 20, 80, 40);
    pauseAndPlay.setBounds(20, 140, 100, 40);
    goToStart.setBounds(140, 140, 80, 40);
    goToEnd.setBounds(240, 140, 80, 40);
    loop.setBounds(340, 140, 80, 40);
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}

void playerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        P1.load_track();
    }

    if (button == &restartButton)
    {
        //god for now
        P1.restart();
        
    }

    if (button == &stopButton)
    {
        //to be edeted
        P1.stop();
    }
    if (button == &mute) {
        P1.mute(&volumeSlider);

    }
    if (button == &pauseAndPlay) {
        P1.pauseAndPlay();

    }
    if (button == &goToStart) {
        P1.goToStart();    

    }
    if (button == &goToEnd) {
        P1.goToEnd();

    }
    if (button == &loop) {
        P1.loop();

    }
}

void playerGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider) {
        P1.setVolume(slider);
    }
}
