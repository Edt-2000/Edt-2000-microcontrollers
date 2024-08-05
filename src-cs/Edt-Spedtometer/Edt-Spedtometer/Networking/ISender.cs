namespace EdtSpedtometer.Networking;

internal interface ISender
{
    Task InitializeAsync();
    Task SendAsync<T>(T payload);
}
