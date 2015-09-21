#include <context/SDL/SdlContext.hh>
#include <SDL/SDL.h>

namespace AGE
{
	std::map<int, AgeKeys> IRenderContext::_toAgeMappedKey =
	{
		{ SDLK_UNKNOWN, AgeKeys::AGE_KEY_UNKNOWN },
		{ SDLK_RETURN, AgeKeys::AGE_RETURN },
		{ SDLK_ESCAPE, AgeKeys::AGE_ESCAPE },
		{ SDLK_BACKSPACE, AgeKeys::AGE_BACKSPACE },
		{ SDLK_TAB, AgeKeys::AGE_TAB },
		{ SDLK_SPACE, AgeKeys::AGE_SPACE },
		{ SDLK_EXCLAIM, AgeKeys::AGE_EXCLAIM },
		{ SDLK_QUOTEDBL, AgeKeys::AGE_QUOTEDBL },
		{ SDLK_HASH, AgeKeys::AGE_HASH },
		{ SDLK_PERCENT, AgeKeys::AGE_PERCENT },
		{ SDLK_DOLLAR, AgeKeys::AGE_DOLLAR },
		{ SDLK_AMPERSAND, AgeKeys::AGE_AMPERSAND },
		{ SDLK_QUOTE, AgeKeys::AGE_QUOTE },
		{ SDLK_LEFTPAREN, AgeKeys::AGE_LEFTPAREN },
		{ SDLK_RIGHTPAREN, AgeKeys::AGE_RIGHTPAREN },
		{ SDLK_ASTERISK, AgeKeys::AGE_ASTERISK },
		{ SDLK_PLUS, AgeKeys::AGE_PLUS },
		{ SDLK_COMMA, AgeKeys::AGE_COMMA },
		{ SDLK_MINUS, AgeKeys::AGE_MINUS },
		{ SDLK_PERIOD, AgeKeys::AGE_PERIOD },
		{ SDLK_SLASH, AgeKeys::AGE_SLASH },
		{ SDLK_0, AgeKeys::AGE_0 },
		{ SDLK_1, AgeKeys::AGE_1 },
		{ SDLK_2, AgeKeys::AGE_2 },
		{ SDLK_3, AgeKeys::AGE_3 },
		{ SDLK_4, AgeKeys::AGE_4 },
		{ SDLK_5, AgeKeys::AGE_5 },
		{ SDLK_6, AgeKeys::AGE_6 },
		{ SDLK_7, AgeKeys::AGE_7 },
		{ SDLK_8, AgeKeys::AGE_8 },
		{ SDLK_9, AgeKeys::AGE_9 },
		{ SDLK_COLON, AgeKeys::AGE_COLON },
		{ SDLK_SEMICOLON, AgeKeys::AGE_SEMICOLON },
		{ SDLK_LESS, AgeKeys::AGE_LESS },
		{ SDLK_EQUALS, AgeKeys::AGE_EQUALS },
		{ SDLK_GREATER, AgeKeys::AGE_GREATER },
		{ SDLK_QUESTION, AgeKeys::AGE_QUESTION },
		{ SDLK_AT, AgeKeys::AGE_AT },
		{ SDLK_LEFTBRACKET, AgeKeys::AGE_LEFTBRACKET },
		{ SDLK_BACKSLASH, AgeKeys::AGE_BACKSLASH },
		{ SDLK_RIGHTBRACKET, AgeKeys::AGE_RIGHTBRACKET },
		{ SDLK_CARET, AgeKeys::AGE_CARET },
		{ SDLK_UNDERSCORE, AgeKeys::AGE_UNDERSCORE },
		{ SDLK_BACKQUOTE, AgeKeys::AGE_BACKQUOTE },
		{ SDLK_a, AgeKeys::AGE_a },
		{ SDLK_b, AgeKeys::AGE_b },
		{ SDLK_c, AgeKeys::AGE_c },
		{ SDLK_d, AgeKeys::AGE_d },
		{ SDLK_e, AgeKeys::AGE_e },
		{ SDLK_f, AgeKeys::AGE_f },
		{ SDLK_g, AgeKeys::AGE_g },
		{ SDLK_h, AgeKeys::AGE_h },
		{ SDLK_i, AgeKeys::AGE_i },
		{ SDLK_j, AgeKeys::AGE_j },
		{ SDLK_k, AgeKeys::AGE_k },
		{ SDLK_l, AgeKeys::AGE_l },
		{ SDLK_m, AgeKeys::AGE_m },
		{ SDLK_n, AgeKeys::AGE_n },
		{ SDLK_o, AgeKeys::AGE_o },
		{ SDLK_p, AgeKeys::AGE_p },
		{ SDLK_q, AgeKeys::AGE_q },
		{ SDLK_r, AgeKeys::AGE_r },
		{ SDLK_s, AgeKeys::AGE_s },
		{ SDLK_t, AgeKeys::AGE_t },
		{ SDLK_u, AgeKeys::AGE_u },
		{ SDLK_v, AgeKeys::AGE_v },
		{ SDLK_w, AgeKeys::AGE_w },
		{ SDLK_x, AgeKeys::AGE_x },
		{ SDLK_y, AgeKeys::AGE_y },
		{ SDLK_z, AgeKeys::AGE_z },
		{ SDLK_KP_DIVIDE, AgeKeys::AGE_KEYPAD_DIVIDE },
		{ SDLK_KP_MULTIPLY, AgeKeys::AGE_KEYPAD_MULTIPLY },
		{ SDLK_KP_MINUS, AgeKeys::AGE_KEYPAD_MINUS },
		{ SDLK_KP_PLUS, AgeKeys::AGE_KEYPAD_PLUS },
		{ SDLK_KP_ENTER, AgeKeys::AGE_KEYPAD_ENTER },
		{ SDLK_KP_1, AgeKeys::AGE_KEYPAD_1 },
		{ SDLK_KP_2, AgeKeys::AGE_KEYPAD_2 },
		{ SDLK_KP_3, AgeKeys::AGE_KEYPAD_3 },
		{ SDLK_KP_4, AgeKeys::AGE_KEYPAD_4 },
		{ SDLK_KP_5, AgeKeys::AGE_KEYPAD_5 },
		{ SDLK_KP_6, AgeKeys::AGE_KEYPAD_6 },
		{ SDLK_KP_7, AgeKeys::AGE_KEYPAD_7 },
		{ SDLK_KP_8, AgeKeys::AGE_KEYPAD_8 },
		{ SDLK_KP_9, AgeKeys::AGE_KEYPAD_9 },
		{ SDLK_KP_0, AgeKeys::AGE_KEYPAD_0 },
		{ SDLK_KP_PERIOD, AgeKeys::AGE_KEYPAD_PERIOD },
		{ SDLK_KP_EQUALS, AgeKeys::AGE_KEYPAD_EQUALS },
		{ SDLK_CAPSLOCK, AgeKeys::AGE_CAPSLOCK },
		{ SDLK_F1, AgeKeys::AGE_F1 },
		{ SDLK_F2, AgeKeys::AGE_F2 },
		{ SDLK_F3, AgeKeys::AGE_F3 },
		{ SDLK_F4, AgeKeys::AGE_F4 },
		{ SDLK_F5, AgeKeys::AGE_F5 },
		{ SDLK_F6, AgeKeys::AGE_F6 },
		{ SDLK_F7, AgeKeys::AGE_F7 },
		{ SDLK_F8, AgeKeys::AGE_F8 },
		{ SDLK_F9, AgeKeys::AGE_F9 },
		{ SDLK_F10, AgeKeys::AGE_F10 },
		{ SDLK_F11, AgeKeys::AGE_F11 },
		{ SDLK_F12, AgeKeys::AGE_F12 },
		{ SDLK_PRINTSCREEN, AgeKeys::AGE_PRINTSCREEN },
		{ SDLK_SCROLLLOCK, AgeKeys::AGE_SCROLLLOCK },
		{ SDLK_PAUSE, AgeKeys::AGE_PAUSE },
		{ SDLK_INSERT, AgeKeys::AGE_INSERT },
		{ SDLK_HOME, AgeKeys::AGE_HOME },
		{ SDLK_PAGEUP, AgeKeys::AGE_PAGEUP },
		{ SDLK_DELETE, AgeKeys::AGE_DELETE },
		{ SDLK_END, AgeKeys::AGE_END },
		{ SDLK_PAGEDOWN, AgeKeys::AGE_PAGEDOWN },
		{ SDLK_RIGHT, AgeKeys::AGE_RIGHT },
		{ SDLK_LEFT, AgeKeys::AGE_LEFT },
		{ SDLK_DOWN, AgeKeys::AGE_DOWN },
		{ SDLK_UP, AgeKeys::AGE_UP },
		{ SDLK_NUMLOCKCLEAR, AgeKeys::AGE_NUMLOCKCLEAR },
		{ SDLK_APPLICATION, AgeKeys::AGE_APPLICATION },
		{ SDLK_POWER, AgeKeys::AGE_POWER },
		{ SDLK_F13, AgeKeys::AGE_F13 },
		{ SDLK_F14, AgeKeys::AGE_F14 },
		{ SDLK_F15, AgeKeys::AGE_F15 },
		{ SDLK_F16, AgeKeys::AGE_F16 },
		{ SDLK_F17, AgeKeys::AGE_F17 },
		{ SDLK_F18, AgeKeys::AGE_F18 },
		{ SDLK_F19, AgeKeys::AGE_F19 },
		{ SDLK_F20, AgeKeys::AGE_F20 },
		{ SDLK_F21, AgeKeys::AGE_F21 },
		{ SDLK_F22, AgeKeys::AGE_F22 },
		{ SDLK_F23, AgeKeys::AGE_F23 },
		{ SDLK_F24, AgeKeys::AGE_F24 },
		{ SDLK_EXECUTE, AgeKeys::AGE_EXECUTE },
		{ SDLK_HELP, AgeKeys::AGE_HELP },
		{ SDLK_MENU, AgeKeys::AGE_MENU },
		{ SDLK_SELECT, AgeKeys::AGE_SELECT },
		{ SDLK_STOP, AgeKeys::AGE_STOP },
		{ SDLK_AGAIN, AgeKeys::AGE_AGAIN },
		{ SDLK_UNDO, AgeKeys::AGE_UNDO },
		{ SDLK_CUT, AgeKeys::AGE_CUT },
		{ SDLK_COPY, AgeKeys::AGE_COPY },
		{ SDLK_PASTE, AgeKeys::AGE_PASTE },
		{ SDLK_FIND, AgeKeys::AGE_FIND },
		{ SDLK_MUTE, AgeKeys::AGE_MUTE },
		{ SDLK_VOLUMEUP, AgeKeys::AGE_VOLUMEUP },
		{ SDLK_VOLUMEDOWN, AgeKeys::AGE_VOLUMEDOWN },
		{ SDLK_ALTERASE, AgeKeys::AGE_ALTERASE },
		{ SDLK_SYSREQ, AgeKeys::AGE_SYSREQ },
		{ SDLK_CANCEL, AgeKeys::AGE_CANCEL },
		{ SDLK_CLEAR, AgeKeys::AGE_CLEAR },
		{ SDLK_PRIOR, AgeKeys::AGE_PRIOR },
		{ SDLK_RETURN2, AgeKeys::AGE_RETURN2 },
		{ SDLK_SEPARATOR, AgeKeys::AGE_SEPARATOR },
		{ SDLK_OUT, AgeKeys::AGE_OUT },
		{ SDLK_OPER, AgeKeys::AGE_OPER },
		{ SDLK_CLEARAGAIN, AgeKeys::AGE_CLEARAGAIN },
		{ SDLK_CRSEL, AgeKeys::AGE_CRSEL },
		{ SDLK_EXSEL, AgeKeys::AGE_EXSEL },
		{ SDLK_LCTRL, AgeKeys::AGE_LCTRL },
		{ SDLK_LSHIFT, AgeKeys::AGE_LSHIFT },
		{ SDLK_LALT, AgeKeys::AGE_LALT },
		{ SDLK_LGUI, AgeKeys::AGE_LGUI },
		{ SDLK_RCTRL, AgeKeys::AGE_RCTRL },
		{ SDLK_RSHIFT, AgeKeys::AGE_RSHIFT },
		{ SDLK_RALT, AgeKeys::AGE_RALT },
		{ SDLK_RGUI, AgeKeys::AGE_RGUI },
		{ SDLK_MODE, AgeKeys::AGE_MODE },
		{ SDLK_AUDIONEXT, AgeKeys::AGE_AUDIONEXT },
		{ SDLK_AUDIOPREV, AgeKeys::AGE_AUDIOPREV },
		{ SDLK_AUDIOSTOP, AgeKeys::AGE_AUDIOSTOP },
		{ SDLK_AUDIOPLAY, AgeKeys::AGE_AUDIOPLAY },
		{ SDLK_AUDIOMUTE, AgeKeys::AGE_AUDIOMUTE },
		{ SDLK_MEDIASELECT, AgeKeys::AGE_MEDIASELECT },
		{ SDLK_WWW, AgeKeys::AGE_WWW },
		{ SDLK_MAIL, AgeKeys::AGE_MAIL },
		{ SDLK_CALCULATOR, AgeKeys::AGE_CALCULATOR },
		{ SDLK_COMPUTER, AgeKeys::AGE_COMPUTER },
		{ SDLK_AC_SEARCH, AgeKeys::AGE_AC_SEARCH },
		{ SDLK_AC_HOME, AgeKeys::AGE_AC_HOME },
		{ SDLK_AC_BACK, AgeKeys::AGE_AC_BACK },
		{ SDLK_AC_FORWARD, AgeKeys::AGE_AC_FORWARD },
		{ SDLK_AC_STOP, AgeKeys::AGE_AC_STOP },
		{ SDLK_AC_REFRESH, AgeKeys::AGE_AC_REFRESH },
		{ SDLK_AC_BOOKMARKS, AgeKeys::AGE_AC_BOOKMARKS },
		{ SDLK_BRIGHTNESSDOWN, AgeKeys::AGE_BRIGHTNESSDOWN },
		{ SDLK_BRIGHTNESSUP, AgeKeys::AGE_BRIGHTNESSUP },
		{ SDLK_DISPLAYSWITCH, AgeKeys::AGE_DISPLAYSWITCH },
		{ SDLK_KBDILLUMTOGGLE, AgeKeys::AGE_KBDILLUMTOGGLE },
		{ SDLK_KBDILLUMDOWN, AgeKeys::AGE_KBDILLUMDOWN },
		{ SDLK_KBDILLUMUP, AgeKeys::AGE_KBDILLUMUP },
		{ SDLK_EJECT, AgeKeys::AGE_EJECT },
		{ SDLK_SLEEP, AgeKeys::AGE_SLEEP }
	};

	std::map<int, AgeKeys> IRenderContext::_toAgePhysicalKey =
	{
		{ SDL_SCANCODE_UNKNOWN, AgeKeys::AGE_KEY_UNKNOWN },
		{ SDL_SCANCODE_RETURN, AgeKeys::AGE_RETURN },
		{ SDL_SCANCODE_ESCAPE, AgeKeys::AGE_ESCAPE },
		{ SDL_SCANCODE_BACKSPACE, AgeKeys::AGE_BACKSPACE },
		{ SDL_SCANCODE_TAB, AgeKeys::AGE_TAB },
		{ SDL_SCANCODE_SPACE, AgeKeys::AGE_SPACE },
		{ SDL_SCANCODE_APOSTROPHE, AgeKeys::AGE_QUOTE },
		{ SDL_SCANCODE_COMMA, AgeKeys::AGE_COMMA },
		{ SDL_SCANCODE_MINUS, AgeKeys::AGE_MINUS },
		{ SDL_SCANCODE_PERIOD, AgeKeys::AGE_PERIOD },
		{ SDL_SCANCODE_SLASH, AgeKeys::AGE_SLASH },
		{ SDL_SCANCODE_0, AgeKeys::AGE_0 },
		{ SDL_SCANCODE_1, AgeKeys::AGE_1 },
		{ SDL_SCANCODE_2, AgeKeys::AGE_2 },
		{ SDL_SCANCODE_3, AgeKeys::AGE_3 },
		{ SDL_SCANCODE_4, AgeKeys::AGE_4 },
		{ SDL_SCANCODE_5, AgeKeys::AGE_5 },
		{ SDL_SCANCODE_6, AgeKeys::AGE_6 },
		{ SDL_SCANCODE_7, AgeKeys::AGE_7 },
		{ SDL_SCANCODE_8, AgeKeys::AGE_8 },
		{ SDL_SCANCODE_9, AgeKeys::AGE_9 },
		{ SDL_SCANCODE_SEMICOLON, AgeKeys::AGE_SEMICOLON },
		{ SDL_SCANCODE_EQUALS, AgeKeys::AGE_EQUALS },
		{ SDL_SCANCODE_LEFTBRACKET, AgeKeys::AGE_LEFTBRACKET },
		{ SDL_SCANCODE_BACKSLASH, AgeKeys::AGE_BACKSLASH },
		{ SDL_SCANCODE_RIGHTBRACKET, AgeKeys::AGE_RIGHTBRACKET },
		{ SDL_SCANCODE_GRAVE, AgeKeys::AGE_BACKQUOTE },
		{ SDL_SCANCODE_A, AgeKeys::AGE_a },
		{ SDL_SCANCODE_B, AgeKeys::AGE_b },
		{ SDL_SCANCODE_C, AgeKeys::AGE_c },
		{ SDL_SCANCODE_D, AgeKeys::AGE_d },
		{ SDL_SCANCODE_E, AgeKeys::AGE_e },
		{ SDL_SCANCODE_F, AgeKeys::AGE_f },
		{ SDL_SCANCODE_G, AgeKeys::AGE_g },
		{ SDL_SCANCODE_H, AgeKeys::AGE_h },
		{ SDL_SCANCODE_I, AgeKeys::AGE_i },
		{ SDL_SCANCODE_J, AgeKeys::AGE_j },
		{ SDL_SCANCODE_K, AgeKeys::AGE_k },
		{ SDL_SCANCODE_L, AgeKeys::AGE_l },
		{ SDL_SCANCODE_M, AgeKeys::AGE_m },
		{ SDL_SCANCODE_N, AgeKeys::AGE_n },
		{ SDL_SCANCODE_O, AgeKeys::AGE_o },
		{ SDL_SCANCODE_P, AgeKeys::AGE_p },
		{ SDL_SCANCODE_Q, AgeKeys::AGE_q },
		{ SDL_SCANCODE_R, AgeKeys::AGE_r },
		{ SDL_SCANCODE_S, AgeKeys::AGE_s },
		{ SDL_SCANCODE_T, AgeKeys::AGE_t },
		{ SDL_SCANCODE_U, AgeKeys::AGE_u },
		{ SDL_SCANCODE_V, AgeKeys::AGE_v },
		{ SDL_SCANCODE_W, AgeKeys::AGE_w },
		{ SDL_SCANCODE_X, AgeKeys::AGE_x },
		{ SDL_SCANCODE_Y, AgeKeys::AGE_y },
		{ SDL_SCANCODE_Z, AgeKeys::AGE_z },
		{ SDL_SCANCODE_KP_DIVIDE, AgeKeys::AGE_KEYPAD_DIVIDE },
		{ SDL_SCANCODE_KP_MULTIPLY, AgeKeys::AGE_KEYPAD_MULTIPLY },
		{ SDL_SCANCODE_KP_MINUS, AgeKeys::AGE_KEYPAD_MINUS },
		{ SDL_SCANCODE_KP_PLUS, AgeKeys::AGE_KEYPAD_PLUS },
		{ SDL_SCANCODE_KP_ENTER, AgeKeys::AGE_KEYPAD_ENTER },
		{ SDL_SCANCODE_KP_1, AgeKeys::AGE_KEYPAD_1 },
		{ SDL_SCANCODE_KP_2, AgeKeys::AGE_KEYPAD_2 },
		{ SDL_SCANCODE_KP_3, AgeKeys::AGE_KEYPAD_3 },
		{ SDL_SCANCODE_KP_4, AgeKeys::AGE_KEYPAD_4 },
		{ SDL_SCANCODE_KP_5, AgeKeys::AGE_KEYPAD_5 },
		{ SDL_SCANCODE_KP_6, AgeKeys::AGE_KEYPAD_6 },
		{ SDL_SCANCODE_KP_7, AgeKeys::AGE_KEYPAD_7 },
		{ SDL_SCANCODE_KP_8, AgeKeys::AGE_KEYPAD_8 },
		{ SDL_SCANCODE_KP_9, AgeKeys::AGE_KEYPAD_9 },
		{ SDL_SCANCODE_KP_0, AgeKeys::AGE_KEYPAD_0 },
		{ SDL_SCANCODE_KP_PERIOD, AgeKeys::AGE_KEYPAD_PERIOD },
		{ SDL_SCANCODE_KP_EQUALS, AgeKeys::AGE_KEYPAD_EQUALS },
		{ SDL_SCANCODE_CAPSLOCK, AgeKeys::AGE_CAPSLOCK },
		{ SDL_SCANCODE_F1, AgeKeys::AGE_F1 },
		{ SDL_SCANCODE_F2, AgeKeys::AGE_F2 },
		{ SDL_SCANCODE_F3, AgeKeys::AGE_F3 },
		{ SDL_SCANCODE_F4, AgeKeys::AGE_F4 },
		{ SDL_SCANCODE_F5, AgeKeys::AGE_F5 },
		{ SDL_SCANCODE_F6, AgeKeys::AGE_F6 },
		{ SDL_SCANCODE_F7, AgeKeys::AGE_F7 },
		{ SDL_SCANCODE_F8, AgeKeys::AGE_F8 },
		{ SDL_SCANCODE_F9, AgeKeys::AGE_F9 },
		{ SDL_SCANCODE_F10, AgeKeys::AGE_F10 },
		{ SDL_SCANCODE_F11, AgeKeys::AGE_F11 },
		{ SDL_SCANCODE_F12, AgeKeys::AGE_F12 },
		{ SDL_SCANCODE_PRINTSCREEN, AgeKeys::AGE_PRINTSCREEN },
		{ SDL_SCANCODE_SCROLLLOCK, AgeKeys::AGE_SCROLLLOCK },
		{ SDL_SCANCODE_PAUSE, AgeKeys::AGE_PAUSE },
		{ SDL_SCANCODE_INSERT, AgeKeys::AGE_INSERT },
		{ SDL_SCANCODE_HOME, AgeKeys::AGE_HOME },
		{ SDL_SCANCODE_PAGEUP, AgeKeys::AGE_PAGEUP },
		{ SDL_SCANCODE_DELETE, AgeKeys::AGE_DELETE },
		{ SDL_SCANCODE_END, AgeKeys::AGE_END },
		{ SDL_SCANCODE_PAGEDOWN, AgeKeys::AGE_PAGEDOWN },
		{ SDL_SCANCODE_RIGHT, AgeKeys::AGE_RIGHT },
		{ SDL_SCANCODE_LEFT, AgeKeys::AGE_LEFT },
		{ SDL_SCANCODE_DOWN, AgeKeys::AGE_DOWN },
		{ SDL_SCANCODE_UP, AgeKeys::AGE_UP },
		{ SDL_SCANCODE_NUMLOCKCLEAR, AgeKeys::AGE_NUMLOCKCLEAR },
		{ SDL_SCANCODE_APPLICATION, AgeKeys::AGE_APPLICATION },
		{ SDL_SCANCODE_POWER, AgeKeys::AGE_POWER },
		{ SDL_SCANCODE_F13, AgeKeys::AGE_F13 },
		{ SDL_SCANCODE_F14, AgeKeys::AGE_F14 },
		{ SDL_SCANCODE_F15, AgeKeys::AGE_F15 },
		{ SDL_SCANCODE_F16, AgeKeys::AGE_F16 },
		{ SDL_SCANCODE_F17, AgeKeys::AGE_F17 },
		{ SDL_SCANCODE_F18, AgeKeys::AGE_F18 },
		{ SDL_SCANCODE_F19, AgeKeys::AGE_F19 },
		{ SDL_SCANCODE_F20, AgeKeys::AGE_F20 },
		{ SDL_SCANCODE_F21, AgeKeys::AGE_F21 },
		{ SDL_SCANCODE_F22, AgeKeys::AGE_F22 },
		{ SDL_SCANCODE_F23, AgeKeys::AGE_F23 },
		{ SDL_SCANCODE_F24, AgeKeys::AGE_F24 },
		{ SDL_SCANCODE_EXECUTE, AgeKeys::AGE_EXECUTE },
		{ SDL_SCANCODE_HELP, AgeKeys::AGE_HELP },
		{ SDL_SCANCODE_MENU, AgeKeys::AGE_MENU },
		{ SDL_SCANCODE_SELECT, AgeKeys::AGE_SELECT },
		{ SDL_SCANCODE_STOP, AgeKeys::AGE_STOP },
		{ SDL_SCANCODE_AGAIN, AgeKeys::AGE_AGAIN },
		{ SDL_SCANCODE_UNDO, AgeKeys::AGE_UNDO },
		{ SDL_SCANCODE_CUT, AgeKeys::AGE_CUT },
		{ SDL_SCANCODE_COPY, AgeKeys::AGE_COPY },
		{ SDL_SCANCODE_PASTE, AgeKeys::AGE_PASTE },
		{ SDL_SCANCODE_FIND, AgeKeys::AGE_FIND },
		{ SDL_SCANCODE_MUTE, AgeKeys::AGE_MUTE },
		{ SDL_SCANCODE_VOLUMEUP, AgeKeys::AGE_VOLUMEUP },
		{ SDL_SCANCODE_VOLUMEDOWN, AgeKeys::AGE_VOLUMEDOWN },
		{ SDL_SCANCODE_ALTERASE, AgeKeys::AGE_ALTERASE },
		{ SDL_SCANCODE_SYSREQ, AgeKeys::AGE_SYSREQ },
		{ SDL_SCANCODE_CANCEL, AgeKeys::AGE_CANCEL },
		{ SDL_SCANCODE_CLEAR, AgeKeys::AGE_CLEAR },
		{ SDL_SCANCODE_PRIOR, AgeKeys::AGE_PRIOR },
		{ SDL_SCANCODE_RETURN2, AgeKeys::AGE_RETURN2 },
		{ SDL_SCANCODE_SEPARATOR, AgeKeys::AGE_SEPARATOR },
		{ SDL_SCANCODE_OUT, AgeKeys::AGE_OUT },
		{ SDL_SCANCODE_OPER, AgeKeys::AGE_OPER },
		{ SDL_SCANCODE_CLEARAGAIN, AgeKeys::AGE_CLEARAGAIN },
		{ SDL_SCANCODE_CRSEL, AgeKeys::AGE_CRSEL },
		{ SDL_SCANCODE_EXSEL, AgeKeys::AGE_EXSEL },
		{ SDL_SCANCODE_LCTRL, AgeKeys::AGE_LCTRL },
		{ SDL_SCANCODE_LSHIFT, AgeKeys::AGE_LSHIFT },
		{ SDL_SCANCODE_LALT, AgeKeys::AGE_LALT },
		{ SDL_SCANCODE_LGUI, AgeKeys::AGE_LGUI },
		{ SDL_SCANCODE_RCTRL, AgeKeys::AGE_RCTRL },
		{ SDL_SCANCODE_RSHIFT, AgeKeys::AGE_RSHIFT },
		{ SDL_SCANCODE_RALT, AgeKeys::AGE_RALT },
		{ SDL_SCANCODE_RGUI, AgeKeys::AGE_RGUI },
		{ SDL_SCANCODE_MODE, AgeKeys::AGE_MODE },
		{ SDL_SCANCODE_AUDIONEXT, AgeKeys::AGE_AUDIONEXT },
		{ SDL_SCANCODE_AUDIOPREV, AgeKeys::AGE_AUDIOPREV },
		{ SDL_SCANCODE_AUDIOSTOP, AgeKeys::AGE_AUDIOSTOP },
		{ SDL_SCANCODE_AUDIOPLAY, AgeKeys::AGE_AUDIOPLAY },
		{ SDL_SCANCODE_AUDIOMUTE, AgeKeys::AGE_AUDIOMUTE },
		{ SDL_SCANCODE_MEDIASELECT, AgeKeys::AGE_MEDIASELECT },
		{ SDL_SCANCODE_WWW, AgeKeys::AGE_WWW },
		{ SDL_SCANCODE_MAIL, AgeKeys::AGE_MAIL },
		{ SDL_SCANCODE_CALCULATOR, AgeKeys::AGE_CALCULATOR },
		{ SDL_SCANCODE_COMPUTER, AgeKeys::AGE_COMPUTER },
		{ SDL_SCANCODE_AC_SEARCH, AgeKeys::AGE_AC_SEARCH },
		{ SDL_SCANCODE_AC_HOME, AgeKeys::AGE_AC_HOME },
		{ SDL_SCANCODE_AC_BACK, AgeKeys::AGE_AC_BACK },
		{ SDL_SCANCODE_AC_FORWARD, AgeKeys::AGE_AC_FORWARD },
		{ SDL_SCANCODE_AC_STOP, AgeKeys::AGE_AC_STOP },
		{ SDL_SCANCODE_AC_REFRESH, AgeKeys::AGE_AC_REFRESH },
		{ SDL_SCANCODE_AC_BOOKMARKS, AgeKeys::AGE_AC_BOOKMARKS },
		{ SDL_SCANCODE_BRIGHTNESSDOWN, AgeKeys::AGE_BRIGHTNESSDOWN },
		{ SDL_SCANCODE_BRIGHTNESSUP, AgeKeys::AGE_BRIGHTNESSUP },
		{ SDL_SCANCODE_DISPLAYSWITCH, AgeKeys::AGE_DISPLAYSWITCH },
		{ SDL_SCANCODE_KBDILLUMTOGGLE, AgeKeys::AGE_KBDILLUMTOGGLE },
		{ SDL_SCANCODE_KBDILLUMDOWN, AgeKeys::AGE_KBDILLUMDOWN },
		{ SDL_SCANCODE_KBDILLUMUP, AgeKeys::AGE_KBDILLUMUP },
		{ SDL_SCANCODE_EJECT, AgeKeys::AGE_EJECT },
		{ SDL_SCANCODE_SLEEP, AgeKeys::AGE_SLEEP }
	};

	std::map<int, AgeWindowInputs> IRenderContext::_toAgeWindowInput =
	{
		{ SDL_WINDOWEVENT_SHOWN, AgeWindowInputs::AGE_WINDOW_SHOWN },
		{ SDL_WINDOWEVENT_HIDDEN, AgeWindowInputs::AGE_WINDOW_HIDDEN },
		{ SDL_WINDOWEVENT_EXPOSED, AgeWindowInputs::AGE_WINDOW_EXPOSED },
		{ SDL_WINDOWEVENT_MOVED, AgeWindowInputs::AGE_WINDOW_MOVED },
		{ SDL_WINDOWEVENT_RESIZED, AgeWindowInputs::AGE_WINDOW_RESIZED },
		{ SDL_WINDOWEVENT_MINIMIZED, AgeWindowInputs::AGE_WINDOW_MINIMIZED },
		{ SDL_WINDOWEVENT_MAXIMIZED, AgeWindowInputs::AGE_WINDOW_MAXIMIZED },
		{ SDL_WINDOWEVENT_RESTORED, AgeWindowInputs::AGE_WINDOW_RESTORED },
		{ SDL_WINDOWEVENT_ENTER, AgeWindowInputs::AGE_WINDOW_ENTER },
		{ SDL_WINDOWEVENT_LEAVE, AgeWindowInputs::AGE_WINDOW_LEAVE },
		{ SDL_WINDOWEVENT_FOCUS_GAINED, AgeWindowInputs::AGE_WINDOW_FOCUS_GAINED },
		{ SDL_WINDOWEVENT_FOCUS_LOST, AgeWindowInputs::AGE_WINDOW_FOCUS_LOST },
		{ SDL_WINDOWEVENT_CLOSE, AgeWindowInputs::AGE_WINDOW_CLOSE },
		{ SDL_QUIT, AgeWindowInputs::AGE_WINDOW_CLOSE }
	};

	std::map<int, AgeMouseButtons> IRenderContext::_toAgeMouseButton =
	{
		{ SDL_BUTTON_LEFT, AgeMouseButtons::AGE_MOUSE_LEFT },
		{ SDL_BUTTON_MIDDLE, AgeMouseButtons::AGE_MOUSE_MIDDLE },
		{ SDL_BUTTON_RIGHT, AgeMouseButtons::AGE_MOUSE_RIGHT },
	};

	std::map<int, AgeJoystickAxis> IRenderContext::_toAgeJoystickAxis =
	{
		{ SDL_CONTROLLER_AXIS_INVALID, AgeJoystickAxis::AGE_JOYSTICK_AXIS_UNKNOWN },
		{ SDL_CONTROLLER_AXIS_LEFTX, AgeJoystickAxis::AGE_JOYSTICK_AXIS_LEFTX },
		{ SDL_CONTROLLER_AXIS_LEFTY, AgeJoystickAxis::AGE_JOYSTICK_AXIS_LEFTY },
		{ SDL_CONTROLLER_AXIS_RIGHTX, AgeJoystickAxis::AGE_JOYSTICK_AXIS_RIGHTX },
		{ SDL_CONTROLLER_AXIS_RIGHTY, AgeJoystickAxis::AGE_JOYSTICK_AXIS_RIGHTY },
		{ SDL_CONTROLLER_AXIS_TRIGGERLEFT, AgeJoystickAxis::AGE_JOYSTICK_AXIS_TRIGGERLEFT },
		{ SDL_CONTROLLER_AXIS_TRIGGERRIGHT, AgeJoystickAxis::AGE_JOYSTICK_AXIS_TRIGGERRIGHT },
	};

	std::map<int, AgeJoystickButtons> IRenderContext::_toAgeJoystickButtons =
	{
		{ SDL_CONTROLLER_BUTTON_INVALID, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_UNKNOWN },
		{ SDL_CONTROLLER_BUTTON_A, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_A },
		{ SDL_CONTROLLER_BUTTON_B, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_B },
		{ SDL_CONTROLLER_BUTTON_X, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_X },
		{ SDL_CONTROLLER_BUTTON_Y, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_Y },
		{ SDL_CONTROLLER_BUTTON_BACK, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_BACK },
		{ SDL_CONTROLLER_BUTTON_GUIDE, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_GUIDE },
		{ SDL_CONTROLLER_BUTTON_START, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_START },
		{ SDL_CONTROLLER_BUTTON_LEFTSTICK, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_LEFTSTICK },
		{ SDL_CONTROLLER_BUTTON_RIGHTSTICK, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_RIGHTSTICK },
		{ SDL_CONTROLLER_BUTTON_LEFTSHOULDER, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_LEFTSHOULDER },
		{ SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_RIGHTSHOULDER },
		{ SDL_CONTROLLER_BUTTON_DPAD_UP, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_DPAD_UP },
		{ SDL_CONTROLLER_BUTTON_DPAD_DOWN, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_DPAD_DOWN },
		{ SDL_CONTROLLER_BUTTON_DPAD_LEFT, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_DPAD_LEFT },
		{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT, AgeJoystickButtons::AGE_JOYSTICK_BUTTON_DPAD_RIGHT },
	};

	std::map<int, AgeJoystickHatDirections> IRenderContext::_toAgeJoystickHatDirections =
	{
		{ SDL_HAT_CENTERED, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_CENTERED },
		{ SDL_HAT_UP, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_UP },
		{ SDL_HAT_RIGHT, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_RIGHT },
		{ SDL_HAT_DOWN, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_DOWN },
		{ SDL_HAT_LEFT, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_LEFT },
		{ SDL_HAT_LEFTUP, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_LEFT_UP },
		{ SDL_HAT_LEFTDOWN, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_LEFT_DOWN },
		{ SDL_HAT_RIGHTUP, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_RIGHT_UP },
		{ SDL_HAT_RIGHTDOWN, AgeJoystickHatDirections::AGE_JOYSTICK_HAT_RIGHT_DOWN },
	};
}
