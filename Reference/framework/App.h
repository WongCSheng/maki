#ifndef APP_H
#define APP_H


class StopWatch;
class Window;
class SceneBase;
class App
{
public:
	static inline App& Instance()
	{
		if (instance != 0)
		{
			return *instance;
		}
		instance = new App();
		return *instance;
	}

	void Start();
	void Run();
	void Exit();
	double DeltaTime(void);
	int WindowWidth(void);
	int WindowHeight(void);

private:
	App();
	~App();

	static App* instance;
	Window* window;
	SceneBase *scene;
	float deltaTime;
	float FPS;
	unsigned int frameTime;
	static bool second;
	StopWatch* timer;
	bool startedTimer;

	int frameRate;

	void GlewSetup();
	void GlfwSetup();
	void CalculateFPS(void);
	void StartTimer(void);
	void TimerShldWait(long long time);
};

#endif