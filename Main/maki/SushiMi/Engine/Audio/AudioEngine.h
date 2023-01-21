/*!
@file    AudioEngine.hpp
@author	 Aurelia Chong

         Header file for AudioEngine.cpp
*//*__________________________________________________________________________*/
#pragma warning(disable:26812)
/*                                                                   includes
----------------------------------------------------------------------------- */
#include <iostream>
#include <chrono>
#include <thread>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>
using namespace std;
using namespace FMOD;

namespace Core
{
    /*                                                                   zinstances
    ----------------------------------------------------------------------------- */
#define AudioManager _audioManager::Instance()

    /*                                                                   Class
    ----------------------------------------------------------------------------- */
    class _audioManager
    {

        /*                                                              Private Class
       ----------------------------------------------------------------------------- */
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


        /*                                                             Public Class
        ----------------------------------------------------------------------------- */
    public:
        static _audioManager& Instance(void);
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

    /*                                                             Call back function
     ----------------------------------------------------------------------------- */
    FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
        FMOD_CHANNELCONTROL_TYPE controlType,
        FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
        void* commandData1,
        void* commandData2);
}