#pragma once

namespace Messages
{
	enum ColorCommands : uint32_t
	{
		SingleSolid = 0,
		SinglePulse = 1,
		SingleSpark = 7,
		RainbowSolid = 2,
		RainbowPulse = 3,
		RainbowSpark = 8,
		VuMeter = 4,
		Twinkle = 5,
		Strobo = 6,
		Berserk = 15,
		DualSolid = 9,
		DualPulse = 10,
		DualSparkle = 11,
		Chase = 12,
		Bash = 13,
		ChaseStill = 14,

		DMXConfig = 254
	};

	struct SingleColorCommand
	{
		// 0 - 127
		uint32_t start;
		uint32_t end;

		// 0 - 255
		uint32_t hue;
		uint32_t saturation;
		uint32_t value;
		uint32_t duration;
	};

	struct DualColorCommand
	{
		// 0 - 127
		uint32_t start;
		uint32_t end;

		// 0 - 255
		uint32_t hue1;
		uint32_t hue2;
		uint32_t percentage;
		uint32_t duration;
	};

	struct RainbowCommand
	{
		// 0 - 127
		uint32_t start;
		uint32_t end;

		// 0 - 255
		uint32_t hue;
		uint32_t deltaHue;
		uint32_t duration;
	};

	struct VuMeterCommand
	{
		// 0 - 127
		uint32_t start;
		uint32_t end;
		uint32_t center;

		// 0 - 255
		uint32_t hue;
		uint32_t deltaHue;
		uint32_t intensity;
	};

	struct TwinkleCommand
	{
		// 0 - 127
		uint32_t start;
		uint32_t end;

		// 0 - 255
		uint32_t hue;
		uint32_t intensity;
	};

	struct ChaseCommand
	{
		// 0 - 255
		uint32_t hue;
		uint32_t speed;
		uint32_t fadeSpeed;
		uint32_t direction;
	};

	struct ChaseStillCommand
	{
		// 0 - 255
		uint32_t hue;
		uint32_t length;
	};

	struct BashCommand
	{
		// 0 - 255
		uint32_t hue;
		uint32_t intensity;
	};

	struct StroboCommand
	{
		// 0 - 255
		uint32_t hue;
		uint32_t intensity;
	};

	struct DMXConfigCommand
	{
		// 0 - 255

		uint32_t config;
		uint32_t deviceAddress;
		uint32_t deviceType;
		uint32_t maximumBrightness;
		uint32_t minimumBrightness;
	};

	struct CommandMessage
	{
		ColorCommands command;
		union Commands
		{
			SingleColorCommand singleColor;
			DualColorCommand dualColor;
			RainbowCommand rainbow;
			VuMeterCommand vuMeter;
			TwinkleCommand twinkle;
			ChaseCommand chase;
			ChaseStillCommand chaseStill;
			BashCommand bash;
			StroboCommand strobo;

			DMXConfigCommand dmxConfig;
		};

		Commands commands;
	};
} // namespace Messages