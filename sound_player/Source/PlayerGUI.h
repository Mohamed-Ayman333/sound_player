#pragma once

#include <JuceHeader.h>
#include "PlayerAudio.h"

using namespace juce;

class waver : public Component, public ChangeListener
{
public:
    playerAudio* pPtr;
    Rectangle<int> r;

    waver(playerAudio* P1);
    waver(int x, int y, int width, int height, playerAudio& P1);
    ~waver() override;

    void paint(Graphics& g) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
};

class playerGUI: public Button::Listener,
	public Slider::Listener,public Component {

	

	Slider volumeSlider;
	
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
	//Graphics gr{};
	
	

public:
	
	
	playerAudio P1;
	waver wave{ &P1 };
	
	playerGUI();
	
	//AudioVisualiserComponent();

	//screen color
	void paint(juce::Graphics& g) override;
	//button Size And Location
	void resized() override;

	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;
	


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(playerGUI)

};
