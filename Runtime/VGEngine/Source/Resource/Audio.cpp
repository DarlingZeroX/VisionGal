#include "Resource/Audio.h"
#include "Core/VFS.h"

namespace VisionGal
{
	AudioClip::AudioClip():
        audioSpec(),
        audioBuffer(nullptr), bufferLength(0)
	{
	}

	AudioClip::~AudioClip()
	{
        Clear();
	}

    bool AudioClip::Open(const String& filePath)
    {
        auto result = VFS::SafeReadFileFromVFS(filePath, [&](const VFS::DataRef& data) {
            ioStream = SDL_IOFromMem(data->data(), data->size());
			audioData = data; // ������Ƶ�������ã�������ǰ�ͷ�
            return 0;
            });

        if (result < 0)
            return false;

        return LoadAudio();
    }

    void AudioClip::Clear()
    {
        if (audioBuffer) {
            SDL_free(audioBuffer);
            audioBuffer = nullptr;
        }
    }

    bool AudioClip::LoadAudio()
    {
        // �ͷž�����
        if (audioBuffer) {
            SDL_free(audioBuffer);
            audioBuffer = nullptr;
        }

        // ������Ƶ�ļ�
        if (SDL_LoadWAV_IO(ioStream, 1, &audioSpec, &audioBuffer, &bufferLength) == false) {
            std::cerr << "����WAVʧ��: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    AudioPlayer::AudioPlayer()
        :
        audioStream(nullptr),
        isPlaying(false),
        bufferCopy(nullptr)
    {
        Init();
    }

    AudioPlayer::~AudioPlayer()
    {
        Stop();
    }

    bool AudioPlayer::Init()
    {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) == false) {
            std::cerr << "��Ƶ��ʼ��ʧ��: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }

    bool AudioPlayer::OpenAudioClip(const Ref<AudioClip>& clip)
    {
        audioClip = clip;

        Stop();

        // �����������ڲ���
        bufferCopy = new uint8_t[audioClip->bufferLength];
        memcpy(bufferCopy, audioClip->audioBuffer, audioClip->bufferLength);
        bufferPosition = bufferCopy;
        remainingLength = audioClip->bufferLength;

        return true;
    }

    // ��Ƶ���ص�����
    static void AudioStreamCallback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount) {
        AudioPlayer* player = static_cast<AudioPlayer*>(userdata);
        player->HandleAudioStream(stream, additional_amount);
    }

    bool AudioPlayer::Play()
    {
        if (!audioClip || isPlaying) return false;

        // ����Ƶ�豸��������
        audioStream = SDL_OpenAudioDeviceStream(
            SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,  // Ĭ�ϲ����豸
            &audioClip->audioSpec,               // ��Ƶ���
            AudioStreamCallback,                 // �ص�����
            this                                 // �û�����
        );

        if (!audioStream) {
            std::cerr << "������Ƶ��ʧ��: " << SDL_GetError() << std::endl;
            return false;
        }

        // ��ʼ����
        SDL_ResumeAudioStreamDevice(audioStream);
        isPlaying = true;
        return true;
    }

    void AudioPlayer::SetLoop(bool enable)
    {
        m_EnableLoop = enable;
    }

    void AudioPlayer::Stop()
    {
        if (!isPlaying) return;

        // ��ͣ��������
        SDL_PauseAudioStreamDevice(audioStream);
        SDL_DestroyAudioStream(audioStream);
        audioStream = nullptr;

        // �ͷŸ��ƻ�����
        if (bufferCopy) {
            delete[] bufferCopy;
            bufferCopy = nullptr;
        }

        isPlaying = false;
    }

    bool AudioPlayer::IsPlayingAudio() const
    {
        return isPlaying;
    }

    bool AudioPlayer::IsLooping() const
    {
        return m_EnableLoop;
    }

    void AudioPlayer::SetVolume(float v)
    {
        m_Volume = SDL_clamp(v, 0.0f, 1.0f);
    }

    float AudioPlayer::GetVolume() const
    {
        return m_Volume;
    }

    void AudioPlayer::HandleAudioStream(SDL_AudioStream* stream, int need_bytes)
    {
        if (remainingLength <= 0) {
            if (m_EnableLoop)
            {
                bufferPosition = bufferCopy;
                remainingLength = audioClip->bufferLength;
            }
            else
            {
                // ������ϣ���侲��
                SDL_PauseAudioStreamDevice(stream);
                isPlaying = false;
                return;
            }
        }

        // ����ɸ��Ƶ�������
        int copy_bytes = SDL_min(remainingLength, need_bytes);

        // ������� < 1������������
        if (m_Volume < 0.99f) {
            int16_t* samples = reinterpret_cast<int16_t*>(bufferPosition);
            size_t sampleCount = copy_bytes / sizeof(int16_t);
            std::vector<int16_t> temp(samples, samples + sampleCount);

            for (auto& s : temp) {
                s = static_cast<int16_t>(s * m_Volume);
            }
            SDL_PutAudioStreamData(stream, temp.data(), copy_bytes);
        }
        else {
            // �������
            SDL_PutAudioStreamData(stream, bufferPosition, copy_bytes);
        }
        //SDL_PutAudioStreamData(stream, bufferPosition, copy_bytes);

        // ����λ�ú�ʣ�೤��
        bufferPosition += copy_bytes;
        remainingLength -= copy_bytes;
    }
}
