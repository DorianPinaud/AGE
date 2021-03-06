#include <Context/IRenderContext.hh>
#include <Core/Inputs/Input.hh>
#include <tmq/message.hpp>
#include <Configuration.hpp>

#ifdef AGE_ENABLE_IMGUI
#include <Core/Age_Imgui.hpp>
#endif

namespace AGE
{
	IRenderContext::IRenderContext()
		: _screenSize(glm::uvec2(10, 10))
		, _windowName("<3 ~AGE~ <3")
	{ }

	IRenderContext::~IRenderContext()
	{
	}

	bool IRenderContext::init(unsigned int swidth, unsigned int sheight, bool fullstreen, std::string && name)
	{
		_windowName = name;
		_screenSize = glm::uvec2(swidth, sheight);
		_fullscreen = fullstreen;
		return _init();
	}

	AgeKeys IRenderContext::findAgeMappedKey(int contextKey) const
	{
		auto it = _toAgeMappedKey.find(contextKey);

		if (it == _toAgeMappedKey.end())
			return (AgeKeys::AGE_KEY_UNKNOWN);
		return (it->second);
	}

	AgeKeys IRenderContext::findAgePhysicalKey(int contextKey) const
	{
		auto it = _toAgePhysicalKey.find(contextKey);

		if (it == _toAgePhysicalKey.end())
			return (AgeKeys::AGE_KEY_UNKNOWN);
		return (it->second);
	}

	AgeWindowInputs IRenderContext::findAgeWindowInput(int contextInput) const
	{
		auto it = _toAgeWindowInput.find(contextInput);

		if (it == _toAgeWindowInput.end())
			return (AgeWindowInputs::AGE_WINDOW_UNKNOWN);
		return (it->second);
	}

	AgeMouseButtons IRenderContext::findAgeMouseButton(int contextInput) const
	{
		auto it = _toAgeMouseButton.find(contextInput);

		if (it == _toAgeMouseButton.end())
			return (AgeMouseButtons::AGE_MOUSE_UNKNOWN);
		return (it->second);
	}

	AgeJoystickAxis IRenderContext::findAgeJoystickAxis(int contextInput) const
	{
		auto it = _toAgeJoystickAxis.find(contextInput);

		if (it == _toAgeJoystickAxis.end())
			return (AgeJoystickAxis::AGE_JOYSTICK_AXIS_UNKNOWN);
		return (it->second);
	}

	AgeJoystickButtons IRenderContext::findAgeJoystickButton(int contextInput) const
	{
		auto it = _toAgeJoystickButtons.find(contextInput);

		if (it == _toAgeJoystickButtons.end())
			return (AgeJoystickButtons::AGE_JOYSTICK_BUTTON_UNKNOWN);
		return (it->second);
	}

	AgeJoystickHatDirections IRenderContext::findAgeJoystickHatDirection(int contextInput) const
	{
		auto it = _toAgeJoystickHatDirections.find(contextInput);

		if (it == _toAgeJoystickHatDirections.end())
			return (AgeJoystickHatDirections::AGE_JOYSTICK_HAT_CENTERED);
		return (it->second);
	}
}