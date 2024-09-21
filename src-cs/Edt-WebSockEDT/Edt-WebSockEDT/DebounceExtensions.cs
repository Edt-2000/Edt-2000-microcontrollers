namespace EdtWebSockEDT;

public static class DebounceExtensions
{
    public static Func<T, Task> Debounce<T>(this Func<T, Task> func, int milliseconds = 25)
    {
        CancellationTokenSource? cancelTokenSource = null;

        return async arg =>
        {
            cancelTokenSource?.Cancel();
            cancelTokenSource = new CancellationTokenSource();

            await Task.Delay(milliseconds, cancelTokenSource.Token)
                .ContinueWith(async t =>
                {
                    if (t.IsCompletedSuccessfully)
                    {
                        await func(arg);
                    }
                }, TaskScheduler.Default);
        };
    }
}
