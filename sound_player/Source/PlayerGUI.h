#pragma once

#include <JuceHeader.h>
#include "PlayerAudio.h"
#include <vector>

using namespace juce;
class waver;
class playerGUI;
class marker;
class playlistModel :public ListBoxModel {

public:
	playerAudio* pPtr;
	
	playerGUI* guiptr;

	playlistModel(playerAudio* P1, playerGUI* gui);
	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	void listBoxItemClicked(int row, const juce::MouseEvent& e) override;
	void menu_action(int option, int row);

};
class marklistModel :public ListBoxModel {

public:
	playerAudio* pPtr;
	
	playerGUI* guiptr;

	marklistModel(playerAudio* P1, playerGUI* gui);
	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	void listBoxItemClicked(int row, const juce::MouseEvent& e) override;
	void menu_action(int option, int row);

};
class marker :public Component {


public:
	double position;

	marker(double pos);

	void paint(Graphics& g) override;
	void mouseDown(const MouseEvent& event);
	void menu_action(int option, waver* parentWaver);
};

class waver : public Component, public ChangeListener
{
public:
	playerAudio* pPtr;
	playerGUI* guiptr;
	Rectangle<int> r;
	marker posetion_marke{ 0.0 };
	std::vector<std::unique_ptr<marker>> markers;
	marker looping_marker[2]{ marker(0.0),marker(0.0) };

	waver(playerAudio* P1, playerGUI* gui);

	~waver() override;

	void paint(Graphics& g) override;


	void mouseDown(const MouseEvent& event) override;
	void mouseDrag(const MouseEvent& event) override;


	void changeListenerCallback(ChangeBroadcaster* source) override;
};

class playerGUI : public Button::Listener,
	public Slider::Listener, public Component, public Timer, public ChangeListener {


public:
	Slider volumeSlider;
	Slider positionSlider;
	Slider speedSlider;


	ImageButton loadButton;
	ImageButton restartButton;
	ImageButton stopButton;
	ImageButton mute;
	ImageButton pauseAndPlay;
	ImageButton goToStart;
	ImageButton goToEnd;
	ImageButton loop;
	ImageButton forward;
	ImageButton backward;
	ImageButton playlists;
	ImageButton make_a_playlist;
	ImageButton add_to_playlist;
	ImageButton next;
	ImageButton back;
	ImageButton markes;
	ImageButton shuf;

	playlistModel playlist_model{ &P1,this };
	ListBox play_list;
	marklistModel marklist_model{ &P1,this };
	ListBox mark_list;

	Label file_data;








	playerAudio P1;
	waver wave{ &P1,this };
	marker* posetion_marke_ptr = &wave.posetion_marke;
	bool markerLoopEnabled{ false };
	bool wasPlayingLastTick = false;
	bool isShuf = false;


	playerGUI();



	//screen color
	void paint(Graphics& g) override;
	//button Size And Location
	void resized() override;

	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;
	void timerCallback();
	void changeListenerCallback(juce::ChangeBroadcaster* source);

	void menu_action(int result, playerGUI* gui);


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(playerGUI)

};