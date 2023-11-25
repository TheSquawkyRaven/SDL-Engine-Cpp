#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Input.h"

#include "Structs/Vector2.h"
#include "Structs/Vector2i.h"
#include "Structs/Rect2.h"
#include "Structs/Viewport.h"
#include "Structs/Color.h"

#include <string>
#include <functional>
#include <memory>
#include <stack>


namespace Perch
{

	class Script;

	// Config definition
	class EngineConfig
	{

	public:

		std::string WindowName = "";
		Vector2i WindowSize = Vector2i(640, 480);

		Color ClearColor = Color();

	};

	// Engine is a friend of Branch
	class Branch;

	// For bool return functions, true represents success
	class Engine
	{

		// # Variables + Getters/Setters

	private:

		std::shared_ptr<EngineConfig> Config;
		Rect2 MainWindowRect = Rect2();

		bool HasError = false;

		// SDL Window for rendering into
		SDL_Window* MainWindow = NULL;

		// SDL Renderer for hardware rendering
		SDL_Renderer* MainWindowRenderer = NULL;

		// Root is not delete when deconstructing because the destroy function will delete itself!
		Branch* Root = NULL;

		std::function<void(Engine* Engine, Branch* Root)> OnRootCreate = NULL;

		std::shared_ptr<Viewport> RootViewport = std::shared_ptr<Viewport>(new Viewport(MainWindowRect));
		std::stack<std::shared_ptr<Viewport>> ViewportStack;

		Uint32 LastUpdateTicks = 0;

		std::unique_ptr<Input> InputRef = std::unique_ptr<Input>(new Input);

	public:

		PERCHENGINECPP_API inline Rect2 GetMainWindowRect() const { return MainWindowRect; }
		PERCHENGINECPP_API inline SDL_Renderer* GetMainWindowRenderer() { return MainWindowRenderer; }
		PERCHENGINECPP_API inline Input* GetInput() const { return InputRef.get(); }

	public:

		float DeltaTime = 0.0f;
		float TotalTime = 0.0f;

		// ###


		// # Functions

	private:

		// Init - Runs in a constructor level
		bool InitMainWindow();

		// Create - 
		void CreateTree();
		void RunTree();

		// Update - Runs every frame
		void Update(SDL_Event* e, bool* quit);
		void StartUpdateLoop();

		void UpdateTime();

		// Returns true if has error
		bool CheckError() const;

	public:

		PERCHENGINECPP_API Engine(std::shared_ptr<EngineConfig> config);
		PERCHENGINECPP_API void UpdateConfig();

		PERCHENGINECPP_API inline void SetOnRootCreate(std::function<void(Engine* Engine, Branch* Root)> onRootCreate) { this->OnRootCreate = onRootCreate; };

		// Simulate viewport use, called in update when it is not drawing for children to use viewport data
		PERCHENGINECPP_API void SimulateUseViewport(std::shared_ptr<Viewport> viewport);
		PERCHENGINECPP_API void SimulateUnuseViewport(std::shared_ptr<Viewport> viewport);

		// Called in Draw and DrawOut to set the current viewport
		PERCHENGINECPP_API void UseViewport(SDL_Renderer* renderer, std::shared_ptr<Viewport> viewport);
		PERCHENGINECPP_API void UnuseViewport(SDL_Renderer* renderer, std::shared_ptr<Viewport> viewport);

		PERCHENGINECPP_API std::shared_ptr<Viewport> GetCurrentViewport();
		PERCHENGINECPP_API void ClearViewportStack();

		template<typename BranchT>
		PERCHENGINECPP_API inline std::shared_ptr<BranchT> CreateBranch()
		{
			static_assert(std::is_base_of<Branch, BranchT>::value, "CreateBranch template must be derived from Branch.");
			BranchT* branch = new BranchT();
			branch->_Init(this);
			return std::shared_ptr<BranchT>(branch);
		}

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		PERCHENGINECPP_API void Start();
		PERCHENGINECPP_API void Quit();

		// ###
	};
}
