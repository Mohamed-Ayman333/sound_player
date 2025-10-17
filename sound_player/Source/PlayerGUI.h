#pragma once

#include <JuceHeader.h>
#include "PlayerAudio.h"
#include <vector>
using namespace juce;

class playerGUI: public Button::Listener,
	public Slider::Listener,public Component{

	int volume;
	TextButton loadButton{ "Load Files"};
	TextButton restartButton{ "Restart" };
	TextButton stopButton{ "Stop" };
	Slider volumeSlider;
	TextButton mute{"mute"};

	TextButton pauseAndPlay{ "pauseAndPlay" };
	TextButton goToStart{ "go to start" };
	TextButton goToEnd{ "go to end" };
	
public:
	playerAudio P1;
	playerGUI();
	//screen color
	void paint(juce::Graphics& g) override;
	//button Size And Location
	void resized() override;

	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;
	/*void n(Slider s);*/
};