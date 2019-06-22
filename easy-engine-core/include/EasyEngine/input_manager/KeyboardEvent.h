#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H
#pragma once

namespace easy_engine {
	namespace input_manager {

		enum Action {
			kPressed = 0,
			kReleased = 1,
			kRepeated = 2
		};

		enum Modifier {
			kShift = 0x0001,
			kControl = 0x0002,
			kAlt = 0x0004,
			kSuper = 0x0008
		};

		enum Key {
			kUnknown = -1,
			kSpace = 32,
			kApostrophe = 39,
			kComma = 44,
			kMinus = 45,
			kPeriod = 46,
			kSlash = 47,
			k0 = 48,
			k1 = 49,
			k2 = 50,
			k3 = 51,
			k4 = 52,
			k5 = 53,
			k6 = 54,
			k7 = 55,
			k8 = 56,
			k9 = 57,
			kSemicolon = 59,
			kEqual = 61,
			kA = 65,
			kB = 66,
			kC = 67,
			kD = 68,
			kE = 69,
			kF = 70,
			kG = 71,
			kH = 72,
			kI = 73,
			kJ = 74,
			kK = 75,
			kL = 76,
			kM = 77,
			kN = 78,
			kO = 79,
			kP = 80,
			kQ = 81,
			kR = 82,
			kS = 83,
			kT = 84,
			kU = 85,
			kV = 86,
			kW = 87,
			kX = 88,
			kY = 89,
			kZ = 90,
			kLeftBracket = 91,
			kBackslash = 92,
			kRightBracket = 93,
			kGraveAccent = 96,
			kWorld1 = 161,
			kWorld2 = 162,
			kEscape = 256,
			kEnter = 257,
			kTab = 258,
			kBackspace = 259,
			kInsert = 260,
			kDelete = 261,
			kRight = 262,
			kLeft = 263,
			kDown = 264,
			kUp = 265,
			kPageUp = 266,
			kPageDown = 267,
			kHome = 268,
			kEnd = 269,
			kCapsLock = 280,
			kScrollLock = 281,
			kNumLock = 282,
			kPrintScreen = 283,
			kPause = 284,
			kF1 = 290,
			kF2 = 291,
			kF3 = 292,
			kF4 = 293,
			kF5 = 294,
			kF6 = 295,
			kF7 = 296,
			kF8 = 297,
			kF9 = 298,
			kF10 = 299,
			kF11 = 300,
			kF12 = 301,
			kF13 = 302,
			kF14 = 303,
			kF15 = 304,
			kF16 = 305,
			kF17 = 306,
			kF18 = 307,
			kF19 = 308,
			kF20 = 309,
			kF21 = 310,
			kF22 = 311,
			kF23 = 312,
			kF24 = 313,
			kF25 = 314,
			kKp0 = 320,
			kKp1 = 321,
			kKp2 = 322,
			kKp3 = 323,
			kKp4 = 324,
			kKp5 = 325,
			kKp6 = 326,
			kKp7 = 327,
			kKp8 = 328,
			kKp9 = 329,
			kKpDecimal = 330,
			kKpDivide = 331,
			kKpMultiply = 332,
			kKpSubtract = 333,
			kKpAdd = 334,
			kKpEnter = 335,
			kKpEqual = 336,
			kLeftShift = 340,
			kLeftControl = 341,
			kLeftAlt = 342,
			kLeftSuper = 343,
			kRightShift = 344,
			kRightControl = 345,
			kRightAlt = 346,
			kRightSuper = 347,
			kMenu = 348
		};

		struct KeyboardEvent {

			KeyboardEvent() = default;
			KeyboardEvent(Key key, int modifiers, Action action)
				: key(key), modifiers(modifiers), action(action) {}

			Key key;
			int modifiers;
			Action action;
		};
	}
}

#endif // !KEYBOARD_EVENT_H

