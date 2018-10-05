#include <Windows.h>
#include <fstream>
#include <complex>
#include <vector>
#include <fftw3.h>
#include <string>
#include "include/al.h"
#include "include/alc.h"
#define _USE_MATH_DEFINES
#include <ATLComTime.h>
#include <cmath>
#include <iostream>
using namespace std;
const int BUF_COUNT = 5;

// Главный класс, который и отвечает за всю работу со звуком 
class MSoundSystem
{
protected:
	// Как говорится, "OpenAL related stuff"
	ALCdevice * in_device;
	ALCdevice * out_device;

	ALCcontext * context;
	ALuint al_source;

	ALuint al_buffers[BUF_COUNT];

	// FFTW related stuff
	fftw_plan p_forward, p_backward;
	fftw_complex * cbuf;
	double * dbuf;

	// Здесь уже наше, промежуточный буфер
	ALshort *play_buf;
	int read_buf_size;
	int play_buf_size;


public:
	MSoundSystem();
	void update();
	
	//// Понизить сигнал на октаву
	//void transform()
	//{

	//	for (unsigned int i = 0; i < play_buf_size; ++i)
	//	{
	//		if (i > play_buf_size / 2)
	//		{
	//			cbuf[i][0] = 0.0;
	//			cbuf[i][1] = 0.0;
	//		}
	//		else
	//		{
	//			cbuf[i][0] = cbuf[i*2][0];
	//			cbuf[i][1] = cbuf[i*2][1];
	//		}
	//	}
	//}

	// Повысить сигнал на октаву
	void transform();

	//// Фильтр высоких частот
	//void transform()
	//{
	//	for (unsigned int i = 0; i < play_buf_size; ++i)
	//	{
	//		if ( ((float)i / (float)play_buf_size * 44100.0f) > 3000 )
	//		{
	//			cbuf[i][0] = 0.0;
	//			cbuf[i][1] = 0.0;
	//		}
	//	}
	//}
	//

	//// Фильтр низких частот
	//void transform()
	//{
	//	for (unsigned int i = 0; i < play_buf_size; ++i)
	//	{
	//		if (((float)i / (float)play_buf_size * 44100.0f) < 3000)
	//		{
	//			cbuf[i][0] = 0.0;
	//			cbuf[i][1] = 0.0;
	//		}
	//	}
	//}

	void process();
	~MSoundSystem();
	void StartLoop();
};

MSoundSystem::MSoundSystem() {
	// Здесь значения надо подбирать экспериментально
	read_buf_size = 44100;
	play_buf_size = 1024;
	play_buf = new ALshort[play_buf_size];

	// Инициализируем OpenAL и создаем всякие штучки
	out_device = alcOpenDevice(0);
	context = alcCreateContext(out_device, 0);
	alcMakeContextCurrent(context);

	in_device = alcCaptureOpenDevice(0, 44100, AL_FORMAT_MONO16, read_buf_size);

	alGenSources(1, &al_source);
	alGenBuffers(BUF_COUNT, al_buffers);

	// Заполняем первую очередь
	for (int i = 0; i < play_buf_size; ++i) play_buf[i] = 0;
	for (int i = 0; i < BUF_COUNT; ++i)
	{
		alBufferData(al_buffers[i], AL_FORMAT_MONO16, play_buf, play_buf_size * sizeof(ALshort), 44100);
	}

	// инициализируем fftw и буферы для него
	cbuf = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * play_buf_size);
	dbuf = (double*)fftw_malloc(sizeof(double) * play_buf_size);
	p_forward = fftw_plan_dft_r2c_1d(play_buf_size, dbuf, cbuf, FFTW_ESTIMATE);
	p_backward = fftw_plan_dft_c2r_1d(play_buf_size, cbuf, dbuf, FFTW_ESTIMATE);
	if (!p_forward)
	{
		printf("Error creating the forward FFT plan!");
	}
	if (!p_backward)
	{
		printf("Error creating the forward FFT plan!");
	}

	// Здесь начинаем запись и воспроизведение
	alSourceQueueBuffers(al_source, BUF_COUNT, al_buffers);
	alSourcePlay(al_source);
	alcCaptureStart(in_device);
}

void MSoundSystem::update() {
	ALint samples, val, state;

	// Если источник вдруг перестал играть, то пнем его
	alGetSourcei(al_source, AL_SOURCE_STATE, &state);
	if (state != AL_PLAYING) alSourcePlay(al_source);

	alcGetIntegerv(in_device, ALC_CAPTURE_SAMPLES, sizeof(samples), &samples);
	alGetSourcei(al_source, AL_BUFFERS_PROCESSED, &val);

	// Пока есть свободные буферы воспроизведения и пока есть готовые
	// данные, которые надо воспроизвести, считываем из захвата и
	// пишем на выход
	while (((val--) > 0) && (samples > play_buf_size))
	{
		ALuint buffer;

		alcCaptureSamples(in_device, play_buf, play_buf_size);

		// ... пишем, да только не сразу, а после обработки ;)
		process();

		// Вытаскиваем последний буфер из очереди, наполняем
		// данными и обратно в очередь
		alSourceUnqueueBuffers(al_source, 1, &buffer);
		alBufferData(buffer, AL_FORMAT_MONO16, play_buf, play_buf_size * sizeof(ALshort), 44100);
		alSourceQueueBuffers(al_source, 1, &buffer);

		alcGetIntegerv(in_device, ALC_CAPTURE_SAMPLES, sizeof(samples), &samples);
	}
}

void MSoundSystem::process() {
	double inv_n = 1.0 / (double)play_buf_size;

	// конвертируем буфер из ALshort в double, делаем FFT и нормализуем результат
	for (unsigned int i = 0; i < play_buf_size; ++i) dbuf[i] = (double)play_buf[i] / (double)((ALushort)(-1)) * 2.0;

	fftw_execute(p_forward);
	for (unsigned int i = 0; i < play_buf_size; ++i)
	{
		cbuf[i][0] *= inv_n;
		cbuf[i][1] *= inv_n;
	}

	// ну, поехали
	transform();

	// делаем обратный FFT и возвращаем обработанный сигнал в буфер
	fftw_execute(p_backward);
	for (unsigned int i = 0; i < play_buf_size; ++i)
	{
		double c = dbuf[i];
		if (c > 1.0) c = 1.0;
		if (c < -1.0) c = -1.0;

		play_buf[i] = (c * (double)((ALushort)(-1))) / 2;
	}
}

void MSoundSystem::transform() {
	for (unsigned int i = play_buf_size; i > 1; --i)
	{
		cbuf[i][0] = cbuf[i / 2][0];
		cbuf[i][1] = cbuf[i / 2][1];
	}
}

void MSoundSystem::StartLoop() {
	while (1) {
		update();
	}
}

MSoundSystem::~MSoundSystem() {
	fftw_destroy_plan(p_backward);
	fftw_destroy_plan(p_forward);
	fftw_free(cbuf);
	fftw_free(dbuf);
	alcCaptureStop(in_device);
	alcCaptureCloseDevice(in_device);
}