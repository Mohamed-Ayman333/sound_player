#include <JuceHeader.h>
#include "MainComponent.h"
#include "PlayerAudio.h"
#include "PlayerGUI.h"

using namespace juce;
// Our application class
class SimpleAudioPlayer : public JUCEApplication
{
    // The main window of the app
    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(String name)
            : DocumentWindow(name, Colours::black, DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true); // MainComponent = our UI + logic
            centreWithSize(1000, 1000);
            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

    std::unique_ptr<MainWindow> mainWindow;
public:
    const String getApplicationName() override { return "Simple Audio Player"; }
    const String getApplicationVersion() override { return "1.0"; }
    // Create and show the main window
    void initialise(const String&) override
    {
        
        mainWindow = std::make_unique<MainWindow>("7maza");
    }

    // Clean up
    void shutdown() override
    {
        mainWindow = nullptr; 
    }


    
    
};

// This macro starts the app
START_JUCE_APPLICATION(SimpleAudioPlayer)
