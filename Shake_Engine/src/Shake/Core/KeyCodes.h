#pragma once
#include <cstdint>
#include <ostream>

namespace Shake
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HZ_KEY_SPACE           ::Shake::Key::Space
#define HZ_KEY_APOSTROPHE      ::Shake::Key::Apostrophe    /* ' */
#define HZ_KEY_COMMA           ::Shake::Key::Comma         /* , */
#define HZ_KEY_MINUS           ::Shake::Key::Minus         /* - */
#define HZ_KEY_PERIOD          ::Shake::Key::Period        /* . */
#define HZ_KEY_SLASH           ::Shake::Key::Slash         /* / */
#define HZ_KEY_0               ::Shake::Key::D0
#define HZ_KEY_1               ::Shake::Key::D1
#define HZ_KEY_2               ::Shake::Key::D2
#define HZ_KEY_3               ::Shake::Key::D3
#define HZ_KEY_4               ::Shake::Key::D4
#define HZ_KEY_5               ::Shake::Key::D5
#define HZ_KEY_6               ::Shake::Key::D6
#define HZ_KEY_7               ::Shake::Key::D7
#define HZ_KEY_8               ::Shake::Key::D8
#define HZ_KEY_9               ::Shake::Key::D9
#define HZ_KEY_SEMICOLON       ::Shake::Key::Semicolon     /* ; */
#define HZ_KEY_EQUAL           ::Shake::Key::Equal         /* = */
#define HZ_KEY_A               ::Shake::Key::A
#define HZ_KEY_B               ::Shake::Key::B
#define HZ_KEY_C               ::Shake::Key::C
#define HZ_KEY_D               ::Shake::Key::D
#define HZ_KEY_E               ::Shake::Key::E
#define HZ_KEY_F               ::Shake::Key::F
#define HZ_KEY_G               ::Shake::Key::G
#define HZ_KEY_H               ::Shake::Key::H
#define HZ_KEY_I               ::Shake::Key::I
#define HZ_KEY_J               ::Shake::Key::J
#define HZ_KEY_K               ::Shake::Key::K
#define HZ_KEY_L               ::Shake::Key::L
#define HZ_KEY_M               ::Shake::Key::M
#define HZ_KEY_N               ::Shake::Key::N
#define HZ_KEY_O               ::Shake::Key::O
#define HZ_KEY_P               ::Shake::Key::P
#define HZ_KEY_Q               ::Shake::Key::Q
#define HZ_KEY_R               ::Shake::Key::R
#define HZ_KEY_S               ::Shake::Key::S
#define HZ_KEY_T               ::Shake::Key::T
#define HZ_KEY_U               ::Shake::Key::U
#define HZ_KEY_V               ::Shake::Key::V
#define HZ_KEY_W               ::Shake::Key::W
#define HZ_KEY_X               ::Shake::Key::X
#define HZ_KEY_Y               ::Shake::Key::Y
#define HZ_KEY_Z               ::Shake::Key::Z
#define HZ_KEY_LEFT_BRACKET    ::Shake::Key::LeftBracket   /* [ */
#define HZ_KEY_BACKSLASH       ::Shake::Key::Backslash     /* \ */
#define HZ_KEY_RIGHT_BRACKET   ::Shake::Key::RightBracket  /* ] */
#define HZ_KEY_GRAVE_ACCENT    ::Shake::Key::GraveAccent   /* ` */
#define HZ_KEY_WORLD_1         ::Shake::Key::World1        /* non-US #1 */
#define HZ_KEY_WORLD_2         ::Shake::Key::World2        /* non-US #2 */

/* Function keys */
#define HZ_KEY_ESCAPE          ::Shake::Key::Escape
#define HZ_KEY_ENTER           ::Shake::Key::Enter
#define HZ_KEY_TAB             ::Shake::Key::Tab
#define HZ_KEY_BACKSPACE       ::Shake::Key::Backspace
#define HZ_KEY_INSERT          ::Shake::Key::Insert
#define HZ_KEY_DELETE          ::Shake::Key::Delete
#define HZ_KEY_RIGHT           ::Shake::Key::Right
#define HZ_KEY_LEFT            ::Shake::Key::Left
#define HZ_KEY_DOWN            ::Shake::Key::Down
#define HZ_KEY_UP              ::Shake::Key::Up
#define HZ_KEY_PAGE_UP         ::Shake::Key::PageUp
#define HZ_KEY_PAGE_DOWN       ::Shake::Key::PageDown
#define HZ_KEY_HOME            ::Shake::Key::Home
#define HZ_KEY_END             ::Shake::Key::End
#define HZ_KEY_CAPS_LOCK       ::Shake::Key::CapsLock
#define HZ_KEY_SCROLL_LOCK     ::Shake::Key::ScrollLock
#define HZ_KEY_NUM_LOCK        ::Shake::Key::NumLock
#define HZ_KEY_PRINT_SCREEN    ::Shake::Key::PrintScreen
#define HZ_KEY_PAUSE           ::Shake::Key::Pause
#define HZ_KEY_F1              ::Shake::Key::F1
#define HZ_KEY_F2              ::Shake::Key::F2
#define HZ_KEY_F3              ::Shake::Key::F3
#define HZ_KEY_F4              ::Shake::Key::F4
#define HZ_KEY_F5              ::Shake::Key::F5
#define HZ_KEY_F6              ::Shake::Key::F6
#define HZ_KEY_F7              ::Shake::Key::F7
#define HZ_KEY_F8              ::Shake::Key::F8
#define HZ_KEY_F9              ::Shake::Key::F9
#define HZ_KEY_F10             ::Shake::Key::F10
#define HZ_KEY_F11             ::Shake::Key::F11
#define HZ_KEY_F12             ::Shake::Key::F12
#define HZ_KEY_F13             ::Shake::Key::F13
#define HZ_KEY_F14             ::Shake::Key::F14
#define HZ_KEY_F15             ::Shake::Key::F15
#define HZ_KEY_F16             ::Shake::Key::F16
#define HZ_KEY_F17             ::Shake::Key::F17
#define HZ_KEY_F18             ::Shake::Key::F18
#define HZ_KEY_F19             ::Shake::Key::F19
#define HZ_KEY_F20             ::Shake::Key::F20
#define HZ_KEY_F21             ::Shake::Key::F21
#define HZ_KEY_F22             ::Shake::Key::F22
#define HZ_KEY_F23             ::Shake::Key::F23
#define HZ_KEY_F24             ::Shake::Key::F24
#define HZ_KEY_F25             ::Shake::Key::F25

/* Keypad */
#define HZ_KEY_KP_0            ::Shake::Key::KP0
#define HZ_KEY_KP_1            ::Shake::Key::KP1
#define HZ_KEY_KP_2            ::Shake::Key::KP2
#define HZ_KEY_KP_3            ::Shake::Key::KP3
#define HZ_KEY_KP_4            ::Shake::Key::KP4
#define HZ_KEY_KP_5            ::Shake::Key::KP5
#define HZ_KEY_KP_6            ::Shake::Key::KP6
#define HZ_KEY_KP_7            ::Shake::Key::KP7
#define HZ_KEY_KP_8            ::Shake::Key::KP8
#define HZ_KEY_KP_9            ::Shake::Key::KP9
#define HZ_KEY_KP_DECIMAL      ::Shake::Key::KPDecimal
#define HZ_KEY_KP_DIVIDE       ::Shake::Key::KPDivide
#define HZ_KEY_KP_MULTIPLY     ::Shake::Key::KPMultiply
#define HZ_KEY_KP_SUBTRACT     ::Shake::Key::KPSubtract
#define HZ_KEY_KP_ADD          ::Shake::Key::KPAdd
#define HZ_KEY_KP_ENTER        ::Shake::Key::KPEnter
#define HZ_KEY_KP_EQUAL        ::Shake::Key::KPEqual

#define HZ_KEY_LEFT_SHIFT      ::Shake::Key::LeftShift
#define HZ_KEY_LEFT_CONTROL    ::Shake::Key::LeftControl
#define HZ_KEY_LEFT_ALT        ::Shake::Key::LeftAlt
#define HZ_KEY_LEFT_SUPER      ::Shake::Key::LeftSuper
#define HZ_KEY_RIGHT_SHIFT     ::Shake::Key::RightShift
#define HZ_KEY_RIGHT_CONTROL   ::Shake::Key::RightControl
#define HZ_KEY_RIGHT_ALT       ::Shake::Key::RightAlt
#define HZ_KEY_RIGHT_SUPER     ::Shake::Key::RightSuper
#define HZ_KEY_MENU            ::Shake::Key::Menu