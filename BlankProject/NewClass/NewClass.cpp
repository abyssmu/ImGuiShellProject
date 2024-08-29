#include "NewClass.h"

namespace NewNamespace
{
	struct NewClass::NewClassImpl
	{
		//Deleted constructors
		NewClassImpl() = delete;
		NewClassImpl(const NewClassImpl& other) = delete;
		NewClassImpl& operator=(const NewClassImpl& other) = delete;
		NewClassImpl(const NewClassImpl&& other) = delete;
		NewClassImpl& operator=(const NewClassImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		~NewClassImpl() = default;

		//Member methods

		//Member variables
	};

	NewClass::NewClass() = default;
	NewClass::~NewClass() = default;
}