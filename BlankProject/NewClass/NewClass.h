#pragma once

#ifndef _NEWCLASS_
#define _NEWCLASS_

//External forward declarations

//Internal declarations
namespace NewNamespace
{
	//External forward declarations

	//Internal declarations
	class NewClass
	{
	public:
		//Deleted constructors
		NewClass(const NewClass& other) = delete;
		NewClass& operator=(const NewClass& other) = delete;
		NewClass(const NewClass&& other) = delete;
		NewClass& operator=(const NewClass&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		NewClass();
		~NewClass();

		//Member methods

		//PIMPL idiom
	private:
		struct NewClassImpl;
		std::unique_ptr<NewClassImpl> _impl;
	};
}

#endif