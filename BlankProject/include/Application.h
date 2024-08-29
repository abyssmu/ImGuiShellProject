#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _APPLICATION_
#define _APPLICATION_

#include <memory>
#include <string>

//External forward declarations

//Internal declarations
namespace App
{
	//External forward declarations

	//Internal declarations
	class Application
	{
	public:
		//Deleted constructors
		Application(const Application& other) = delete;
		Application& operator=(const Application& other) = delete;
		Application(const Application&& other) = delete;
		Application& operator=(const Application&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		Application();
		~Application();

		//Member methods
		bool Init(const std::string& name, const int& width, const int& height);
		void Run(bool demo);

		//PIMPL idiom
	private:
		struct ApplicationImpl;
		std::unique_ptr<ApplicationImpl> _impl;
	};
}

#endif