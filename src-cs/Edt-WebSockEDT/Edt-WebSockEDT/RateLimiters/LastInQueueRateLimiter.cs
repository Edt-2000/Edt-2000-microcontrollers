using System.Threading.RateLimiting;

namespace EdtWebSockEDT.RateLimiters;

public sealed class LastInQueueRateLimiter : RateLimiter
{
    private readonly object _lock = new();
    private readonly TimeSpan _waitTimeBetween;

    private CancellationTokenSource _cts = new();
    private TaskCompletionSource? _tcs;
    private DateTime _previousCompletion;

    public LastInQueueRateLimiter(
        TimeSpan waitTimeBetween)
    {
        _waitTimeBetween = waitTimeBetween;
    }

    public override TimeSpan? IdleDuration => null;

    public override RateLimiterStatistics? GetStatistics() => null;

    protected override async ValueTask<RateLimitLease> AcquireAsyncCore(int permitCount, CancellationToken cancellationToken)
    {
        if (permitCount > 1)
        {
            throw new ArgumentException("Permit count can only be 1");
        }

        Task waitTask;
        CancellationToken nextInLineToken;

        lock (_lock)
        {
            // cancel the previous one
            _cts.Cancel();

            // create a new source for this attempt
            _cts = new();

            // if no other call has made it through, always allow it
            if (_tcs == null)
            {
                return AllowThrough();
            }

            waitTask = _tcs.Task;
            nextInLineToken = _cts.Token;
        }

        // rate limit ourselves a bit
        var diff = DateTime.UtcNow - _previousCompletion;
        if (diff < _waitTimeBetween)
        {
            try
            {
                await Task.Delay(_waitTimeBetween - diff, cancellationToken).WaitAsync(nextInLineToken);
            }
            catch (TaskCanceledException)
            {
                return Bounce();
            }
        }

        // make sure the previous call is completely finished
        try
        {
            await waitTask.WaitAsync(nextInLineToken);
        }
        catch (TaskCanceledException)
        {
            return Bounce();
        }

        // lock so we're 100% sure that we are allowed through
        lock (_lock)
        {
            if (nextInLineToken.IsCancellationRequested)
            {
                return Bounce();
            }

            return AllowThrough();
        }

        RateLimitLease AllowThrough()
        {
            _tcs = new();
            _previousCompletion = DateTime.UtcNow;
            return new OneAtTheTimeRateLimitLease(true, _tcs);
        }

        static OneAtTheTimeRateLimitLease Bounce()
        {
            return new OneAtTheTimeRateLimitLease(false, new());
        }
    }

    protected override RateLimitLease AttemptAcquireCore(int permitCount)
    {
        throw new NotSupportedException("Only async flow is allowed");
    }

    private sealed class OneAtTheTimeRateLimitLease : RateLimitLease
    {
        private readonly TaskCompletionSource _tcs;

        public OneAtTheTimeRateLimitLease(
            bool isAcquired,
            TaskCompletionSource tcs)
        {
            IsAcquired = isAcquired;
            _tcs = tcs;
        }

        public override bool IsAcquired { get; }

        public override IEnumerable<string> MetadataNames => [];

        public override bool TryGetMetadata(string metadataName, out object? metadata)
        {
            metadata = null;
            return false;
        }

        protected override void Dispose(bool disposing)
        {
            _tcs.SetResult();
        }
    }
}
