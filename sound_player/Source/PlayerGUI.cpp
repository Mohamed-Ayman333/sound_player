#include "PlayerGUI.h"


using namespace juce;

marker::marker(double pos) {

	position = pos;
}
void marker::paint(Graphics& g) {
    g.fillAll(juce::Colours::red);
}


waver::waver(playerAudio* P1) {

    pPtr = P1;
    if (pPtr)
        pPtr->thumbnail.addChangeListener(this);

};

waver::~waver()
{
    if (pPtr)
        pPtr->thumbnail.removeChangeListener(this);
}

void waver::changeListenerCallback(ChangeBroadcaster* source)
{

    MessageManager::callAsync([this] { repaint(); });
}

void waver::paint(Graphics& g) {
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::orange);

    if (pPtr != nullptr && pPtr->thumbnail.getNumChannels() > 0)
    {
        r = getLocalBounds();
        // draw the full duration from 0 to thumbnail total length
        const double totalLength = pPtr->thumbnail.getTotalLength();
        pPtr->thumbnail.drawChannels(g, r, 0.0, totalLength > 0.0 ? totalLength : 1.0, 0.8);
    }


}

playerGUI::playerGUI(){
    
   
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

    forward.addListener(this);
    addAndMakeVisible(forward);

    backward.addListener(this);
    addAndMakeVisible(backward);

    // sliders
   
    volumeSlider.setRange(0, 100, 1);
    volumeSlider.setValue(50);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    setSize(1000, 1000);

    
    
    //wave

    wave.addAndMakeVisible(&posetion_marke);
	
    addAndMakeVisible(wave);
    
   
}

//screen color
void playerGUI::paint(Graphics& g)
{
    
    g.fillAll(juce::Colours::black);
    
    
}
//button Size And Location
void playerGUI::resized()
{
    //r1
    loadButton.setBounds(20, 20, 100, 40);
    restartButton.setBounds(140, 20, 80, 40);
    stopButton.setBounds(240, 20, 80, 40);
    mute.setBounds(340, 20, 80, 40);
    //r2
    pauseAndPlay.setBounds(20, 140, 100, 40);
    goToStart.setBounds(140, 140, 80, 40);
    goToEnd.setBounds(240, 140, 80, 40);
    loop.setBounds(340, 140, 80, 40);
    //r3
    backward.setBounds(20, 260, 80, 40);
    forward.setBounds(140, 260, 100, 40);
    
    

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
    

    wave.setBounds(20, 340, getWidth() - 40, 60);
	posetion_marke.setBounds(0, 0, 1, wave.getHeight());
    
}

void playerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        
        P1.load_track([this] { wave.repaint(); });
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
    if (button == &forward) {
        P1.forward();

    }
    if (button == &backward) {
        P1.backward();

    }
}

void playerGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider) {
        P1.setVolume(slider);
    }
}

void waver::mouseDown(const MouseEvent& event)
{
    if (pPtr == nullptr)
        return;

    const int w = getWidth();
    if (w <= 0)
        return;

    const double total = pPtr->thumbnail.getTotalLength();
    if (total <= 0.0)
        return;

    const int x = jlimit(0, w - 1, event.getPosition().x);
    const double newPositionSeconds = (double) x / (double) w * total;

    pPtr->transportSource.setPosition(newPositionSeconds);
    
    
    if (auto* parentGui = dynamic_cast<playerGUI*>(getParentComponent()))
    {
       
        parentGui->posetion_marke.setBounds(x - 2, 0, 5, getHeight());
        parentGui->posetion_marke.repaint();
    }

    repaint();
}

void waver::mouseDrag(const MouseEvent& event)
{
    // Support scrubbing while dragging
    if (pPtr == nullptr)
        return;

    const int w = getWidth();
    if (w <= 0)
        return;

    const double total = pPtr->thumbnail.getTotalLength();
    if (total <= 0.0)
        return;

    int x = event.getPosition().x;
    x = jlimit(0, w - 1, x);
    const double newPositionSeconds = (double) x / (double) w * total;

    pPtr->transportSource.setPosition(newPositionSeconds);
    pPtr->transportSource.start();

    if (auto* parentGui = dynamic_cast<playerGUI*>(getParentComponent()))
    {

        parentGui->posetion_marke.setBounds(x - 2, 0, 5, getHeight());
        parentGui->posetion_marke.repaint();
    }
    repaint();
}


