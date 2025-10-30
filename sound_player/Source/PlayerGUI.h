#pragma once

#include <JuceHeader.h>
#include "PlayerAudio.h"

using namespace juce;

class marker:public Component {


	public:
	double position; 
	
	marker(double pos);

	void paint(Graphics& g) override;
};

class waver : public Component, public ChangeListener
{
public:
    playerAudio* pPtr;
    Rectangle<int> r;
	

    waver(playerAudio* P1);
    
    ~waver() override;

    void paint(Graphics& g) override;

    
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
	

    void changeListenerCallback(ChangeBroadcaster* source) override;
};

class playerGUI: public Button::Listener,
	public Slider::Listener,public Component {

	

	Slider volumeSlider;
	//Slider positionSlider;
	
	TextButton loadButton{ "Load Files"};
	TextButton restartButton{ "Restart" };
	TextButton stopButton{ "Stop" };
	TextButton mute{"mute"};
	TextButton pauseAndPlay{ "pauseAndPlay" };
	TextButton goToStart{ "go to start" };
	TextButton goToEnd{ "go to end" };
	TextButton loop{ "loop" };
	TextButton forward{ "10s forward" };
	TextButton backward{ "10s backward" };
	

	

public:
	
	
	playerAudio P1;
	waver wave{ &P1 };
	marker posetion_marke{ 0.0 };
	playerGUI();
	
	

	//screen color
	void paint(juce::Graphics& g) override;
	//button Size And Location
	void resized() override;

	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;
	


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(playerGUI)

};
