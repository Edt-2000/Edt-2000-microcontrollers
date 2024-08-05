namespace EdtSpedtometer.Messaging;

internal record AnimationAndSettingsMessage(
    string Animation) : SettingsMessage;
