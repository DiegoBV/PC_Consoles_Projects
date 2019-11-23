#pragma once
#include <thread>
#include <atomic>
#include <Utils/ConcurrentQueue.h>

class RendererThread
{
public:
	enum RenderCommandType { CLEAR, END_FRAME, PUT_PIXEL, WRITE_RAIN };

	struct RenderCommandPutPixelParams {
		int x, y;
	};

	struct RenderCommandParams { //TODO : UNION LOKO
		float radius;
		int* current;
		int* image;

		int color;
		RenderCommandPutPixelParams putPixelParam; 
	};

	struct RenderCommand {
		RenderCommandType type;
		RenderCommandParams params;
	};

private:
	std::thread* _thread;
	std::atomic<bool> _quitRequested;
	std::atomic<int> _pendingframes;
	ConcurrentQueue<RenderCommand> _concurrentQueue;

	void renderLoop();
	int renderPixel(int x, int y, int* current, int* image);
	bool isValid(int i, int j);
	int clamp(int value, int min, int max);

public:
	RendererThread();
	~RendererThread();

	void start(); //comienza la ejecucion de la hebra
	void stop(); //espera a que acabe (join) y delete thread
	void enqueueCommand(RenderCommand c); //llamado desde la logica. actualiza el numero de frames que quedan por pintar
	inline int getPendingFrames() { return _pendingframes; }; //al final del bucle de la logica se tiene que poner while(cuantosFramesMeQuedanPorPintar > numFrameBuffers);
	//para que espere si se adelanta la logica a la hebra de render para que no se pisen frames ni se llene la cola con muchos comandos
	//y exploten
};

