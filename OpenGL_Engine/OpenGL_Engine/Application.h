#pragma once
struct GLFWwindow;
class Application
{
public:
	Application();
	virtual ~Application();

	void run(int a_screenWidth, int a_screenHeight, const char* a_windowName);

	virtual int startup() = 0;
	virtual void update(float a_deltaTime) = 0;
	virtual void draw() = 0;
	virtual void shutdown() = 0;

	void clearScreen();
	// sets the colour that the sceen is cleared to
	void setBackgroundColour(float a_r, float a_g, float a_b, float a_a = 1.0f);
	// show or hide the OS cursor
	void setShowCursor(bool a_visible);
	// enable or disable v-sync
	void setVSync(bool a_enabled);
	// returns the frames-per-second that the loop is running at
	unsigned int getFPS() const { return m_fps; }
	// returns the width / height of the game window
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;
	// returns time since application started
	float getTime() const;
	float getDeltaTime() const;
	GLFWwindow* getWindowPointer() const { return m_window; }
	bool hasWindowSizeChanged();

protected:
	virtual int createWindow(int a_screenWidth, int a_screenHeight, const char* a_windowName);
	void destroyWindow();

private:
	GLFWwindow* m_window;

	float windowWidth;
	float windowHeight;

	unsigned int m_fps = 0;
	double deltaTime = 0;
};