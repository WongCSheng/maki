#pragma warning(disable:26812)
#include <iostream>
#include <chrono>
#include <thread>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>
using namespace std;
using namespace FMOD;

#define AudioManager _audioManager::Instance()

class _audioManager
{
private:
    _audioManager(void);
    ~_audioManager(void);
    System* fmodSystem = NULL;
    Channel* channel = nullptr;
    Channel* musicChannel = nullptr;
    ChannelGroup* channelGroup = nullptr;
    map<string, Sound*> soundDatabase;
    map<string, Sound*> musicDatabase;
    bool isActive = true;
    
public:
    static _audioManager& Instance(void);
    //bool succeededOrWarn(const std::string& message, FMOD_RESULT result);
    Channel* GetMusicChannel(void);
    void CleanPlaying(void);
    void PlayClip(string audiClip);
    void PlayMusic(string musicTrack);
    void StopMusic(void);
    void SetAudioVolume(float volume);
    void SetMusicVolume(float volume);
    void Update(void);
    void LoadSound(string name);
    void LoadMusic(string name);
    void UnloadSound(string name);
    void UnloadMusic(string name);
    void Free(void);
    Sound* GetSound(string name);
};

FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
    FMOD_CHANNELCONTROL_TYPE controlType,
    FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
    void* commandData1,
    void* commandData2);
